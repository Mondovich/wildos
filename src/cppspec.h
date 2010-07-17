/*
 * cppspec.h
 *
 *  Created on: 16/lug/2010
 *      Author: RaimondoS
 */

#ifndef CPPSPEC_H_
#define CPPSPEC_H_

#include "types.h"

void *operator new(size_t size);
void *operator new(size_t size, size_t place);
void *operator new(size_t size, bool pageAlign, size_t *physAddr=NULL);
void *operator new[](size_t size);
void *operator new[](size_t size, bool pageAlign, size_t *physAddr=NULL);
void  operator delete(void *p);
void  operator delete[](void *p);

#endif /* CPPSPEC_H_ */
