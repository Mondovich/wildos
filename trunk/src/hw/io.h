/*
 * io.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#ifndef IO_H_
#define IO_H_

#include "../common/types.h"

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t ind(uint16_t port);

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint16_t value);
void outd(uint16_t port, uint32_t value);

#endif /* IO_H_ */
