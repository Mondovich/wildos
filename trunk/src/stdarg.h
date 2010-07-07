/*
 * stdarg.h
 *
 *  Created on: 02/lug/2010
 *      Author: RaimondoS
 */

#ifndef STDARG_H_
#define STDARG_H_

typedef char *va_list;

#define va_start(ap,p)    (ap = (char *) (&(p) + 1))
#define va_arg(ap,type)   ((type *) (ap += sizeof(type)))[-1]
#define va_end(ap)

#endif /* STDARG_H_ */
