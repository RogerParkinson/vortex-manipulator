/*
 * AppRegistry.h
 *
 *  Created on: 23/05/2013
 *      Author: roger
 */

#ifndef APPREGISTRY_H_
#define APPREGISTRY_H_

#include "App.h"
#define MAX_APPS 10
//#define DEBUG_APPREGISTRY

class AppRegistry {
private:
	int count=0;
	App *apps[MAX_APPS];
	App *currentApp=NULL;
	const char *m_menuName = PSTR("Menu");
public:
	AppRegistry();
	void setCurrentApp(App *app) {
		if (app == NULL) {
			Serial.println(PSTR("warning: AppRegistry:setCurrentApp(NULL)"));
			return;
		}
		if (app == currentApp) {
			return; // do nothing if we are already there
		}
		currentApp = app;
#ifdef DEBUG_APPREGISTRY
		Serial.print(PSTR("AppRegistry: switching to: "));
		Serial.println(app->getName());
#endif
		app->setup();
#ifdef DEBUG_APPREGISTRY
		Serial.print(PSTR("AppRegistry: setup complete for "));
		Serial.println(app->getName());
#endif
	};
	const char* getMenuName() {
		return m_menuName;
	}
	void jumpToMenu() {
#ifdef DEBUG_APPREGISTRY
		Serial.println(PSTR("AppRegistry: jump to menu"));
#endif
		if (currentApp != NULL) {
			if (strcmp(currentApp->getName(),m_menuName)==0) {
				return; // already on the menu
			}
			currentApp->close();
		}
		setCurrentApp(getApp(m_menuName));
	}
	App *getCurrentApp() {return currentApp;};
	void registerApp(App *app);
	App *getApp(const char* name);
	App *getApp(int i);
	void init();
	int getAppCount();
	virtual ~AppRegistry();
};
extern AppRegistry Appregistry;
#endif /* APPREGISTRY_H_ */
