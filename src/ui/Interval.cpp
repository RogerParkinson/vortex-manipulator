/*
 * Interval.cpp
 *
 *  Created on: Oct 7, 2018
 *      Author: roger
 */

#include "Interval.h"

Interval::Interval(long timeInterval, Action *action) {
	m_timeInterval = timeInterval;
	m_action = action;
	m_triggerTime = millis() + m_timeInterval;
}

void Interval::check(long currentTime) {
	if (m_triggerTime < currentTime) {
//		Serial.print("firing ");
//		Serial.print(m_action->getName());
//		Serial.print(" at ");
//		Serial.println(currentTime);
		m_action->execute();
		m_triggerTime = currentTime + m_timeInterval;
	}
}

Interval::~Interval() {
	// TODO Auto-generated destructor stub
}

