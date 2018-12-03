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
	loggerHardware = loggerFactory.getLogger("Hardware");
}

void Configuration::load() {
	File dataFile = SD.open(PSTR("hconfig.txt"));
	if (dataFile) {
		loggerHardware->debug("loading hconfig.txt");
		m_timeZone = Hardware.readInt(dataFile);//#define COMPASS_DEBUG

		m_lowPulse = Hardware.readInt(dataFile);
		m_highPulse = Hardware.readInt(dataFile);
		dataFile.close();
		loggerHardware->debug("loaded hconfig.txt");
	}
	// if the file isn't open, pop up an error:
	else {
		Serial.println(PSTR("error opening hconfig.txt"));
	}
}

Configuration::~Configuration() {
}

Configuration configuration = Configuration();
