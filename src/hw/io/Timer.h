/*
 * Timer.h
 *
 *  Created on: 29/lug/2010
 *      Author: RaimondoS
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "../../common/types.h"
#include "../../utils/Callable.h"
#include "../cpu/InterruptHandler.h"

namespace Hardware {

class Timer: public InterruptHandler {
	uint32_t frequency;
	uint32_t tick;
public:
	Timer() {
	}
	;
	virtual ~Timer() {
	}
	;
	void init(uint32_t frequency);
	void call(Registers& regs);
};

}

#endif /* TIMER_H_ */
