/*
 * MemoryManager.cpp
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */
#include "MemoryManager.h"
#include "../../common/types.h"
#include "../../utils/string.h"
#include "../../log/Log.h"

namespace Hardware {

MemoryManager *MemoryManager::instance_ = NULL;

MemoryManager::MemoryManager() {
	gdt = GDT();
	tss = TSS();
}

MemoryManager *MemoryManager::instance() {
	if (!instance_)
		instance_ = new MemoryManager;
	return instance_;
}

void MemoryManager::init() {
	// Initialise the global descriptor table.
	DEBUG("Init GDT");
	gdt.init();
	DEBUG("end");
}

void MemoryManager::enablePaging(uint32_t memsize) {
//	// The size of physical memory.
//	size_t mem_end_page = memsize;
//
//	nframes = mem_end_page / 0x1000;
//	//	printk("nframes = %x\n", nframes);
//	frames = (size_t*) kmalloc(INDEX_FROM_BIT(nframes));
//	//	printk("frames = %x\n", *frames);
//	memset(frames, 0, INDEX_FROM_BIT(nframes));
//
//	// Let's make a page directory.
//	kernel_directory = (page_directory_t*) kmalloc(sizeof(page_directory_t), true);
//	//	printk("kernel_directory = %x\n", kernel_directory);
//	memset(kernel_directory, 0, sizeof(page_directory_t));
//	kernel_directory->physical_addr = (size_t) kernel_directory->physical_tables;
//	current_directory = kernel_directory;
//	//	printk("current_directory = %x\n", current_directory);
//
//	/* Map some pages in the kernel heap area.
//	 * Here we call get_page but not alloc_frame. This causes page_table_t's
//	 * to be created where necessary. We can't allocate frames yet because they
//	 * they need to be identity mapped first below, and yet we can't increase
//	 * placement_address between identity mapping and enabling the heap!
//	 */
//	//	puts("Map some pages in the kernel heap area");
//	for (size_t i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
//		get_page(i, true, kernel_directory);
//
//	// We need to identity map (phys addr = virt addr) from
//	// 0x0 to the end of used memory, so we can access this
//	// transparently, as if paging wasn't enabled.
//	// NOTE that we use a while loop here deliberately.
//	// inside the loop body we actually change placement_address
//	// by calling kmalloc(). A while loop causes this to be
//	// computed on-the-fly rather than once at the start.
//	for (size_t i = 0; i < placement_address + 0x1000; i += 0x1000) {
//		// Kernel code is readable but not writeable from userspace.
//		alloc_frame(get_page(i, true, kernel_directory), 0, 0);
//	}
//
//	// Now allocate those pages we mapped earlier.
//	for (size_t i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
//		alloc_frame(get_page(i, true, kernel_directory), 0, 0);
//
//	// Before we enable paging, we must register our page fault handler.
//	set_interrupt_handler(14, page_fault);
//
//	// Now, enable paging!
//	switch_page_directory(kernel_directory);
//
//	/* Initialise the kernel heap. */
//	kheap = create_heap(KHEAP_START, KHEAP_START + KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);
//
//	current_directory = clone_directory(kernel_directory);
//	//	printk("current_directory = %x\n", current_directory);
//	switch_page_directory(current_directory);
//
//	return;
}

void MemoryManager::setKernelStack(size_t stack) {
	tss.setKernelStack(stack);
}

} // namespace Hardware
