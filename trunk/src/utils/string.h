/*
 * string.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */
#include "../common/types.h"

#ifndef STRING_H_
#define STRING_H_

size_t strlen (const char *s);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dst, const char *src);
char *strncpy (char *dst, const char *src, size_t n);
char *strcat(char *dst, const char *src);
char *strrev(char *s);
char *itoa(uint32_t value, char *str, uint32_t base);

void *memset(void *ptr, int value, size_t num);
extern "C" void *memcpy(void *destination, const void *source, size_t num);
int memcmp(const void * ptr1, const void * ptr2, size_t num);

#endif /* STRING_H_ */
