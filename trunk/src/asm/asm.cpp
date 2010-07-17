/*
 * asm.cpp
 *
 *  Created on: 09/lug/2010
 *      Author: RaimondoS
 */

#include "../asm/asm.h"
#include "../types.h"

size_t getRegister(REGS reg) {
	size_t result = 0;

	switch (reg) {
	case EAX:
		asm volatile("mov %%eax, %0" : "=r" (result));
		break;
	case EBX:
		asm volatile("mov %%ebx, %0" : "=r" (result));
		break;
	case ESP:
		asm volatile("mov %%esp, %0" : "=r" (result));
		break;
	case CR0:
		asm volatile("mov %%cr0, %0" : "=r" (result));
		break;
	case CR3:
		asm volatile("mov %%cr3, %0" : "=r" (result));
		break;
	default:
		break;
	}
	return result;
}

void setRegister(REGS reg, size_t value) {
	switch (reg) {
	case EAX:
		asm volatile("mov %0, %%eax" : : "r" (value));
		break;
	case EBX:
		asm volatile("mov %0, %%ebx" : : "r" (value));
		break;
	case ESP:
		asm volatile("mov %0, %%esp" : : "r" (value));
		break;
	case CR0:
		asm volatile("mov %0, %%cr0" : : "r" (value));
		break;
	case CR3:
		asm volatile("mov %0, %%cr3" : : "r" (value));
		break;
	default:
		break;
	}
	return;
}
