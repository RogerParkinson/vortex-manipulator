/*
 * Interval.h
 *
 *  Created on: Oct 7, 2018
 *      Author: roger
 */

#ifndef INTERVAL_H_
#define INTERVAL_H_
#include "Arduino.h"

class Action {
public:
	Action(){};
	virtual const char* getName() {return PSTR("Action");};
	virtual void execute();
//	virtual ~Action();
};

class Interval {
private:
	Action *m_action;
	long m_timeInterval;
	long m_triggerTime;
	static Interval *m_intervals[10];
	static int m_intervalCount;

public:
	Interval(long millis, Action *action);
	void check(long currentTime);
	virtual ~Interval();
};

class Intervals {
private:
	Interval *m_intervals[10];
	int m_intervalCount=0;

public:
	Intervals(){};
	void check() {
//		Serial.print("Intervals::check m_intervalCount ");
//		Serial.println(m_intervalCount);
		long currentTime = millis();
		for (int i=0;i<m_intervalCount;i++) {
			m_intervals[i]->check(currentTime);
		}
	}
	void create(long millis, Action *action) {
		Interval *interval = new Interval(millis,action);
		m_intervals[m_intervalCount++] = interval;
	}
	virtual ~Intervals(){};
};

#endif /* INTERVAL_H_ */
