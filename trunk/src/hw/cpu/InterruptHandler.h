/*
 * InterruptHandler.h
 *
 *  Created on: 30/lug/2010
 *      Author: RaimondoS
 */

#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

class Registers {
public:
	uint32_t ds; /*!< Data segment selector */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /*!< Pushed by pusha */
	uint32_t int_no, err_code; /*!< Interrupt number and error code (if applicable) */
	uint32_t eip, cs, eflags, useresp, ss; /*!< Pushed by the processor automatically */
};

namespace Hardware {

class InterruptHandler {
public:
	virtual ~InterruptHandler() {};
	virtual void call(Registers& regs) = 0;
protected:
	InterruptHandler() {};
};

}

#endif /* INTERRUPTHANDLER_H_ */
