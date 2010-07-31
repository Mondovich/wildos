/*
 * IOManager.cpp
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */

#include "IOManager.h"

namespace Hardware {

IOManager *IOManager::instance_ = NULL;

IOManager::IOManager() {
	// TODO Auto-generated constructor stub

}

IOManager::~IOManager() {
	// TODO Auto-generated destructor stub
}

IOManager *IOManager::instance() {
	if (!instance_)
		instance_ = new IOManager;
	return instance_;
}

uint8_t IOManager::inb(uint16_t port) {
	uint8_t result;
	asm ("inb %1, %0" : "=a"(result) : "Nd"(port));
	return result;
}
uint16_t IOManager::inw(uint16_t port) {
	uint16_t result;
	asm ("inw %1, %0" : "=a"(result) : "Nd"(port));
	return result;
}
uint32_t IOManager::ind(uint16_t port) {
	uint32_t result;
	asm ("inl %1, %0" : "=a"(result) : "Nd"(port));
	return result;
}

void IOManager::outb(uint16_t port, uint8_t value) {
	asm ("outb %0, %1" :: "a"(value), "Nd"(port));
	return;
}
void IOManager::outw(uint16_t port, uint16_t value) {
	asm ("outw %0, %1" :: "a"(value), "Nd"(port));
	return;
}
void IOManager::outd(uint16_t port, uint32_t value) {
	asm ("outl %0, %1" :: "a"(value), "Nd"(port));
	return;
}

}
