/*
 * Menu.h
 *
 *  Created on: 23/05/2013
 *      Author: roger
 */
// TODO: icons on SD?
// Icons need to be black and white and 28x28. Export to .h and use the array generated.

#ifndef MENU_H_
#define MENU_H_

#include "AppRegistry.h"

#define MAX_COLUMN 3
#define MAX_ROW 4
#define OFFSET_ROW 60
#define OFFSET_COLUMN 20
//#define DEBUG_MENU

class Menu: public App {
private:
//	uint16_t m_height;
//	uint16_t m_width;
public:
	Menu();
	virtual void setup();
	virtual void init();
	virtual void display();
	virtual unsigned long getUpdateInterval() {return 2000000UL;};
	virtual boolean touch(TS_Point p);
	virtual const char* getName() {return Appregistry.getMenuName();};
	virtual void notify(const char *s);
	virtual ~Menu();
};

#endif /* MENU_H_ */
