/*
 * iostream
 *
 *  Created on: 22/lug/2010
 *      Author: RaimondoS
 */

#ifndef IOSTREAM_H_
#define IOSTREAM_H_

#include "ostream.h"

namespace std {

class ConsoleStream: public ostream {
public:
	ConsoleStream();
	virtual ~ConsoleStream();

	ostream &put(char);
	ostream &write(const char*);
	ostream &flush(ostream &);
private:
};

class SerialStream: public ostream {
public:
	SerialStream();
	virtual ~SerialStream();

//	ostream &put(char);
	ostream &flush(ostream &);
private:
};
//
extern ConsoleStream cout;
extern SerialStream clog;
extern SerialStream cerr;

} // namespace std


#endif /* IOSTREAM_H_ */
