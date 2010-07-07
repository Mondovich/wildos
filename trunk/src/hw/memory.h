/*
 * memory.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#include "../types.h"
#include "tss.h"

#ifndef MEMORY_H_
#define MEMORY_H_

void *memset(void *ptr, int value, size_t num);
void *memcpy(void *destination, const void *source, size_t num);
int memcmp(const void * ptr1, const void * ptr2, size_t num);

extern "C" void gdt_flush (uint32_t addr);
extern "C" void idt_flush (uint32_t addr);
extern "C" void tss_flush();

void init_idt (void);
void init_gdt (void);

// Allows the kernel stack in the TSS to be changed.
void set_kernel_stack(size_t stack);


#endif /* MEMORY_H_ */
