/*
 * Clock.cpp
 *
 *  Created on: 28/04/2013
 *      Author: roger
 */

#include "Clock.h"

static uint16_t myicon[] PROGMEM = {
	0xa514,0xbdd7,0xb596,0xc618,0x0000,0x0000,0x7bcf,0x0000,0xa514,0x8c51,0xbdd7,0xbdd7,0x9cd3,0xce59,0x9492,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x8c51,0xdedb,0xad55,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0xad55,0xe71c,0x6b4d,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0xbdd7,0xad55,0xbdd7,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0x9492,0xbdd7,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xbdd7,0xa514,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0xffdf,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xb596,0xc618,0x0000,0x0000,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x9492,0x8c51,0x0000,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xd69a,0x0000,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xdedb,0x0000,0x0000,0xb596,0xbdd7,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0xffdf,0x0000,0xb596,0x0000,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0xffdf,0xb596,0xa514,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xb596,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xb596,0x5acb,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xb596,0x8c51,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xd69a,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0x0000,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xd69a,0xffdf,0xb596,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0xdedb,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xb596,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0xc618,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xdedb,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xffdf,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xc618,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xdedb,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0xef5d,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x8c51,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0841,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xdedb,0xffdf,0xffdf,0xa514,0x630c,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0xce59,0xffdf,0xbdd7,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0x0000,0x0000,0xffdf,0xbdd7,0x0000,0x0000,
	0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0xffdf,0x0000,0xce59,0x0000,0x0000,0xce59,0x0000,0x0000,0x0000,0x0};

Clock::Clock(): App() {
	// Keep the constructor empty and do most things in the init()
}
void Clock::init() {
#ifdef CLOCK_DEBUG
	Serial.println("Clock::init()");
#endif
	m_noise = false;
	m_icon = new Icon(28,myicon);
	m_timeZone = configuration.getTimeZone();
#ifdef CLOCK_DEBUG
	Serial.print("m_timeZone=");
	Serial.println(m_timeZone);
#endif
}

void Clock::setup() {
#ifdef CLOCK_DEBUG
	Serial.println("Clock::setup()");
#endif
	Graphics.fillScreen(BLACK);
	Graphics.setRotation(3);
	m_buttonOn->draw();
	m_buttonOff->draw();
}

void Clock::close() {
#ifdef CLOCK_DEBUG
	Serial.println(PSTR("Clock::close()"));
#endif
	m_noise = false;
}

boolean Clock::touch(TS_Point p) {
	if (m_buttonOn->isClicked(p)) {
		Serial.println(PSTR("clock::touch turning off noise"));
		m_buttonOn->flash();
		m_noise = false;
	}
	else if (m_buttonOff->isClicked(p)) {
		Serial.println(PSTR("clock::touch turning on noise"));
		m_buttonOff->flash();
		m_noise = true;
	}
#ifdef CLOCK_DEBUG
	Serial.print(PSTR("clock::touch m_noise="));
	Serial.println(m_noise);
#endif
	return true;
}
void Clock::display() {
	if (m_noise) {
		Serial.println(PSTR("clock::noise"));
		Hardware.playTone(3136,30,40);
		Hardware.playTone(4186,30,9);
		Hardware.blink1();
	}
	Graphics.fillRect(0,0,Graphics.width(),120,BLACK);
	Graphics.setCursor(60,50);
	Graphics.setTextColor(WHITE);
	Graphics.setTextSize(3);
	Graphics.setFont(Arial_20);

	long adjustedDate = now();// + (m_timeZone * SECS_PER_HOUR);

	Graphics.println(Hardware.timeString(adjustedDate));
	Graphics.setCursor(50,100);
	Graphics.println(Hardware.dateString(adjustedDate));
	Graphics.setFont(Hardware.getDefaultFont());
}

Clock::~Clock() {
}

App *clock = new Clock();


