/*
 * utils.h
 *
 *  Created on: 05/lug/2010
 *      Author: RaimondoS
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "../stdarg.h"

#define PANIC(msg)      panic (__FILE__, __LINE__, msg);
#define ASSERT(b)       ((b) ? (void) 0 : panic_assert (__FILE__, __LINE__, #b))
#define LOG(msg, ...)	(							\
	va_list va_args;								\
	printk ("LOG: %s:%d - ", __FILE__, __LINE__);	\
	printk (msg, va_args);							\
	printk ("\n");\
)

void panic (const char *file, int line, char *msg);
void panic_assert (const char *file, int line, char *msg);

#endif /* UTILS_H_ */
