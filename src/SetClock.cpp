/*
 * SetClock.cpp
 *
 *  Created on: 28/04/2013
 *      Author: roger
 */

#include "SetClock.h"

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

SetClock::SetClock(): App() {
	// Keep the constructor empty and do most things in the init()
}
void SetClock::init() {
#ifdef SETCLOCK_DEBUG
	Serial.println(PSTR("SetClock::init()"));
#endif
	m_icon = new Icon(28,myicon);
}

void SetClock::setup() {
#ifdef SETCLOCK_DEBUG
	Serial.println(PSTR("SetClock::setup()"));
#endif
	Graphics.fillScreen(BLACK);
	Graphics.setRotation(3);
	long adjustedDate = now() + (m_timeZone * SECS_PER_HOUR);

	m_buttonHH->setValue(hour(adjustedDate));
	m_buttonMM->setValue(minute(adjustedDate));
	m_buttonYY->setValue(year(adjustedDate));
	m_buttonmm->setValue(month(adjustedDate));
	m_buttonDD->setValue(day(adjustedDate));
	drawDateButtons();
	m_OK->draw();
}

void SetClock::drawDateButtons() {
	m_buttonHH->draw();
	m_buttonMM->draw();
	m_buttonYY->draw();
	m_buttonmm->draw();
	m_buttonDD->draw();
}

void SetClock::close() {
#ifdef SETCLOCK_DEBUG
	Serial.println(PSTR("SetClock::close()"));
#endif
}

boolean SetClock::touch(TS_Point p) {
	m_buttonHH->isClicked(p);
	m_buttonMM->isClicked(p);
	m_buttonYY->isClicked(p);
	m_buttonmm->isClicked(p);
	m_buttonDD->isClicked(p);
	if (m_OK->isClicked(p)) {
		// They clicked on OK
		m_OK->flash();
		setDateTime();
		return false;
	}
	return true;
}
void SetClock::setDateTime() {
	setTime(m_buttonHH->getValue(),
			m_buttonMM->getValue(),
			0,
			m_buttonDD->getValue(),
			m_buttonmm->getValue(),
			m_buttonYY->getValue());
	Teensy3Clock.set(now());// - (m_timeZone * SECS_PER_HOUR));
}
void SetClock::display() {
//	Graphics.fillRect(0,0,Graphics.width(),120,BLACK);
//	Graphics.setCursor(60,50);
//	Graphics.setTextColor(WHITE);
//	Graphics.setTextSize(3);
//
//	long adjustedDate = now() + (m_timeZone * SECS_PER_HOUR);

//	Graphics.println(Hardware.timeString(adjustedDate));
//	Graphics.setCursor(50,100);
//	Graphics.println(Hardware.dateString(adjustedDate));
}

SetClock::~SetClock() {
}

App *setclock = new SetClock();


