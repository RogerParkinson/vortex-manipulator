/*
 * Interval.cpp
 *
 *  Created on: Oct 7, 2018
 *      Author: roger
 */

#include "Interval.h"

IntervalCycle::IntervalCycle(long limit, Action *action) {
	m_cycleLimit = limit;
	m_cycle = 0L;
	m_action = action;
}


void IntervalCycle::check(long currentTime) {
	if (m_cycle++ > m_cycleLimit) {
		if (m_action->execute()) {
			m_cycle = 0L;
		}
	}
}
void IntervalCycle::reset() {
	m_cycle = 0L;
}

IntervalMillis::IntervalMillis(long limit, Action *action) {
	m_timeInterval = limit;
	m_action = action;
	m_triggerTime = millis() + m_timeInterval;
	m_action = action;
}


void IntervalMillis::check(long currentTime) {
	if (m_triggerTime < currentTime) {
		m_action->execute();
		m_triggerTime = currentTime + m_timeInterval;
	}
}


