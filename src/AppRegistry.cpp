/*
 * AppRegistry.cpp
 *
 *  Created on: 23/05/2013
 *      Author: roger
 */

#include "AppRegistry.h"

AppRegistry::AppRegistry() {
	loggerAppRegistry = loggerFactory.getLogger("AppRegistry");
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
	loggerAppRegistry->debug("Count=%d\n",count);
	for (int i=0;i<count;i++) {
		loggerAppRegistry->debug("Starting...%s",apps[i]->getName());
		apps[i]->init();
		loggerAppRegistry->debug("%s...done",apps[i]->getName());
	}
	jumpToMenu();
}
AppRegistry::~AppRegistry() {
}
AppRegistry Appregistry;

