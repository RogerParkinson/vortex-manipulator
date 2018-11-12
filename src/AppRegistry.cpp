/*
 * AppRegistry.cpp
 *
 *  Created on: 23/05/2013
 *      Author: roger
 */

#include "AppRegistry.h"

AppRegistry::AppRegistry() {
}

void AppRegistry::registerApp(App *app) {
	if (count > MAX_APPS)
	{
		return;
	}
	apps[count++] = app;
}
App *AppRegistry::getApp(int i) {
	if (i >= count) {
		return NULL;
	}
	return apps[i];
}
App *AppRegistry::getApp(const char* name) {
	for (int i=0;i<count;i++) {
		if (strcmp(name,apps[i]->getName())==0) {
			return apps[i];
		}
	}
	return NULL;
}
int AppRegistry::getAppCount() {
	return count;
}
void AppRegistry::init() {
#ifdef DEBUG_APPREGISTRY
	Serial.print(PSTR("Count="));
	Serial.println(count);
#endif
	for (int i=0;i<count;i++) {
#ifdef DEBUG_APPREGISTRY
		Serial.print("Starting...");
		Serial.println(apps[i]->getName());
#endif
		apps[i]->init();
#ifdef DEBUG_APPREGISTRY
		Serial.print(apps[i]->getName());
		Serial.println("...done");
#endif
	}
	jumpToMenu();
}
AppRegistry::~AppRegistry() {
}
AppRegistry Appregistry;

