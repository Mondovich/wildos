/*
 * asm.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#ifndef __ASM_H
#define __ASM_H

#define cli()    asm volatile ("cli")
#define sti()    asm volatile ("sti")

#define reboot()        \
do {                    \
    cli ();             \
    outb (0x64, 0xFE);  \
    sti ();             \
} while (/* CONSTCOND */ 0)

#define halt()                      \
	printk ("System halted.\n");    \
	for (;;);

#endif /* __ASM_H */
