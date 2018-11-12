/*
 * HeartRateInterrupt.cpp
 *
 *  Created on: 14/04/2013
 *      Author: roger
 */

#include "HeartRateInterrupt.h"
#include "../Hardware.h"

#define PULSE_LED LED1_PIN
const char *COMMA = PSTR(",");

HeartRateInterrupt::HeartRateInterrupt(long startTime) {
	m_counter = 0;
	m_runningTime = startTime;
	m_bpm = 0;
	m_effects = false;
	m_lastInterval = 0.0F;
	m_lastMax = 0;
	m_lastMin = 300000;
}
HeartRateInterrupt::~HeartRateInterrupt() {
}

int HeartRateInterrupt::getCurrentBPM() {
	return m_bpm;
}
void HeartRateInterrupt::log() {
	if (m_bpm > 20 && m_bpm < 200) {
		File m_logFile = SD.open(PSTR("datalog.txt"), FILE_WRITE);
		if (m_logFile) {
			m_logFile.print(now());
			m_logFile.print(COMMA);
			m_logFile.print(m_bpm);
			m_logFile.print(COMMA);
			m_logFile.println(m_lastInterval);
			m_logFile.close();
		}
	}
	return;
}
void HeartRateInterrupt::reset() {
	m_lastInterval = 0.0F;
	m_counter = 0;
	m_runningTime = 0;
	digitalWrite(PULSE_LED, LOW);
}

long HeartRateInterrupt::processPulse(long irValue) {

  if (checkForBeat(irValue) == true)
  {
	//We sensed a beat!
	m_lastInterval = millis() - lastBeat;
	poincare.add(m_lastInterval);
	lastBeat = millis();

	float beatsPerMinute = 60 / (m_lastInterval / 1000.0);

	if (beatsPerMinute < 255 && beatsPerMinute > 20) {
		rates[rateSpot++] = (byte) beatsPerMinute; //Store this reading in the array
		rateSpot %= RATE_SIZE; //Wrap variable

		//Take average of readings
		int beatAvg = 0;
		for (byte x = 0; x < RATE_SIZE; x++)
			beatAvg += rates[x];
		beatAvg = beatAvg / RATE_SIZE;
		m_bpm = beatAvg;
	}
	if (m_effects) {
		digitalWrite(PULSE_LED, HIGH);
		if (m_bpm < configuration.getLowPulse()) {
			tone(TONE_PIN, 3136,31);
		}
		if (m_bpm > configuration.getHighPulse()) {
			tone(TONE_PIN, 4186,30);
		}
	}
  }
  return irValue;
}

void HeartRateInterrupt::calculate(volatile int signal) {

	digitalWrite(PULSE_LED, LOW);
	noTone(TONE_PIN);
	long irValue = particleSensor.getIR();
	processPulse(irValue);
	readings[readingsSpot++] = irValue;
	readingsSpot %= READINGS_SIZE;

	//Take average of readings
	long readingsAvg = 0;
	for (byte x = 0; x < READINGS_SIZE; x++)
		readingsAvg += readings[x];
	m_lastY = readingsAvg / READINGS_SIZE;//230-((((readingsAvg /= RATE_SIZE)-440)*0.20F)+80);
	m_lastMax = max(m_lastMax,m_lastY);
	m_lastMin = min(m_lastMin,m_lastY);
//#ifdef HEARTRATEINTERRUPT_DEBUG
//	Serial.print("HeartRateInterrupt::calculate m_lastY=");
//	Serial.print(m_lastY);
//	Serial.print(" readingsAvg=");
//	Serial.print(readingsAvg);
//	Serial.print(" min=");
//	Serial.print(m_lastMin);
//	Serial.print(" max=");
//	Serial.println(m_lastMax);
//#endif

	m_counter++;
}

