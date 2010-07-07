/*
 * utils.cpp
 *
 *  Created on: 05/lug/2010
 *      Author: RaimondoS
 */
#include "utils.h"
#include "../asm/asm.h"
#include "../hw/screen.h"

void panic (const char *file, int line, char *msg)
{
    printk ("PANIC: %s:%d : %s\n", file, line, msg);
    halt ();
}

void panic_assert (const char *file, int line, char *msg)
{
    printk ("ASSERTION-FAILED: %s:%d : %s\n", file, line, msg);
    halt ();
}
