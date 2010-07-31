/*
 * Timer.cpp
 *
 *  Created on: 29/lug/2010
 *      Author: RaimondoS
 */

#include "Timer.h"
#include "../io/IOManager.h"
#include "../cpu/InterruptManager.h"
#include "../../log/Log.h"
#include "../../std/iostream.h"

namespace Hardware {

void Timer::init(uint32_t frequency) {

	DEBUG("init");
	this->frequency = frequency;

	//	set_interrupt_handler(IRQ0, (isr_t) &timer_callback); /* register our callback */

	/* The value we send to the PIT is the value to divide it's input clock
	 * (1193180 Hz) by, to get our required frequency. Important to note is
	 * that the divisor must be small enough to fit into 16-bits.
	 */
	uint32_t divisor = 1193180 / frequency;

	IOManager::instance()->outb(0x43, 0x36); /* Send command byte */
	/* Divisor has to be sent byte-wise, so split here into upper/lower bytes. */
	uint8_t l = (uint8_t) (divisor & 0xFF);
	uint8_t h = (uint8_t) ((divisor >> 8) & 0xFF);
	/* Send the frequency divisor. */
	IOManager::instance()->outb(0x40, l);
	IOManager::instance()->outb(0x40, h);
	DEBUG("end");
	return;
}

void Timer::call(Registers& regs) {
	std::cout << Screen::Red << ".";
	tick++;
}

}
