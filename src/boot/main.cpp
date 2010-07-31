/*
 * main.c
 *
 *  Created on: 16/lug/2010
 *      Author: RaimondoS
 */

#include "../common/types.h"
#include "../kernel/kernel.h"
#include "../hw/screen.h"
#include "../std/iostream.h"
#include "multiboot.h"

extern uint32_t start_ctors;
extern uint32_t end_ctors;
extern uint32_t end;

extern "C" void __main(void) {
	// Constructor list is defined in the linker script.
	uint32_t *iterator = (uint32_t *) &start_ctors;
	while (iterator < (uint32_t *) &end_ctors) {
		void (*fp)(void) = ( void (*)(void) )*iterator;
		fp();
		iterator += 4;
	}
}

extern "C" int _main(struct multiboot_t *mboot_ptr, size_t initial_stack) {

	Multiboot::instance()->init(mboot_ptr);

	Kernel::Kernel::instance()->run();

	return 0;
}
