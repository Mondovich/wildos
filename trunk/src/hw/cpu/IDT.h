/*
 * IDT.h
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */
#include "../../common/types.h"

#ifndef IDT_H_
#define IDT_H_

namespace Hardware {

/*!
 * \struct idt_entry_t
 * \brief Structure describing an interrupt gate.
 */
typedef struct idt_entry_t {
	uint16_t base_low; /*!< The lower 16 bits of the address to jump when this interrupt fires. */
	uint16_t sel; /*!< Kernel segment selector. */
	uint8_t unused; /*!< This must always be zero. */
	uint8_t flags; /*!< More flag. See documentation. */
	uint16_t base_high; /*!< The upper 16 bits of the address to jump to. */
}__attribute__ ((packed)) idt_entry_t;

/*!
 * \struct idt_t
 * \brief Address of the IDT (base/limit).
 */
typedef struct {
	uint16_t limit;
	uint32_t base; /*!< The address of the first element in our idt_entry_t array. */
}__attribute__ ((packed)) idt_t;

/* Extern directives let us access the addresses of our ASM ISR handlers */

extern "C" void isr0(void); //0 - Division by zero exception
extern "C" void isr1(void); //1 - Debug exception
extern "C" void isr2(void); //2 - Non maskable interrupt
extern "C" void isr3(void); //3 - Breakpoint exception
extern "C" void isr4(void); //4 - 'Into detected overflow'
extern "C" void isr5(void); //5 - Out of bounds exception
extern "C" void isr6(void); //6 - Invalid opcode exception
extern "C" void isr7(void); //7 - No coprocessor exception
extern "C" void isr8(void); //8 - Double fault (pushes an error code)
extern "C" void isr9(void); //9 - Coprocessor segment overrun
extern "C" void isr10(void); //10 - Bad TSS (pushes an error code)
extern "C" void isr11(void); //11 - Segment not present (pushes an error code)
extern "C" void isr12(void); //12 - Stack fault (pushes an error code)
extern "C" void isr13(void); //13 - General protection fault (pushes an error code)
extern "C" void isr14(void); //14 - Page fault (pushes an error code)
extern "C" void isr15(void); //15 - Unknown interrupt exception
extern "C" void isr16(void); //16 - Coprocessor fault
extern "C" void isr17(void); //17 - Alignment check exception
extern "C" void isr18(void); //18 - Machine check exception
extern "C" void isr19(void); //19-31 - Reserved
extern "C" void isr20(void); //19-31 - Reserved
extern "C" void isr21(void); //19-31 - Reserved
extern "C" void isr22(void); //19-31 - Reserved
extern "C" void isr23(void); //19-31 - Reserved
extern "C" void isr24(void); //19-31 - Reserved
extern "C" void isr25(void); //19-31 - Reserved
extern "C" void isr26(void); //19-31 - Reserved
extern "C" void isr27(void); //19-31 - Reserved
extern "C" void isr28(void); //19-31 - Reserved
extern "C" void isr29(void); //19-31 - Reserved
extern "C" void isr30(void); //19-31 - Reserved
extern "C" void isr31(void); //19-31 - Reserved
extern "C" void isr128(void);
extern "C" void irq0(void);
extern "C" void irq1(void);
extern "C" void irq2(void);
extern "C" void irq3(void);
extern "C" void irq4(void);
extern "C" void irq5(void);
extern "C" void irq6(void);
extern "C" void irq7(void);
extern "C" void irq8(void);
extern "C" void irq9(void);
extern "C" void irq10(void);
extern "C" void irq11(void);
extern "C" void irq12(void);
extern "C" void irq13(void);
extern "C" void irq14(void);
extern "C" void irq15(void);

extern "C" void idt_flush(uint32_t addr);

class IDT {
	idt_t addr;
	idt_entry_t entries[256];
public:
	IDT();
	virtual ~IDT();
	void init();
private:
	void setGate(int num, uint32_t base, uint16_t sel, uint8_t flags);
};

}

#endif /* IDT_H_ */
