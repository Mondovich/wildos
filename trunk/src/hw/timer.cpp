/*
 * pit.cpp
 *
 *  Created on: 02/lug/2010
 *      Author: RaimondoS
 */
#include "timer.h"
#include "task.h"
#include "../common/types.h"
#include "isr.h"
#include "io.h"
#include "cpu/InterruptManager.h"

uint32_t tick = 0;

static void timer_callback (registers_t *regs)
{
    tick++;
    switch_task();
    return;
}

void init_timer (uint32_t frequency)
{
    uint32_t divisor;
    uint8_t l, h;

    set_interrupt_handler (Hardware::InterruptManager::IRQ0, (isr_t) &timer_callback); /* register our callback */

    /* The value we send to the PIT is the value to divide it's input clock
     * (1193180 Hz) by, to get our required frequency. Important to note is
     * that the divisor must be small enough to fit into 16-bits.
     */

    divisor = 1193180 / frequency;

    outb (0x43, 0x36); /* Send command byte */
    /* Divisor has to be sent byte-wise, so split here into upper/lower bytes. */
    l = (uint8_t) (divisor & 0xFF);
    h = (uint8_t) ((divisor >> 8) & 0xFF);
    /* Send the frequency divisor. */
    outb (0x40, l);
    outb (0x40, h);

    return;
}
