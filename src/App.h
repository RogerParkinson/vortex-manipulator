/*
 * App.h
 *
 *  Created on: 21/05/2013
 *      Author: roger
 */

#ifndef APP_H_
#define APP_H_
#include "Hardware.h"
#include "Configuration.h"
//#define DEBUG_APP

extern const char *INIT;
extern const char *BLANK;
extern const char *NLL;
extern const char *MATCH;
extern const char *COMMA;

class App {
protected:
	Icon *m_icon = NULL;
	int m_x1, m_y1, m_x2, m_y2;
public:
	App();
	virtual ~App() {};
	virtual unsigned long getUpdateInterval() {return 500000UL;};
	virtual const char* getName() {return PSTR("App");};
	virtual const Icon *getIcon() {return m_icon;};
	virtual void notify(const char *s) {};
	virtual boolean touch(TS_Point p) {
#ifdef DEBUG_APP
		Serial.print(PSTR("App::touch "));
		Serial.println(getName());
#endif
		return true; // false means exit to menu
	};
	virtual void setMenuPos(int x1, int y1, int x2, int y2) {
		m_x1 = x1;
		m_y1 =y1;
		m_x2 = x2;
		m_y2 =y2;
#ifdef DEBUG_APP
		Serial.print(PSTR("setMenuPos app "));
		Serial.print(getName());
		Serial.print(" ");
		Serial.print(m_x1);
		Serial.print(" ");
		Serial.print(m_x2);
		Serial.print(" ");
		Serial.print(m_y1);
		Serial.print(" ");
		Serial.print(m_y2);
		Serial.println("");
#endif
	}
	bool menuMatch(TS_Point p) {
#ifdef DEBUG_APP
		Serial.print(PSTR("app "));
		Serial.print(getName());
		Serial.print(" ");
		Serial.print(m_x1);
		Serial.print(" ");
		Serial.print(m_x2);
		Serial.print(" ");
		Serial.print(m_y1);
		Serial.print(" ");
		Serial.print(m_y2);
		if ((p.x>=m_x1 && p.x<m_x2 && p.y>=m_y1 && p.y<m_y2)) {
			Serial.print(PSTR(" matched!!"));
		}
		Serial.println("");
#endif
		return (p.x>=m_x1 && p.x<m_x2 && p.y>=m_y1 && p.y<m_y2);
	}
	virtual void init() {
#ifdef DEBUG_APP
		Serial.print(PSTR("App::init "));
		Serial.println(getName());
#endif
	};
	virtual void setup() {
#ifdef DEBUG_APP
		Serial.print(PSTR("App::setup "));
		Serial.println(getName());
#endif
		Graphics.setRotation(3);
		Graphics.setCursor(0,0);
		Graphics.fillScreen(BLACK);
	};
	virtual void close() {
#ifdef DEBUG_APP
		Serial.print(PSTR("App::close "));
		Serial.println(getName());
#endif
	};
	virtual void display() {
#ifdef DEBUG_APP
		Serial.print(PSTR("App::display "));
		Serial.println(getName());
#endif
	};
};

#endif /* APP_H_ */
