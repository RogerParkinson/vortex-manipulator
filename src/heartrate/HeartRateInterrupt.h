/*
 * HeartRateInterrupt.h
 *
 *  Created on: 14/04/2013
 *      Author: roger
 */

#ifndef HEARTRATEINTERRUPT_H_
#define HEARTRATEINTERRUPT_H_
#include "Arduino.h"
#include "../Configuration.h"
//#include "../ui/Interval.h"
#include <wiring.h>

#define PREVBUFSIZE 30
#define SLOPE 8
#define HIGH_CUTOFF 510
#define LOW_CUTOFF 480
#define POINCARE_SIZE 50
//#define HEARTRATEINTERRUPT_DEBUG


// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class Poincare {
	float data[POINCARE_SIZE];
	int count = 0;
	bool full = false;

public:
	Poincare() {
		count = 0;
		full = false;
	}
	void add(float p) {
		if (p < 800 || p > 4000) {
			return;
		}
		data[count++] = p;
#ifdef HEARTRATEINTERRUPT_DEBUG
		Serial.print("Poincare: count ");
		Serial.println(count);
#endif
		count %= POINCARE_SIZE;
		if (count == 0) {
			full = true;
		}
	}
	float get(int i) {
		return data[i];
	}
	int getMax() {
		int ret = POINCARE_SIZE-1;
		if (!full) {
			 ret = count-1;
		}
#ifdef HEARTRATEINTERRUPT_DEBUG
		Serial.print("Poincare: getMax ");
		Serial.print(" full ");
		Serial.print(full);
		Serial.print(" count ");
		Serial.print(count);
		Serial.print(" ret ");
		Serial.print(ret);
		Serial.println();
#endif
		return ret;
	}
};

class HeartRateInterrupt {
private:
	volatile int m_prev[PREVBUFSIZE];
	volatile long m_bpm;
	volatile long m_runningTime;
	volatile long m_counter;
	volatile bool m_effects;
	volatile float m_lastInterval;
	volatile float m_lastY;
	volatile float m_lastMax;
	volatile float m_lastMin;

	const static byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
	byte rates[RATE_SIZE]; //Array of heart rates
	byte rateSpot = 0;
	long lastBeat = 0; //Time at which the last beat occurred

	const static byte READINGS_SIZE = 10;
	long readings[READINGS_SIZE];
	byte readingsSpot = 0;

	long processPulse(long irValue);
	Poincare poincare;

public:
	HeartRateInterrupt(long startTime);
	virtual ~HeartRateInterrupt();
	int getCurrentBPM();
	void log();
	void calculate(int signal);
	Poincare *getPoincare() {
		return &poincare;
	}
	void reset();

	void setEffects(bool effects) {
		m_effects = effects;
	}

	float getLastInterval() const {
		return m_lastInterval;
	}

	volatile float getLastY() const {
		return m_lastY;
	}
	volatile float getLastMin() const {
		return m_lastMin;
	}
	volatile float getLastMax() const {
		return m_lastMax;
	}

	volatile long getCounter() const {
		return m_counter;
	}

	volatile int BPM; // used to hold the pulse rate
	volatile int averageBPM; // used to hold the pulse rate
	volatile int averageBPMCount; // used to hold the pulse rate
};

extern HeartRateInterrupt heartRateInterrupt;

#endif /* HEARTRATEINTERRUPT_H_ */
