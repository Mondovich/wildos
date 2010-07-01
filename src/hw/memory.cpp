/*
 * memory.cpp
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#include "memory.h"
#include "../types.h"

struct gdt_entry_t gdt_entries[6];
struct gdt_t p_gdt;
//struct tss_entry_t tss_entry;

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

static void gdt_set_gate (int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

void init_gdt(void) {
	p_gdt.limit = (sizeof(struct gdt_entry_t) * 6) - 1;
	p_gdt.base = (uint32_t) &gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0); /* Null segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User mode code segment */
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User mode data segment */
	//write_tss(5, 0x10, 0x0);

	gdt_flush((uint32_t) &p_gdt);
	//tss_flush();
}
