/*
 * Prova.h
 *
 *  Created on: 16/lug/2010
 *      Author: RaimondoS
 */

#ifndef PROVA_H_
#define PROVA_H_



class Prova {
	int i;
public:

	Prova();
	virtual ~Prova();
    int getI() const
    {
        return i;
    }

    void setI(int i = 0)
    {
        this->i = i;
    }

};



#endif /* PROVA_H_ */
