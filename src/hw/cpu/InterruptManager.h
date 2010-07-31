/*
 * InterruptManager.h
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */

#ifndef INTERRUPTMANAGER_H_
#define INTERRUPTMANAGER_H_

#include "IDT.h"
#include "InterruptHandler.h"

namespace Hardware {


/*!
 * \struct registers_t
 * \brief Structure describing registers used by the ISR handler.
 */
typedef struct {
	uint32_t ds; /*!< Data segment selector */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /*!< Pushed by pusha */
	uint32_t int_no, err_code; /*!< Interrupt number and error code (if applicable) */
	uint32_t eip, cs, eflags, useresp, ss; /*!< Pushed by the processor automatically */
} __attribute__((packed)) registers_t;

class InterruptManager {
	bool enabled;
	InterruptHandler *handlers[256];
	IDT idt;
public:
	/* A few defines to make life a little easier */
	enum ISR {
		ISR0,
		ISR1,
		ISR2,
		ISR3,
		ISR4,
		ISR5,
		ISR6,
		ISR7,
		ISR8,
		ISR9,
		ISR10,
		ISR11,
		ISR12,
		ISR13,
		ISR14,
		ISR15,
		ISR16,
		ISR17,
		ISR18,
		ISR19,
		ISR20,
		ISR21,
		ISR22,
		ISR23,
		ISR24,
		ISR25,
		ISR26,
		ISR27,
		ISR28,
		ISR29,
		ISR30,
		ISR31,
		IRQ0 = 32,
		IRQ1 = 33,
		IRQ2 = 34,
		IRQ3 = 35,
		IRQ4 = 36,
		IRQ5 = 37,
		IRQ6 = 38,
		IRQ7 = 39,
		IRQ8 = 40,
		IRQ9 = 41,
		IRQ10 = 42,
		IRQ11 = 43,
		IRQ12 = 44,
		IRQ13 = 45,
		IRQ14 = 46,
		IRQ15 = 47,
		ISR128 = 128
	};

	virtual ~InterruptManager() {
	}
	;
	static InterruptManager *instance();
	void init();
	void setInterruptHandler(ISR, InterruptHandler *);
	static void handler(Registers&);
	bool areEnabled() const {
		return enabled;
	}

	void setEnabled(bool enabled) {
		this->enabled = enabled;
		if (enabled) {
			asm volatile ("sti");
		} else {
			asm volatile ("cli");
		}
	}

private:
	InterruptManager() {
	}
	;
	static InterruptManager *instance_;
};

}

#endif /* INTERRUPTMANAGER_H_ */
