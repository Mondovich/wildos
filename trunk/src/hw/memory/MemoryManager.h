/*
 * MemoryManager.h
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include "GDT.h"
#include "TSS.h"
#include "Paging.h"
#include "../../common/types.h"

namespace Hardware {

class MemoryManager {
	GDT gdt;
	TSS tss;
	size_t *frames;
	size_t nframes;
	page_directory_t* kernel_directory;
	page_directory_t* current_directory;
public:
	virtual ~MemoryManager() {};
	static MemoryManager *instance();
	void init();
	void enablePaging(uint32_t memsize);
	void setKernelStack(size_t stack);
private:
	MemoryManager();
	static MemoryManager *instance_;
};

} // namespace Hardware

#endif /* MEMORYMANAGER_H_ */
