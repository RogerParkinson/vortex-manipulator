/*
 * Clock.h
 *
 *  Created on: 28/04/2013
 *      Author: roger
 */

#ifndef CLOCK_H_
#define CLOCK_H_
#include "AppRegistry.h"
#include "ui/Button.h"
//#define CLOCK_DEBUG

class Clock : public App {
private:
	int displayHeading(int h);
	virtual void setup();
	bool m_noise = false;
	bool m_mars = false;
	int m_timeZone = 0;
	Button *m_buttonOn = new Button(60,150,50,"OFF");
	Button *m_buttonOff = new Button(150,150,50,"ON");
	Button *m_buttonMars = new Button(230,150,50,"MARS");

public:
	Clock();
	virtual unsigned long getUpdateInterval() {return 1000000UL;};
	virtual void init();
	virtual void display();
	virtual const char* getName() {return PSTR("Clock");};
	virtual boolean touch(TS_Point p);
	virtual void close();
	virtual ~Clock();
};

#endif /* CLOCK_H_ */
