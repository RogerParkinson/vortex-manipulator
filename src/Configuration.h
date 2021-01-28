/*
 * Configuration.h
 *
 *  Created on: 12/06/2014
 *      Author: roger
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_
#define VERSION "1.54"
#include <Logger.h>


class Configuration {
private:
	int m_timeZone;
	int m_lowPulse;
	int m_highPulse;
	Logger *loggerHardware;
public:
	Configuration();
	void load();
	virtual ~Configuration();

	int getHighPulse() const {
		return m_highPulse;
	}

	int getLowPulse() const {
		return m_lowPulse;
	}

	int getTimeZone() const {
		return m_timeZone;
	}
};

extern Configuration configuration;

#endif /* CONFIGURATION_H_ */
