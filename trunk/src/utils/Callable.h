/*
 * Callable.h
 *
 *  Created on: 29/lug/2010
 *      Author: RaimondoS
 */

#ifndef CALLABLE_H_
#define CALLABLE_H_

namespace std {

template <typename V>
class Callable {
protected:
	Callable() {};
	virtual ~Callable() {};
	virtual V call() = 0;
};

}

#endif /* CALLABLE_H_ */
