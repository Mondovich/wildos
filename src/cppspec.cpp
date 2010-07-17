/*
 * cppspec.cpp
 *
 *  Created on: 16/lug/2010
 *      Author: RaimondoS
 */

#include "types.h"
#include "hw/kheap.h"

// Required to get G++ to link without libstdc++
void *__gxx_personality_v0 = NULL;
// Required for GCC
void *__dso_handle;

extern "C" void __cxa_atexit(void(* f)(void *), void *p, void *d) {
}

void *operator new(size_t size) {
	return kmalloc(size);
}
;
void *operator new(size_t size, size_t place) {
}
;
void *operator new(size_t size, bool pageAlign, size_t *physAddr = NULL) {
	return kmalloc(size, pageAlign, physAddr);
}
;
void *operator new[](size_t size) {
	return kmalloc(size);
}
;
void *operator new[](size_t size, bool pageAlign, size_t *physAddr = NULL) {
	return kmalloc(size, pageAlign, physAddr);
}
;
void operator delete(void *p) {
	kfree(p);
}
;
void operator delete[](void *p) {
	kfree(p);
}
;

