/*
 * screen.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#define VGA_MONO	0xB8000
#define VGA_COLOR	0xB8000
#define EGA_VGA		0xA0000
#define SCREENROWS	25
#define SCREENCOLS	80
#define SIZESCREEN	SCREENROWS*SCREENCOLS
#define SCREENLIM	VGA_MONO+SIZESCREEN

// Clear the screen to all black.
void clear();
// Write a single character out to the screen.
void putchar(char c);
// Output a null-terminated ASCII string to the monitor and appends a newline character ('\n').
void puts(const char *c);
// Output a null-terminated ASCII string to the monitor and appends a newline character ('\n').
void puts(int c);
// Output a null-terminated ASCII string to the monitor.
void fputs(const char *c);

#endif /* SCREEN_H_ */
