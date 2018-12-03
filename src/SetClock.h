/*
 * SetClock.h
 *
 *  Created on: 28/04/2013
 *      Author: roger
 */

#ifndef SETCLOCK_H_
#define SETCLOCK_H_
#include "AppRegistry.h"
#include "ui/Button.h"
#include "ui/Incrementor.h"

class SetClock : public App {
private:
	int displayHeading(int h);
	virtual void setup();
	void drawDateButtons();
	void setDateTime();
	bool m_noise = false;
	int m_timeZone = 0;
	Button *m_OK = new Button(240,95,40,PSTR("OK"));
	Incrementor *m_buttonHH = new Incrementor(20,5,200,0,60);
	Incrementor *m_buttonMM = new Incrementor(20,50,200,0,60);
	Incrementor *m_buttonYY = new Incrementor(20,95,200,1970,2070);
	Incrementor *m_buttonmm = new Incrementor(20,140,200,1,12);
	Incrementor *m_buttonDD = new Incrementor(20,185,200,1,31);

public:
	SetClock();
	virtual unsigned long getUpdateInterval() {return 1000000UL;};
	virtual void init();
	virtual void display();
	virtual const char* getName() {return PSTR("SetClock");};
	virtual boolean touch(TS_Point p);
	virtual void close();
	virtual ~SetClock();
};

#endif /* SETCLOCK_H_ */
