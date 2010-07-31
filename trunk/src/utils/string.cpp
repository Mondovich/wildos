/*
 * string.cpp
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */
#include "string.h"
#include "../common/types.h"
#include "../utils/utils.h"

size_t strlen(const char *s) {
	uint16_t i = 0;
	while (*s++)
		i++;
	return i;
}

int strcmp(const char *s1, const char *s2) {
	for (; *s1 != 0 && *s2 != 0; s1++, s2++)
		if (*s1 != *s2) {
			return s1 - s2;
		}
	return 0;
}

char *strcpy(char *dst, const char *src) {
	char *res = dst;
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return res;
}

char *strncpy(char *dst, const char *src, size_t n) {
	char *res = dst;
	uint16_t i = 0;
	for (; i < n && src[i] != 0; ++i) {
		dst[i] = src[i];
	}
	for (; i < n; ++i) {
		dst[i] = 0;
	}
	return res;
}

char *strcat(char *dst, const char *src) {
	char *res = dst;
	while (*dst)
		*dst++;

	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return res;

}

char *strrev(char *s) {
	for (uint16_t j = 0, i = strlen(s) - 1; j < i; ++j, --i) {
		char tmp = s[j];
		s[j] = s[i];
		s[i] = tmp;
	}
	return s;
}

char *itoa(uint32_t value, char *str, uint32_t base) {
	int tmp;
	int i = 0;

	do {
		tmp = value % base;
		str[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'A' - 10);
	} while (value /= base);
	str[i--] = 0;

	return strrev(str);
}

void *memset(void *ptr, int value, size_t num) {
        char *p = (char *) ptr;
        for (; num != 0; --num)
                *p++ = value;
        return ptr;
}

void *memcpy(void *destination, const void *source, size_t num) {
        const char *sp = (const char *) source;
        char *dp = (char *) destination;
        for (; num != 0; num--)
                *dp++ = *sp++;
        return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
        const char *p1 = (const char *) ptr1;
        const char *p2 = (const char *) ptr2;
        for (size_t i = 0; i < num; ++i) {
                if (*p1 != *p2)
                        return *p1 - *p2;
        }
        return 0;
}
