/*
 * Configuration.cpp
 *
 *  Created on: 12/06/2014
 *      Author: roger
 */

#include "Configuration.h"
#include "Hardware.h"

Configuration::Configuration() {
	// Default values
	m_timeZone = 12;
	m_lowPulse = 120;
	m_highPulse = 150;

	m_lowPulse = 40;
	m_highPulse = 50;

}

void Configuration::load() {
	File dataFile = SD.open(PSTR("hconfig.txt"));
	if (dataFile) {
#ifdef HARDWARE_DEBUG
		Serial.println(PSTR("loading hconfig.txt"));
#endif
		m_timeZone = Hardware.readInt(dataFile);
		m_lowPulse = Hardware.readInt(dataFile);
		m_highPulse = Hardware.readInt(dataFile);
		dataFile.close();
#ifdef HARDWARE_DEBUG
		Serial.println(PSTR("loaded hconfig.txt"));
#endif
	}
	// if the file isn't open, pop up an error:
	else {
		Serial.println(PSTR("error opening hconfig.txt"));
	}
}

Configuration::~Configuration() {
}

Configuration configuration = Configuration();
