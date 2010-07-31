/*
 * SerialIO.h
 *
 *  Created on: 27/lug/2010
 *      Author: RaimondoS
 */

#ifndef SERIALIO_H_
#define SERIALIO_H_

#define PORT 0x3f8   /* COM1 */

namespace Hardware {

class SerialIO {
	static SerialIO *instance_;
public:
	virtual ~SerialIO();
	static SerialIO *instance();

	void init();

	int received();
	char read();
	int isTransmitEmpty();
	void write(char a);
private:
	SerialIO();
};

} // namespace Hardware


#endif /* SERIALIO_H_ */
