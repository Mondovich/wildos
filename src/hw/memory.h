/*
 * memory.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#include "../types.h"

#ifndef MEMORY_H_
#define MEMORY_H_

void *memset(void *ptr, int value, size_t num);
void *memcpy(void *destination, const void *source, size_t num);
int memcmp(const void * ptr1, const void * ptr2, size_t num);

/*!
 * \struct gdt_entry_t
 * \brief Structure describing a segment's descriptor.
 */
struct gdt_entry_t
{
    uint16_t limit_low;     /*!< The lower 16 bits of the limit. */
    uint16_t base_low;      /*!< The lower 16 bits of the base. */
    uint8_t  base_middle;   /*!< The next 8 bits of the base. */
    uint8_t  access;        /*!< Access flags, determine what ring this segment can be used in. */
    uint8_t  granularity;
    uint8_t  base_high;     /*!< The last 8 bits of the base. */
} __attribute__ ((packed));

/*!
 * \struct gdt_t
 * \brief Address of the GDT (base/limit).
 */
struct gdt_t
{
    uint16_t limit; /*!< The upper 16 bits of all selector limits. */
    uint32_t base;  /*!< The address of the first gdt_entry_t struct. */
} __attribute__ ((packed));

extern "C" void gdt_flush (uint32_t addr);
void init_gdt (void);

/*!
 * \struct idt_entry_t
 * \brief Structure describing an interrupt gate.
 */
struct idt_entry_t
{
    uint16_t base_low;  /*!< The lower 16 bits of the address to jump when this interrupt fires. */
    uint16_t sel;       /*!< Kernel segment selector. */
    uint8_t  unused;    /*!< This must always be zero. */
    uint8_t  flags;     /*!< More flag. See documentation. */
    uint16_t base_high; /*!< The upper 16 bits of the address to jump to. */
} __attribute__ ((packed));

/*!
 * \struct idt_t
 * \brief Address of the IDT (base/limit).
 */
struct idt_t
{
    uint16_t limit;
    uint32_t base;  /*!< The address of the first element in our idt_entry_t array. */
} __attribute__ ((packed));

extern void idt_flush (uint32_t addr);
void init_idt (void);

/* Extern directives let us access the addresses of our ASM ISR handlers */
extern void isr0  (void);
extern void isr1  (void);
extern void isr2  (void);
extern void isr3  (void);
extern void isr4  (void);
extern void isr5  (void);
extern void isr6  (void);
extern void isr7  (void);
extern void isr8  (void);
extern void isr9  (void);
extern void isr10 (void);
extern void isr11 (void);
extern void isr12 (void);
extern void isr13 (void);
extern void isr14 (void);
extern void isr15 (void);
extern void isr16 (void);
extern void isr17 (void);
extern void isr18 (void);
extern void isr19 (void);
extern void isr20 (void);
extern void isr21 (void);
extern void isr22 (void);
extern void isr23 (void);
extern void isr24 (void);
extern void isr25 (void);
extern void isr26 (void);
extern void isr27 (void);
extern void isr28 (void);
extern void isr29 (void);
extern void isr30 (void);
extern void isr31 (void);
extern void irq0  (void);
extern void irq1  (void);
extern void irq2  (void);
extern void irq3  (void);
extern void irq4  (void);
extern void irq5  (void);
extern void irq6  (void);
extern void irq7  (void);
extern void irq8  (void);
extern void irq9  (void);
extern void irq10 (void);
extern void irq11 (void);
extern void irq12 (void);
extern void irq13 (void);
extern void irq14 (void);
extern void irq15 (void);
extern void isr128(void);

#endif /* MEMORY_H_ */
