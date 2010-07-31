/*
 * kernel.h
 *
 *  Created on: 16/giu/2010
 *      Author: RaimondoS
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "../hw/video/Screen.h"
#include "../hw/memory/MemoryManager.h"
#include "../hw/cpu/InterruptManager.h"
#include "../hw/io/Timer.h"

namespace Kernel {

class Kernel {
public:
	virtual ~Kernel();
	void run();
	static Kernel *instance();
private:
	Kernel();
	static Kernel *instance_;
	Hardware::Screen *screen;
	Hardware::MemoryManager *memoryManager;
	Hardware::InterruptManager *interruptManager;
	Hardware::Timer *timer;
};

} // namespace Kernel

#endif /* KERNEL_H_ */
