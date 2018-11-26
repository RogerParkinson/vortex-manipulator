/*
 * Interval.h
 *
 *  Created on: Oct 7, 2018
 *      Author: roger
 */

#ifndef INTERVAL_H_
#define INTERVAL_H_
#include "Arduino.h"

//#define INTERVAL_DEBUG

class Action {
public:
	Action(){};
	virtual const char* getName() {return PSTR("Action");};
	virtual boolean execute();
	virtual ~Action(){};
};

class Interval {
public:
	virtual void check(long currentTime);
	virtual ~Interval(){};
};

class IntervalCycle: public Interval {
private:
	long m_cycleLimit;
	long m_cycle;
	Action *m_action;

public:
	IntervalCycle(long limit, Action *action);
	virtual void check(long currentTime);
	virtual void reset();
};

class IntervalMillis: public Interval {
private:
	Action *m_action;
	long m_timeInterval;
	long m_triggerTime;

public:
	IntervalMillis(long limit, Action *action);
	virtual void check(long currentTime);
};

class Intervals {
private:
	Interval *m_intervals[10];
	int m_intervalCount=0;

public:
	Intervals(){};
	void check() {
		long currentTime = millis();
#ifdef INTERVAL_DEBUG
		Serial.print("Intervals::check ");
		Serial.println(m_intervalCount);
#endif
		for (int i=0;i<m_intervalCount;i++) {
			m_intervals[i]->check(currentTime);
		}
	}
	void create(long millis, Action *action) {
		Interval *interval = new IntervalMillis(millis,action);
		create(interval);
	}
	void create(Interval *interval) {
		m_intervals[m_intervalCount++] = interval;
	}
	virtual ~Intervals(){};
};

#endif /* INTERVAL_H_ */
