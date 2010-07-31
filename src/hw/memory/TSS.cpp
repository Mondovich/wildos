/*
 * TSS.cpp
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */

#include "TSS.h"
#include "MemoryManager.h"
#include "../../utils/string.h"
#include "../../log/Log.h"

namespace Hardware {

void TSS::setKernelStack(size_t stack) {
	entry.esp0 = stack;
}

}  // namespace Hardware
