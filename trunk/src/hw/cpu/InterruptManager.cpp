/*
 * InterruptManager.cpp
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */

#include "InterruptManager.h"
#include "../../common/types.h"
#include "../../std/iostream.h"

namespace Hardware {

InterruptManager *InterruptManager::instance_ = NULL;

InterruptManager *InterruptManager::instance() {
	if (!instance_)
		instance_ = new InterruptManager;
	return instance_;
}

void InterruptManager::init() {
	idt.init();
}

void InterruptManager::setInterruptHandler(ISR num, InterruptHandler *handler){
	std::clog << Screen::White << "Interrupt " << (uint32_t) num << " set";
	handlers[num] = handler;
}

void InterruptManager::handler(Registers &regs){
	uint8_t intNumber = regs.int_no & 0xFF;

	if (instance()->handlers[intNumber]) {
		instance()->handlers[intNumber]->call(regs);
	} else {
		std::cout << Screen::White << "Interrupt " << intNumber << " unhandled.";
	}

}

}
