/*
 * iostream.cpp
 *
 *  Created on: 22/lug/2010
 *      Author: RaimondoS
 */

#include "iostream.h"
#include "../common/types.h"
#include "../hw/screen.h"
#include "../hw/io/SerialIO.h"
#include "../utils/string.h"
#include "../log/Log.h"

using namespace Hardware;


namespace std {

ConsoleStream::ConsoleStream() :
	ostream::basic_ostream() {
}
ConsoleStream::~ConsoleStream() {
}

ostream &ConsoleStream::put(char c) {
	Screen::instance()->putchar(c, foreColor, backColor);
	return *this;
}

ostream &ConsoleStream::write(const char *in) {
	Log::video(in);
	return ostream::write(in);
}

ostream &ConsoleStream::flush(ostream &) {
	for (int i = 0; buf[i] && i < 256; ++i) {
		Screen::instance()->putchar(buf[i], foreColor, backColor);
	}
	clear();
	return *this;
}

SerialStream::SerialStream() :
	ostream::basic_ostream() {
}
SerialStream::~SerialStream() {
}

//ostream &SerialStream::put(char c) {
//	SerialIO::instance()->write(c);
//	return *this;
//}

ostream &SerialStream::flush(ostream &) {
	for (int i = 0; buf[i] && i < 256; ++i) {
		SerialIO::instance()->write(buf[i]);
	}
	clear();
	return *this;
}

ConsoleStream std::cout = ConsoleStream();
SerialStream std::clog = SerialStream();
SerialStream std::cerr = SerialStream();

} // namespace std
