/*
 * io.cpp
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */
#include "io.h"

uint8_t inb(uint16_t port) {
	uint8_t result;
	asm ("inb %1, %0" : "=a"(result) : "Nd"(port));
	return result;
}
uint16_t inw(uint16_t port) {
	uint16_t result;
	asm ("inw %1, %0" : "=a"(result) : "Nd"(port));
	return result;
}
uint32_t ind(uint16_t port) {
	uint32_t result;
	asm ("inl %1, %0" : "=a"(result) : "Nd"(port));
	return result;
}

void outb(uint16_t port, uint8_t value) {
	asm ("outb %0, %1" :: "a"(value), "Nd"(port));
	return;
}
void outw(uint16_t port, uint16_t value) {
	asm ("outw %0, %1" :: "a"(value), "Nd"(port));
	return;
}
void outd(uint16_t port, uint32_t value) {
	asm ("outl %0, %1" :: "a"(value), "Nd"(port));
	return;
}
