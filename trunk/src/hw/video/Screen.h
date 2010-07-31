/*
 * screen.h
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#include "../../common/types.h"
#include "../../utils/string.h"

#ifndef SCREEN_H_
#define SCREEN_H_

#define VGA_MONO	0xB8000
#define VGA_COLOR	0xB8000
#define EGA_VGA		0xA0000
#define SCREENROWS	25
#define SCREENCOLS	80
#define SCREENSIZE	SCREENROWS*SCREENCOLS
#define SCREENLIM	VGA_MONO+SCREENSIZE

namespace Hardware {

class Screen {
	int base_;
public:
	enum Color {
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Orange = 6,
		LightGrey = 7,
		DarkGrey = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};
	virtual ~Screen();
	static Screen *instance();
	void clear();
	void putchar(char c, Color foreColor, Color backColor);
//	void write(const char*, Color foreColor, Color backColor);

private:
	Screen();
	static Screen *instance_;

	void move_cursor();
	uint16_t *video_memory;
	int8_t kx;
	int8_t ky;

	void Screen::scrollup(int n);

};

} // namespace Hardware

#endif /* SCREEN_H_ */
