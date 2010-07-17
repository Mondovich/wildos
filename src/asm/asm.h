/*
 * asm.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#ifndef __ASM_H
#define __ASM_H

#include "../types.h"

enum REGS {
	EAX, EBX, EBP, ESP, CR0, CR3
};

#define disableInt()    asm volatile ("cli");
#define enableInt()    asm volatile ("sti");

#define reboot()        \
do {                    \
	disableInt();             \
    outb (0x64, 0xFE);  \
    enableInt ();             \
} while (/* CONSTCOND */ 0)

#define halt()                      \
	printk ("System halted.\n");    \
	for (;;);

size_t getRegister(REGS reg);
void setRegister(REGS reg, size_t value);

#endif /* __ASM_H */
