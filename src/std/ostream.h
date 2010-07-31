/*
 * ostream
 *
 *  Created on: 22/lug/2010
 *      Author: RaimondoS
 */
#ifndef OSTREAM_H_
#define OSTREAM_H_

#include "../hw/video/screen.h"
#include "../hw/memory/MemoryManager.h"
#include "../utils/string.h"

using namespace Hardware;

namespace std {

template<typename _CharT>
class basic_ostream {
protected:
	_CharT buf[255];
	int _index;
	int _base;
	Screen::Color foreColor;
	Screen::Color backColor;
public:
	basic_ostream() {
		_base = 10;
		_index = 0;
		foreColor = Screen::White;
		backColor = Screen::Black;
	}
	;
	virtual ~basic_ostream() {
	}
	;

	basic_ostream<_CharT> &operator<<(const _CharT *str) {
		write(str, foreColor, backColor);
		return (*this);
	}
	;
	basic_ostream<_CharT> &operator<<(const _CharT c) {
		put(c);
		return (*this);
	}
	;
	basic_ostream<_CharT> &operator<<(uint8_t i) {
		char buf[16];
		itoa(i, buf, _base);
		write(buf, foreColor, backColor);
		return (*this);

	}
	;
	basic_ostream<_CharT> &operator<<(uint16_t i) {
		char buf[16];
		itoa(i, buf, _base);
		write(buf, foreColor, backColor);
		return (*this);

	}
	;
	basic_ostream<_CharT> &operator<<(uint32_t i) {
		char buf[16];
		itoa(i, buf, _base);
		write(buf, foreColor, backColor);
		return (*this);

	}
	;
	basic_ostream<_CharT> &operator<<(Screen::Color color) {
		foreColor = color;
		return *this;
	}
	;
	basic_ostream<_CharT> &operator<<(basic_ostream<_CharT>& (*__pf)(basic_ostream<_CharT>&)) {
		__pf(*this);
		return *this;
	}
	;

	int getBase() const {
		return _base;
	}

	void setBase(int __base) {
		this->_base = __base;
	}

	virtual basic_ostream<_CharT> &clear() {
		_index = 0;
		memset(buf, 0, 256);
		return *this;
	}
	;

	virtual basic_ostream<_CharT> &flush(basic_ostream<_CharT> &) = 0;

	virtual basic_ostream<_CharT> &put(_CharT c) {
		buf[_index++] = c;
		if (_index > 256) {
			_index = 0;
			flush(*this);
		}
		return *this;
	}
	;

	virtual basic_ostream<_CharT> &write(const _CharT* in) {
		while (*in) {
			put(*in++);
		}
		return *this;
	}
	;
	virtual basic_ostream<_CharT> &write(const _CharT* in, Screen::Color foreColor,
			Screen::Color backColor) {
		this->foreColor = foreColor;
		this->backColor = backColor;
		write(in);
		return *this;
	}
	;

};

typedef basic_ostream<char> ostream;

template<typename _CharT>
inline basic_ostream<_CharT>&
hex(basic_ostream<_CharT>& __base) {
	__base.setBase(16);
	return __base;
}

template<typename _CharT>
inline basic_ostream<_CharT>&
dec(basic_ostream<_CharT>& __base) {
	__base.setBase(10);
	return __base;
}

template<typename _CharT>
basic_ostream<_CharT>&
endl(basic_ostream<_CharT>& __os) {
	return __os.flush(__os.put('\n'));
}

}

#endif /* OSTREAM_H_ */
