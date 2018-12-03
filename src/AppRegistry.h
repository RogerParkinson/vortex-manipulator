/*
 * AppRegistry.h
 *
 *  Created on: 23/05/2013
 *      Author: roger
 */

#ifndef APPREGISTRY_H_
#define APPREGISTRY_H_

#include "App.h"
#include <Logger.h>

#define MAX_APPS 10
//#define DEBUG_APPREGISTRY

class AppRegistry {
private:
	Logger *loggerAppRegistry;
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
		loggerAppRegistry->debug(PSTR("switching to: %s"),app->getName());
		app->setup();
		loggerAppRegistry->debug(PSTR("setup complete for: %s"),app->getName());
	};
	const char* getMenuName() {
		return m_menuName;
	}
	void jumpToMenu() {
		loggerAppRegistry->debug(PSTR("AppRegistry: jump to menu"));
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
