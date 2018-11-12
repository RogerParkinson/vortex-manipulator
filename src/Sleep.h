/*
 * Sleep.h
 *
 *  Created on: 28/04/2013
 *      Author: roger
 */

#ifndef SHUTDOWN_H_
#define SHUTDOWN_H_
#include "AppRegistry.h"
#include "ui/Button.h"
//#define SHUTDOWN_DEBUG

const char *SLEEP = PSTR("Sleep");
const char *SHUTDOWN = PSTR("Shutdown");

class Sleep : public App {
private:
	int displayHeading(int h);
	virtual void setup();
	int m_timeZone = 0;
	Button *m_buttonSleep = new Button(80,40,150,SLEEP);
	Button *m_buttonShutdown = new Button(80,90,150,SHUTDOWN);

public:
	Sleep();
	virtual unsigned long getUpdateInterval() {return 1000000UL;};
	virtual void init();
	virtual void display();
	virtual const char* getName() {return SLEEP;};
	virtual boolean touch(TS_Point p);
	virtual void close();
	virtual ~Sleep();
};

#endif /* SHUTDOWN_H_ */
