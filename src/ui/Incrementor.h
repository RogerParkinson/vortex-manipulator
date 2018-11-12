/*
 * Incrementor.h
 *
 *  Created on: 10/06/2014
 *      Author: roger
 */

#ifndef INCREMENTOR_H_
#define INCREMENTOR_H_

#include "Button.h"

class Incrementor: public Button {
private:
	char m_valueString[10];
	int m_value;
	int m_rangeLow = 0;
	int m_rangeHigh = -1;
	void internalIncrement();
	void internalDeccrement();

public:
	Incrementor(int x, int y, int size, int rangeLow, int rangeHigh);
	virtual ~Incrementor();
	void setValue(int value);
	void increment();
	void decrement();
	bool isClicked(TS_Point p);

	int getValue() const {
		return m_value;
	}
};

#endif /* INCREMENTOR_H_ */
