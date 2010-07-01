/*
 * string.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */
#include "../types.h"

#ifndef STRING_H_
#define STRING_H_

size_t strlen (const char *s);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dst, const char *src);
char *strncpy (char *dst, const char *src, size_t n);
char *strcat(char *dst, const char *src);
char *strrev(char *s);
char *itoa(int value, char *str, int base);

#endif /* STRING_H_ */
