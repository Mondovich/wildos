/*
 * Multiboot.cpp
 *
 *  Created on: 16/lug/2010
 *      Author: RaimondoS
 */

#include "multiboot.h"

Multiboot::Multiboot() {}
Multiboot::~Multiboot() {}

Multiboot::Multiboot(struct multiboot_t *mboot_ptr) {
	this->mboot_ptr = mboot_ptr;
}


