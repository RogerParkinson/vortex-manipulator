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
		return true; // false means exit to menu
	};
	virtual void setMenuPos(int x1, int y1, int x2, int y2) {
		m_x1 = x1;
		m_y1 =y1;
		m_x2 = x2;
		m_y2 =y2;
	}
	bool menuMatch(TS_Point p) {
		return (p.x>=m_x1 && p.x<m_x2 && p.y>=m_y1 && p.y<m_y2);
	}
	virtual void init() {
	};
	virtual void setup() {
		Graphics.setRotation(3);
		Graphics.setCursor(0,0);
		Graphics.fillScreen(BLACK);
	};
	virtual void close() {
	};
	virtual void display() {
	};
};

#endif /* APP_H_ */
