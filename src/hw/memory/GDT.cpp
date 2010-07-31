/*
 * GDT.cpp
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */

#include "GDT.h"

namespace Hardware {

void GDT::init() {
	DEBUG("init");
	addr.limit = (sizeof(struct gdt_entry_t) * 6) - 1;
	addr.base = (uint32_t) &entries;
	DEBUG("setGate");
	setGate(0, 0, 0, 0, 0); /* Null segment */
	setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
	setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
	setGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User mode code segment */
	setGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User mode data segment */
	DEBUG("write TSS");
	writeTss(5, 0x10, 0x0);
	DEBUG("gdt flush");
	gdtFlush((uint32_t) &addr);
	DEBUG("tss flush");
	tssFlush();
	DEBUG("end");
}

void GDT::setGate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
	entries[num].baseLow = (base & 0xFFFF);
	entries[num].baseMiddle = (base >> 16) & 0xFF;
	entries[num].baseHigh = (base >> 24) & 0xFF;

	entries[num].limitLow = (limit & 0xFFFF);
	entries[num].granularity = (limit >> 16) & 0x0F;

	entries[num].granularity |= gran & 0xF0;
	entries[num].access = access;
}

// Initialise our task state segment structure.
void GDT::writeTss(int32_t num, uint16_t ss0, uint32_t esp0) {
	// Firstly, let's compute the base and limit of our entry into the GDT.
	uint32_t base = (uint32_t) &tss.entry;
	uint32_t limit = base + sizeof(tss.entry);

	// Now, add our TSS descriptor's address to the GDT.
	setGate(num, base, limit, 0xE9, 0x00);

	// Ensure the descriptor is initially zero.
	memset(&tss.entry, 0, sizeof(tss.entry));

	tss.entry.ss0 = ss0; // Set the kernel stack segment.
	tss.entry.esp0 = esp0; // Set the kernel stack pointer.

	// Here we set the cs, ss, ds, es, fs and gs entries in the TSS. These specify what
	// segments should be loaded when the processor switches to kernel mode. Therefore
	// they are just our normal kernel code/data segments - 0x08 and 0x10 respectively,
	// but with the last two bits set, making 0x0b and 0x13. The setting of these bits
	// sets the RPL (requested privilege level) to 3, meaning that this TSS can be used
	// to switch to kernel mode from ring 3.
	tss.entry.cs = 0x0b;
	tss.entry.ss = tss.entry.ds = tss.entry.es = tss.entry.fs = tss.entry.gs = 0x13;
}

} // namespace Hardware

