/*
 * Interval.cpp
 *
 *  Created on: Oct 7, 2018
 *      Author: roger
 */

#include "Interval.h"

//Interval::Interval(long timeInterval, Action *action) {
//}
//
//
//void Interval::check(long currentTime) {
//}
//
//Interval::~Interval() {
//	// TODO Auto-generated destructor stub
//}

IntervalCycle::IntervalCycle(long limit, Action *action) {
	m_cycleLimit = limit;
	m_cycle = 0L;
	m_action = action;
}


void IntervalCycle::check(long currentTime) {
	if (m_cycle++ > m_cycleLimit) {
		m_action->execute();
		m_cycle = 0;
	}
}

//IntervalCycle::~IntervalCycle() {
//	// TODO Auto-generated destructor stub
//}
IntervalMillis::IntervalMillis(long limit, Action *action) {
	m_timeInterval = limit;
	m_action = action;
	m_triggerTime = millis() + m_timeInterval;
	m_action = action;
}


void IntervalMillis::check(long currentTime) {
	if (m_triggerTime < currentTime) {
//		Serial.print("firing ");
//		Serial.print(m_action->getName());
//		Serial.print(" at ");
//		Serial.println(currentTime);
		m_action->execute();
		m_triggerTime = currentTime + m_timeInterval;
	}
}

//IntervalMillis::~IntervalMillis() {
//	// TODO Auto-generated destructor stub
//}

