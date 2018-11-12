/*
 * App.cpp
 *
 *  Created on: 21/05/2013
 *      Author: roger
 */

#include "App.h"
#include "AppRegistry.h"

const char *INIT = PSTR("::init()");
const char *BLANK = PSTR(" ");
const char *NLL = PSTR("");
const char *MATCH = PSTR(" match!");

App::App() {
		Appregistry.registerApp(this);
	};



