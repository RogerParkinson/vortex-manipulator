/*
 * HeartRateMonitor.h
 *
 *  Created on: 28/04/2013
 *      Author: roger
 */

#ifndef HEARTRATEMONITOR_H_
#define HEARTRATEMONITOR_H_
#include "AppRegistry.h"
#include "heartrate/HeartRateInterrupt.h"
#include "heartrate/SimpleMap.h"
#include "ui/Panel.h"
#include <cassert>

#define POINCARE // turns on Poincare plot
#define MAX_GUESS 0
#define MIN_GUESS 112632
#define PREV_BUFSIZE 40
#define SCREEN_OFFSET 100
#define SCREEN_HEIGHT 240-SCREEN_OFFSET

class HeartRateMonitor : public App {
private:
	virtual void setup();
	volatile int m_prev[PREV_BUFSIZE];
	bool m_prevPopulated;
	volatile int m_prevCount;
	bool m_effects;
	long m_lastInterval;
	int m_lastX;
	float m_lastMin;
	float m_lastMax;
	float m_lastScale;
	float m_scaledLastMin;
	float m_scaledLastMax;
	SimpleMap *m_map;
	virtual void initaliseGraph(int bpm, float interval);
	virtual void figureScale();
	Logger *logger;
	Panel panelText = Panel(0,0,150,100,WHITE);
	Panel panelHR = Panel(0,100,320,SCREEN_HEIGHT,WHITE);
	Panel panelPoincare = Panel(150,0,170,100,WHITE);

public:
	HeartRateMonitor();
	virtual void init();
	virtual void display();
	virtual unsigned long getUpdateInterval() {return 2000UL;};
	virtual const char* getName() {return PSTR("HeartRate");};
	virtual boolean touch(TS_Point p);
	virtual void close();

	virtual ~HeartRateMonitor();
};


#endif /* HEARTRATEMONITOR_H_ */
