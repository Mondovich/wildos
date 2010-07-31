/*
 * IDT.cpp
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */

#include "IDT.h"
#include "../memory/MemoryManager.h"
#include "../io/IOManager.h"
#include "../../utils/string.h"

namespace Hardware {

IDT::IDT() {
	// TODO Auto-generated constructor stub

}

IDT::~IDT() {
	// TODO Auto-generated destructor stub
}

void IDT::init() {
	addr.limit = sizeof(struct idt_entry_t) * 256 - 1;
	addr.base = (uint32_t) &entries;

	memset(&entries, 0, sizeof(struct idt_entry_t) * 256);

	// Remap the irq table.
	IOManager::instance()->outb(0x20, 0x11);
	IOManager::instance()->outb(0xA0, 0x11);
	IOManager::instance()->outb(0x21, 0x20);
	IOManager::instance()->outb(0xA1, 0x28);
	IOManager::instance()->outb(0x21, 0x04);
	IOManager::instance()->outb(0xA1, 0x02);
	IOManager::instance()->outb(0x21, 0x01);
	IOManager::instance()->outb(0xA1, 0x01);
	IOManager::instance()->outb(0x21, 0x0);
	IOManager::instance()->outb(0xA1, 0x0);

	/* exceptions */
	setGate(0x00, (uint32_t) isr0, 0x08, 0x8E);
	setGate(0x01, (uint32_t) isr1, 0x08, 0x8E);
	setGate(0x02, (uint32_t) isr2, 0x08, 0x8E);
	setGate(0x03, (uint32_t) isr3, 0x08, 0x8E);
	setGate(0x04, (uint32_t) isr4, 0x08, 0x8E);
	setGate(0x05, (uint32_t) isr5, 0x08, 0x8E);
	setGate(0x06, (uint32_t) isr6, 0x08, 0x8E);
	setGate(0x07, (uint32_t) isr7, 0x08, 0x8E);
	setGate(0x08, (uint32_t) isr8, 0x08, 0x8E);
	setGate(0x09, (uint32_t) isr9, 0x08, 0x8E);
	setGate(0x0A, (uint32_t) isr10, 0x08, 0x8E);
	setGate(0x0B, (uint32_t) isr11, 0x08, 0x8E);
	setGate(0x0C, (uint32_t) isr12, 0x08, 0x8E);
	setGate(0x0D, (uint32_t) isr13, 0x08, 0x8E);
	setGate(0x0E, (uint32_t) isr14, 0x08, 0x8E);
	setGate(0x0F, (uint32_t) isr15, 0x08, 0x8E);
	setGate(0x10, (uint32_t) isr16, 0x08, 0x8E);
	setGate(0x11, (uint32_t) isr17, 0x08, 0x8E);
	setGate(0x12, (uint32_t) isr18, 0x08, 0x8E);
	setGate(0x13, (uint32_t) isr19, 0x08, 0x8E);
	setGate(0x14, (uint32_t) isr20, 0x08, 0x8E);
	setGate(0x15, (uint32_t) isr21, 0x08, 0x8E);
	setGate(0x16, (uint32_t) isr22, 0x08, 0x8E);
	setGate(0x17, (uint32_t) isr23, 0x08, 0x8E);
	setGate(0x18, (uint32_t) isr24, 0x08, 0x8E);
	setGate(0x19, (uint32_t) isr25, 0x08, 0x8E);
	setGate(0x1A, (uint32_t) isr26, 0x08, 0x8E);
	setGate(0x1B, (uint32_t) isr27, 0x08, 0x8E);
	setGate(0x1C, (uint32_t) isr28, 0x08, 0x8E);
	setGate(0x1D, (uint32_t) isr29, 0x08, 0x8E);
	setGate(0x1E, (uint32_t) isr30, 0x08, 0x8E);
	setGate(0x1F, (uint32_t) isr31, 0x08, 0x8E);

	/* IRQs */
	setGate(0x20, (uint32_t) irq0, 0x08, 0x8E);
	setGate(0x21, (uint32_t) irq1, 0x08, 0x8E);
	setGate(0x22, (uint32_t) irq2, 0x08, 0x8E);
	setGate(0x23, (uint32_t) irq3, 0x08, 0x8E);
	setGate(0x24, (uint32_t) irq4, 0x08, 0x8E);
	setGate(0x25, (uint32_t) irq5, 0x08, 0x8E);
	setGate(0x26, (uint32_t) irq6, 0x08, 0x8E);
	setGate(0x27, (uint32_t) irq7, 0x08, 0x8E);
	setGate(0x28, (uint32_t) irq8, 0x08, 0x8E);
	setGate(0x29, (uint32_t) irq9, 0x08, 0x8E);
	setGate(0x2A, (uint32_t) irq10, 0x08, 0x8E);
	setGate(0x2B, (uint32_t) irq11, 0x08, 0x8E);
	setGate(0x2C, (uint32_t) irq12, 0x08, 0x8E);
	setGate(0x2D, (uint32_t) irq13, 0x08, 0x8E);
	setGate(0x2E, (uint32_t) irq14, 0x08, 0x8E);
	setGate(0x2F, (uint32_t) irq15, 0x08, 0x8E);

	/* syscall */
	setGate(0x80, (uint32_t) isr128, 0x08, 0x8E);

	idt_flush((uint32_t) &addr);
}

void IDT::setGate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
	entries[num].base_low = base & 0xFFFF;
	entries[num].base_high = (base >> 16) & 0xFFFF;

	entries[num].sel = sel;
	entries[num].unused = 0;
	entries[num].flags = flags | 0x60;
}

}
