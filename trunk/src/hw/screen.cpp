/*
 * screen.cpp
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#include "screen.h"
#include "../utils/string.h"
#include "../types.h"

uint16_t *video_memory = (uint16_t *) VGA_MONO;
int8_t kx = 0;
int8_t ky = 0;

// Clear the screen to all black.
void clear() {
	for (int i = 0; i < SIZESCREEN; i++)
		video_memory[i] = 0;

	kx = ky = 0;
	return;
}
// Scrolls the text on the screen up by n line.
void scrollup(int n) {
	uint16_t *video, *tmp;

	for (video = video_memory; video < (uint16_t *) SCREENLIM; video += 2) {
		tmp = video + n * SCREENCOLS * 2;

		if (tmp < (uint16_t *) SCREENLIM) {
			*video = *tmp;
			*(video + 1) = *(tmp + 1);
		} else {
			*video = 0;
			*(video + 1) = 0x07;
		}
	}

	ky -= n;
	if (ky < 0)
		ky = 0;
	return;
}
// Write a single character out to the screen.
void putchar(char c) {
	// The background colour is black (0), the foreground is white (15).
	uint8_t backColour = 0;
	uint8_t foreColour = 15;

	// The attribute byte is made up of two nibbles - the lower being the
	// foreground colour, and the upper the background colour.
	uint8_t attributeByte = (backColour << 4) | (foreColour & 0x0F);
	// The attribute byte is the top 8 bits of the word we have to send to the
	// VGA board.
	uint16_t attribute = attributeByte << 8;
	uint16_t *location;

	switch (c) {
	case 8: /* BS */
		if (kx) {
			*(video_memory + 1) = 0;
			kx--;
		}
		break;

	case 9: /* TAB */
		kx = kx + 4 - (kx % 4);
		break;

	case 10: /* CR-NL */
		kx = 0;
		ky++;
		break;

	case 13: /* CR */
		kx = 0;
		break;

	default:
		location = video_memory + (ky * SCREENCOLS + kx);
		*location = c | attribute;

		kx++;
		if (kx > SCREENCOLS - 1) {
			kx = 0;
			ky++;
		}
		break;
	}

	if (ky > SCREENROWS)
		scrollup(ky - 24);

	return;
}
// Output a null-terminated ASCII string to the monitor
// and appends a newline character ('\n').
void puts(const char *c) {
	fputs(c);
	putchar('\n');
	return;
}
void puts(int c){
	char *n;
	itoa(c, n, 10);
	puts(n);
}
// Output a null-terminated ASCII string to the monitor
void fputs(const char *c) {
	while (*c)
		putchar(*c++);
	return;
}
