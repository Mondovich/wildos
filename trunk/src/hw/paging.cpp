/*
 * paging.cpp
 *
 *  Created on: 05/lug/2010
 *      Author: RaimondoS
 */

#include "paging.h"
#include "kheap.h"
#include "memory/MemoryManager.h"
#include "screen.h"
#include "isr.h"
#include "../utils/utils.h"
#include "../utils/string.h"
#include "../common/types.h"

size_t *frames;
size_t nframes;

// ASM procedure
extern "C" void copy_page_physical(size_t, size_t);
// Defined in kheap.c
extern size_t placement_address;
extern heap_t *kheap;

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

page_directory_t* kernel_directory;
page_directory_t* current_directory;

void init_paging(uint32_t memsize) {
	// The size of physical memory.
	size_t mem_end_page = memsize;

	nframes = mem_end_page / 0x1000;
//	printk("nframes = %x\n", nframes);
	frames = (size_t*) kmalloc(INDEX_FROM_BIT(nframes));
//	printk("frames = %x\n", *frames);
	memset(frames, 0, INDEX_FROM_BIT(nframes));

	// Let's make a page directory.
	kernel_directory = (page_directory_t*) kmalloc(sizeof(page_directory_t), true);
//	printk("kernel_directory = %x\n", kernel_directory);
	memset(kernel_directory, 0, sizeof(page_directory_t));
	kernel_directory->physical_addr = (size_t) kernel_directory->physical_tables;
	current_directory = kernel_directory;
//	printk("current_directory = %x\n", current_directory);

	/* Map some pages in the kernel heap area.
	 * Here we call get_page but not alloc_frame. This causes page_table_t's
	 * to be created where necessary. We can't allocate frames yet because they
	 * they need to be identity mapped first below, and yet we can't increase
	 * placement_address between identity mapping and enabling the heap!
	 */
//	puts("Map some pages in the kernel heap area");
	for (size_t i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
		get_page(i, true, kernel_directory);

	// We need to identity map (phys addr = virt addr) from
	// 0x0 to the end of used memory, so we can access this
	// transparently, as if paging wasn't enabled.
	// NOTE that we use a while loop here deliberately.
	// inside the loop body we actually change placement_address
	// by calling kmalloc(). A while loop causes this to be
	// computed on-the-fly rather than once at the start.
	for (size_t i = 0; i < placement_address + 0x1000; i += 0x1000) {
		// Kernel code is readable but not writeable from userspace.
		alloc_frame(get_page(i, true, kernel_directory), 0, 0);
	}

	// Now allocate those pages we mapped earlier.
	for (size_t i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
		alloc_frame(get_page(i, true, kernel_directory), 0, 0);

	// Before we enable paging, we must register our page fault handler.
	set_interrupt_handler(14, page_fault);

	// Now, enable paging!
	switch_page_directory(kernel_directory);

	/* Initialise the kernel heap. */
	kheap = create_heap(KHEAP_START, KHEAP_START + KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);

	current_directory = clone_directory(kernel_directory);
//	printk("current_directory = %x\n", current_directory);
	switch_page_directory(current_directory);

	return;
}

// Static function to set a bit in the frames bitset
static void set_frame(size_t frame_addr) {
	size_t frame = frame_addr / 0x1000;
	size_t idx = INDEX_FROM_BIT(frame);
	size_t off = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << off);
}

// Static function to clear a bit in the frames bitset
static void clear_frame(size_t frame_addr) {
	size_t frame = frame_addr / 0x1000;
	size_t idx = INDEX_FROM_BIT(frame);
	size_t off = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << off);
}

// Static function to test if a bit is set.
static size_t test_frame(size_t frame_addr) {
	size_t frame = frame_addr / 0x1000;
	size_t idx = INDEX_FROM_BIT(frame);
	size_t off = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1 << off));
}

// Static function to find the first free frame.
static size_t first_frame() {
	size_t i, j;
	for (i = 0; i < INDEX_FROM_BIT(nframes); i++) {
		if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
		{
			// at least one bit is free here.
			for (j = 0; j < 32; j++) {
				size_t toTest = 0x1 << j;
				if (!(frames[i] & toTest)) {
					return i * 4 * 8 + j;
				}
			}
		}
	}
	return (size_t) -1;
}

// Function to allocate a frame.
void alloc_frame(page_t *page, int is_kernel, int is_writeable) {
	if (page->frame != 0) {
		return; // Frame was already allocated, return straight away.
	} else {
		size_t idx = first_frame(); // idx is now the index of the first free frame.
		//		printk("idx = %u\n", idx);
		if (idx == (size_t) -1) {
			// PANIC is just a macro that prints a message to the screen then hits an infinite loop.
			PANIC("No free frames!");
		}
		set_frame(idx * 0x1000); // this frame is now ours!
		page->present = 1; // Mark it as present.
		page->rw = (is_writeable) ? 1 : 0; // Should the page be writeable?
		page->user = (is_kernel) ? 0 : 1; // Should the page be user-mode?
		page->frame = idx;
	}
}

// Function to deallocate a frame.
void free_frame(page_t *page) {
	size_t frame;
	if (!(frame = page->frame)) {
		return; // The given page didn't actually have an allocated frame!
	} else {
		clear_frame(frame); // Frame is now free again.
		page->frame = 0x0; // Page now doesn't have a frame.
	}
}

void switch_page_directory(page_directory_t *dir) {
//	printk("Switching to %x\n", dir->physical_addr);
	current_directory = dir;
	asm volatile("mov %0, %%cr3":: "r"(dir->physical_addr));
	size_t cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000; // Enable paging!
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(size_t address, bool make, page_directory_t *dir) {
	// Turn the address into an index.
	address /= 0x1000;
	// Find the page table containing this address.
	size_t table_idx = address / 1024;
	//printk("address = %x, table_idx = %u\n", address, table_idx);
	if (dir->tables[table_idx]) // If this table is already assigned
	{
		return &dir->tables[table_idx]->pages[address % 1024];
	} else if (make) {
		size_t tmp;
		dir->tables[table_idx] = (page_table_t*) kmalloc(sizeof(page_table_t), true, &tmp);
		memset(dir->tables[table_idx], 0, 0x1000);
		dir->physical_tables[table_idx] = tmp | 0x7; // PRESENT, RW, US.
		return &dir->tables[table_idx]->pages[address % 1024];
	} else {
		return 0;
	}
}

void page_fault(registers_t *regs) {
	// A page fault has occurred.
	// The faulting address is stored in the CR2 register.
	size_t faulting_address;
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

	// The error code gives us details of what happened.
	int present = !((*regs).err_code & 0x1); // Page not present
	int rw = (*regs).err_code & 0x2; // Write operation?
	int us = (*regs).err_code & 0x4; // Processor was in user-mode?
	int reserved = (*regs).err_code & 0x8; // Overwritten CPU-reserved bits of page entry?
	int id = (*regs).err_code & 0x10; // Caused by an instruction fetch?

	// Output an error message.
	fputs("Page fault! ( ");
	if (present) {
		fputs("present ");
	}
	if (rw) {
		fputs("read-only ");
	}
	if (us) {
		fputs("user-mode ");
	}
	if (reserved) {
		fputs("reserved ");
	}
	printk(") at %x\n", faulting_address);
	PANIC("Page fault");
}
static page_table_t *clone_table(page_table_t *src, size_t *phys_addr) {
	int i;

	/* Make a new page table, which is page aligned. */
	page_table_t *table = (page_table_t *) kmalloc(sizeof(page_table_t), true, phys_addr);
	memset(table, 0, sizeof(page_directory_t)); /* Ensure that the new table is blank. */

	/* For every entry in the table... */
	for (i = 0; i < 1024; ++i) {
		/* If the source entry has a frame associated with it... */
		if (!src->pages[i].frame)
			continue;

		/* Get a new frame. */
		alloc_frame(&table->pages[i], 0, 0);
		/* Clone the flags from source to destination. */

		if (src->pages[i].present)
			table->pages[i].present = 1;
		if (src->pages[i].rw)
			table->pages[i].rw = 1;
		if (src->pages[i].user)
			table->pages[i].user = 1;
		if (src->pages[i].accessed)
			table->pages[i].accessed = 1;
		if (src->pages[i].dirty)
			table->pages[i].dirty = 1;

		/* Physically copy the data across. This function is in process.asm. */
		copy_page_physical(src->pages[i].frame * 0x1000, table->pages[i].frame * 0x1000);
	}
	return table;
}
page_directory_t *clone_directory(page_directory_t *src) {
	size_t phys, offset;
	int i;

	/* Make a new page directory and obtain its physical address. */
	page_directory_t *dir = (page_directory_t *) kmalloc(sizeof(page_directory_t), true, &phys);
	memset(dir, 0, sizeof(page_directory_t)); /* Ensure that it is blank. */

	/* Get the offset of tablesPhysical from the start of the page_directory_t structure. */
	offset = (size_t) dir->physical_tables - (size_t) dir;

	/* Then the physical address of dir->tablesPhysical is: */
	dir->physical_addr = phys + offset;

	/* Go through each page table. If the page table is in the kernel directory, do not make a new copy. */
	for (i = 0; i < 1024; i++) {
		if (!src->tables[i])
			continue;

		if (kernel_directory->tables[i] == src->tables[i]) {
			/* It's in the kernel, so just use the same pointer. */
			dir->tables[i] = src->tables[i];
			dir->physical_tables[i] = src->physical_tables[i];
		} else {
			/* Copy the table. */
			size_t phys;
			dir->tables[i] = clone_table(src->tables[i], &phys);
			dir->physical_tables[i] = phys | 0x07;
		}
	}

	return dir;
}
