/*
 * IOManager.h
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */

#include "../../common/types.h"

#ifndef IOMANAGER_H_
#define IOMANAGER_H_

namespace Hardware {

class IOManager {
public:
	virtual ~IOManager();
	static IOManager *instance();
	uint8_t inb(uint16_t port);
	uint16_t inw(uint16_t port);
	uint32_t ind(uint16_t port);

	void outb(uint16_t port, uint8_t value);
	void outw(uint16_t port, uint16_t value);
	void outd(uint16_t port, uint32_t value);
private:
	IOManager();
	static IOManager *instance_;
};

}

#endif /* IOMANAGER_H_ */
