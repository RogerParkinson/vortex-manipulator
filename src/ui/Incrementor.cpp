/*
 * Incrementor.cpp
 *
 *  Created on: 10/06/2014
 *      Author: roger
 */

#include "Incrementor.h"

Incrementor::Incrementor(int x, int y, int size, int rangeLow, int rangeHigh): Button(x, y, size, " " ) {
	m_rangeLow = rangeLow;
	m_rangeHigh = rangeHigh;
	setText(m_valueString);
}

Incrementor::~Incrementor() {
	// TODO Auto-generated destructor stub
}

void Incrementor::setValue(int value) {
	m_value = value;
	itoa(value,m_valueString,10);
}
void Incrementor::increment() {
	internalIncrement();
	itoa(m_value,m_valueString,10);
	draw();
}
void Incrementor::internalIncrement() {
	if (m_rangeHigh != -1) {
		if (m_value == m_rangeHigh) {
			m_value = m_rangeLow;
			return;
		}
	}
	m_value++;
}
void Incrementor::decrement() {
	internalDeccrement();
	itoa(m_value,m_valueString,10);
	draw();
}
void Incrementor::internalDeccrement() {
	if (m_rangeHigh != -1) {
		if (m_value == m_rangeLow) {
			m_value = m_rangeHigh;
			return;
		}
	}
	m_value--;
}

bool Incrementor::isClicked(TS_Point p) {
	if (!Button::isClicked(p)) {
		// we didn't get clicked
		return false;
	}
	if (p.x > getX()+(getSizex()/2)) {
		increment();
	} else {
		decrement();
	}
	return true;
}
