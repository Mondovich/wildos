/*
 * Multiboot.cpp
 *
 *  Created on: 16/lug/2010
 *      Author: RaimondoS
 */

#include "multiboot.h"

Multiboot* Multiboot::instance_ = NULL;

Multiboot::Multiboot() {
}
Multiboot::~Multiboot() {
}

Multiboot *Multiboot::instance() {
	if (!instance_)
		instance_ = new Multiboot;
	return instance_;
}
