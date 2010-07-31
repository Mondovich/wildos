/*
 * SerialIO.cpp
 *
 *  Created on: 27/lug/2010
 *      Author: RaimondoS
 */

#include "SerialIO.h"
#include "IOManager.h"

namespace Hardware {

SerialIO *SerialIO::instance_ = NULL;

SerialIO::SerialIO() {
	init();
}

SerialIO::~SerialIO() {
	// TODO Auto-generated destructor stub
}

SerialIO *SerialIO::instance() {
	if (!instance_)
		instance_ = new SerialIO;
	return instance_;
}

void SerialIO::init() {
	IOManager::instance()->outb(PORT + 1, 0x00); // Disable all interrupts
	IOManager::instance()->outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
	IOManager::instance()->outb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
	IOManager::instance()->outb(PORT + 1, 0x00); //                  (hi byte)
	IOManager::instance()->outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
	IOManager::instance()->outb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
	IOManager::instance()->outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int SerialIO::received() {
	return IOManager::instance()->inb(PORT + 5) & 1;
}

char SerialIO::read() {
	while (received() == 0)
		;

	return IOManager::instance()->inb(PORT);
}

int SerialIO::isTransmitEmpty() {
	return IOManager::instance()->inb(PORT + 5) & 0x20;
}

void SerialIO::write(char a) {
	while (isTransmitEmpty() == 0)
		;

	IOManager::instance()->outb(PORT, a);
}

} // namespace Hardware

