/*
 * screen.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#include "../common/types.h"
#include "../utils/string.h"

#ifndef SCREEN_H_
#define SCREEN_H_

#define VGA_MONO	0xB8000
#define VGA_COLOR	0xB8000
#define EGA_VGA		0xA0000
#define SCREENROWS	25
#define SCREENCOLS	80
#define SCREENSIZE	SCREENROWS*SCREENCOLS
#define SCREENLIM	VGA_MONO+SCREENSIZE

void clear();
void putchar(char c);
void puts(const char *c);
void puts(int c);
void fputs(const char *c);
int printk(char *format, ...);

#endif /* SCREEN_H_ */
