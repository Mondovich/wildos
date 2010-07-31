/*
 * screen.cpp
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#include "Screen.h"
#include "../io/IOManager.h"
#include "../../utils/string.h"
#include "../../common/types.h"
#include "../../common/stdarg.h"

namespace Hardware {

// initialize pointer
Screen* Screen::instance_ = NULL;

Screen::Screen() {
	this->base_ = 10;
	video_memory = (uint16_t *) VGA_MONO;
	kx = 0;
	ky = 0;
}
Screen::~Screen() {

}

Screen* Screen::instance() {
	if (!instance_)
		instance_ = new Screen;
	return instance_;
}
//
//Hardware::Screen &Screen::operator<<(const Hardware::Base& base) {
//	this->base_ = base.getBase();
//	return (*this);
//}

// Updates the hardware cursor.
void Screen::move_cursor() {
	// The screen is 80 characters wide...
	uint16_t cursorLocation = ky * SCREENCOLS + kx;
	IOManager::instance()->outb(0x3D4, 14); // Tell the VGA board we are setting the high cursor byte.
	IOManager::instance()->outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
	IOManager::instance()->outb(0x3D4, 15); // Tell the VGA board we are setting the low cursor byte.
	IOManager::instance()->outb(0x3D5, cursorLocation); // Send the low cursor byte.
}
// Clear the screen to all black.
void Screen::clear() {
	// Get a space character with the default colour attributes.
	uint8_t attributeByte = (Black << 4) | (White & 0x0F);
	uint16_t blank = 0x20 /* space */| (attributeByte << 8);

	for (int i = 0; i < SCREENSIZE; i++)
		video_memory[i] = blank;

	kx = ky = 0;
	return;
}
// Scrolls the text on the screen up by n line.
void Screen::scrollup(int n) {
	// Get a space character with the default colour attributes.
	uint8_t attributeByte = (Black << 4) | (White & 0x0F);
	uint16_t blank = 0x20 /* space */| (attributeByte << 8);

	// Move the current text chunk that makes up the screen
	// back in the buffer by a line
	int i;
	for (i = 0; i < SCREENSIZE; i++) {
		if (i < SCREENSIZE - n * SCREENCOLS) {
			video_memory[i] = video_memory[i + n * SCREENCOLS];
		} else {
			video_memory[i] = blank;
		}
	}

	// The cursor should now be on the last line.
	ky = SCREENROWS - n;
}

//void Screen::write(const char *c, Color foreColor, Color backColor) {
//	while (*c)
//		putchar(*c++, foreColor, backColor);
//	return;
//}
// Write a single character out to the screen.
void Screen::putchar(char c, Color foreColor, Color backColor) {
	// The attribute byte is made up of two nibbles - the lower being the
	// foreground colour, and the upper the background colour.
	uint8_t attributeByte = (backColor << 4) | (foreColor & 0x0F);
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

	if (ky > SCREENROWS - 1) {
		scrollup(ky - (SCREENROWS - 1));
	}

	// Move the hardware cursor.
	move_cursor();

	return;
}

} // namespace Hardware
