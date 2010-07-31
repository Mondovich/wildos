/*
 * TSS.h
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */

#ifndef TSS_H_
#define TSS_H_

#include "../../common/types.h"

namespace Hardware {

// A struct describing a Task State Segment.
typedef struct {
	size_t prev_tss; // The previous TSS - if we used hardware task switching this would form a linked list.
	size_t esp0; // The stack pointer to load when we change to kernel mode.
	size_t ss0; // The stack segment to load when we change to kernel mode.
	size_t esp1; // Unused...
	size_t ss1;
	size_t esp2;
	size_t ss2;
	size_t cr3;
	size_t eip;
	size_t eflags;
	size_t eax;
	size_t ecx;
	size_t edx;
	size_t ebx;
	size_t esp;
	size_t ebp;
	size_t esi;
	size_t edi;
	size_t es; // The value to load into ES when we change to kernel mode.
	size_t cs; // The value to load into CS when we change to kernel mode.
	size_t ss; // The value to load into SS when we change to kernel mode.
	size_t ds; // The value to load into DS when we change to kernel mode.
	size_t fs; // The value to load into FS when we change to kernel mode.
	size_t gs; // The value to load into GS when we change to kernel mode.
	size_t ldt; // Unused...
	uint16_t trap;
	uint16_t iomap_base;

}__attribute__((packed)) tss_entry_t;

extern "C" void tssFlush();

class TSS {
public:
	tss_entry_t entry;
	TSS() {};
	virtual ~TSS() {};
	void setKernelStack(size_t stack);
private:
};

}  // namespace Hardware

#endif /* TSS_H_ */
