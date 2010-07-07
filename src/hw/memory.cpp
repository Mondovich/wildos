/*
 * memory.cpp
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#include "memory.h"
#include "io.h"
#include "gdt.h"
#include "idt.h"
#include "tss.h"
#include "../types.h"

struct gdt_entry_t gdt_entries[6];
struct gdt_t p_gdt;
struct idt_entry_t idt_entries[256];
struct idt_t p_idt;
struct tss_entry_t tss_entry;

void *memset(void *ptr, int value, size_t num) {
	char *p = (char *) ptr;
	for (; num != 0; --num)
		*p++ = value;
	return ptr;
}

void *memcpy(void *destination, const void *source, size_t num) {
	const char *sp = (const char *) source;
	char *dp = (char *) destination;
	for (; num != 0; num--)
		*dp++ = *sp++;
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
	const char *p1 = (const char *) ptr1;
	const char *p2 = (const char *) ptr2;
	for (size_t i = 0; i < num; ++i) {
		if (*p1 != *p2)
			return *p1 - *p2;
	}
	return 0;
}

static void gdt_set_gate(int num, uint32_t base, uint32_t limit,
		uint8_t access, uint8_t gran) {
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access = access;
}

// Initialise our task state segment structure.
static void write_tss(int32_t num, uint16_t ss0, uint32_t esp0)
{
    // Firstly, let's compute the base and limit of our entry into the GDT.
	uint32_t base = (uint32_t) &tss_entry;
	uint32_t limit = base + sizeof(tss_entry);

    // Now, add our TSS descriptor's address to the GDT.
    gdt_set_gate(num, base, limit, 0xE9, 0x00);

    // Ensure the descriptor is initially zero.
    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0  = ss0;  // Set the kernel stack segment.
    tss_entry.esp0 = esp0; // Set the kernel stack pointer.

    // Here we set the cs, ss, ds, es, fs and gs entries in the TSS. These specify what
    // segments should be loaded when the processor switches to kernel mode. Therefore
    // they are just our normal kernel code/data segments - 0x08 and 0x10 respectively,
    // but with the last two bits set, making 0x0b and 0x13. The setting of these bits
    // sets the RPL (requested privilege level) to 3, meaning that this TSS can be used
    // to switch to kernel mode from ring 3.
    tss_entry.cs   = 0x0b;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
}

void init_gdt(void) {
	p_gdt.limit = (sizeof(struct gdt_entry_t) * 6) - 1;
	p_gdt.base = (uint32_t) &gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0); /* Null segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User mode code segment */
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User mode data segment */
	write_tss(5, 0x10, 0x0);

	gdt_flush((uint32_t) &p_gdt);
	tss_flush();
}

static void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
	idt_entries[num].base_low = base & 0xFFFF;
	idt_entries[num].base_high = (base >> 16) & 0xFFFF;

	idt_entries[num].sel = sel;
	idt_entries[num].unused = 0;
	idt_entries[num].flags = flags | 0x60;
}

void init_idt() {
	p_idt.limit = sizeof(struct idt_entry_t) * 256 - 1;
	p_idt.base = (uint32_t) &idt_entries;

	memset(&idt_entries, 0, sizeof(struct idt_entry_t) * 256);

	// Remap the irq table.
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	/* exceptions */
	idt_set_gate(0x00, (uint32_t) isr0, 0x08, 0x8E);
	idt_set_gate(0x01, (uint32_t) isr1, 0x08, 0x8E);
	idt_set_gate(0x02, (uint32_t) isr2, 0x08, 0x8E);
	idt_set_gate(0x03, (uint32_t) isr3, 0x08, 0x8E);
	idt_set_gate(0x04, (uint32_t) isr4, 0x08, 0x8E);
	idt_set_gate(0x05, (uint32_t) isr5, 0x08, 0x8E);
	idt_set_gate(0x06, (uint32_t) isr6, 0x08, 0x8E);
	idt_set_gate(0x07, (uint32_t) isr7, 0x08, 0x8E);
	idt_set_gate(0x08, (uint32_t) isr8, 0x08, 0x8E);
	idt_set_gate(0x09, (uint32_t) isr9, 0x08, 0x8E);
	idt_set_gate(0x0A, (uint32_t) isr10, 0x08, 0x8E);
	idt_set_gate(0x0B, (uint32_t) isr11, 0x08, 0x8E);
	idt_set_gate(0x0C, (uint32_t) isr12, 0x08, 0x8E);
	idt_set_gate(0x0D, (uint32_t) isr13, 0x08, 0x8E);
	idt_set_gate(0x0E, (uint32_t) isr14, 0x08, 0x8E);
	idt_set_gate(0x0F, (uint32_t) isr15, 0x08, 0x8E);
	idt_set_gate(0x10, (uint32_t) isr16, 0x08, 0x8E);
	idt_set_gate(0x11, (uint32_t) isr17, 0x08, 0x8E);
	idt_set_gate(0x12, (uint32_t) isr18, 0x08, 0x8E);
	idt_set_gate(0x13, (uint32_t) isr19, 0x08, 0x8E);
	idt_set_gate(0x14, (uint32_t) isr20, 0x08, 0x8E);
	idt_set_gate(0x15, (uint32_t) isr21, 0x08, 0x8E);
	idt_set_gate(0x16, (uint32_t) isr22, 0x08, 0x8E);
	idt_set_gate(0x17, (uint32_t) isr23, 0x08, 0x8E);
	idt_set_gate(0x18, (uint32_t) isr24, 0x08, 0x8E);
	idt_set_gate(0x19, (uint32_t) isr25, 0x08, 0x8E);
	idt_set_gate(0x1A, (uint32_t) isr26, 0x08, 0x8E);
	idt_set_gate(0x1B, (uint32_t) isr27, 0x08, 0x8E);
	idt_set_gate(0x1C, (uint32_t) isr28, 0x08, 0x8E);
	idt_set_gate(0x1D, (uint32_t) isr29, 0x08, 0x8E);
	idt_set_gate(0x1E, (uint32_t) isr30, 0x08, 0x8E);
	idt_set_gate(0x1F, (uint32_t) isr31, 0x08, 0x8E);

	/* IRQs */
	idt_set_gate(0x20, (uint32_t) irq0, 0x08, 0x8E);
	idt_set_gate(0x21, (uint32_t) irq1, 0x08, 0x8E);
	idt_set_gate(0x22, (uint32_t) irq2, 0x08, 0x8E);
	idt_set_gate(0x23, (uint32_t) irq3, 0x08, 0x8E);
	idt_set_gate(0x24, (uint32_t) irq4, 0x08, 0x8E);
	idt_set_gate(0x25, (uint32_t) irq5, 0x08, 0x8E);
	idt_set_gate(0x26, (uint32_t) irq6, 0x08, 0x8E);
	idt_set_gate(0x27, (uint32_t) irq7, 0x08, 0x8E);
	idt_set_gate(0x28, (uint32_t) irq8, 0x08, 0x8E);
	idt_set_gate(0x29, (uint32_t) irq9, 0x08, 0x8E);
	idt_set_gate(0x2A, (uint32_t) irq10, 0x08, 0x8E);
	idt_set_gate(0x2B, (uint32_t) irq11, 0x08, 0x8E);
	idt_set_gate(0x2C, (uint32_t) irq12, 0x08, 0x8E);
	idt_set_gate(0x2D, (uint32_t) irq13, 0x08, 0x8E);
	idt_set_gate(0x2E, (uint32_t) irq14, 0x08, 0x8E);
	idt_set_gate(0x2F, (uint32_t) irq15, 0x08, 0x8E);

	/* syscall */
	idt_set_gate(0x80, (uint32_t) isr128, 0x08, 0x8E);

	idt_flush((uint32_t) &p_idt);
}

void set_kernel_stack(size_t stack)
{
    tss_entry.esp0 = stack;
}
