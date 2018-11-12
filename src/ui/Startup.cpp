/*
 * Startup.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: roger
 */

#include "Startup.h"

Startup::Startup() {
	row = 1;
}

void Startup::run() {
	Graphics.setRotation(3);
	row = 1;
	Graphics.fillScreen(BLACK);
	Graphics.setCursor(0, 0);
	Graphics.setTextColor(YELLOW);
	Graphics.setTextSize(4);
	char r[20];
	sprintf(r,"%d",rand());
	println("Scanning for space-time vortices...");
	print("Located vortex at ");
	println(r);
	print("Acquiring lock on ");
	print(r);
	println("...");
	println("Acquired");
	println("Tardis scanner active.");
	println("No Tardis in this vicinity.");
	Hardware.blink1();
}

void Startup::print(const char *s) {
	byte i = 0;
	char p = s[i++];
	while (p != 0) {
		Graphics.print(p);
		Hardware.playTone(3136,30,40);
		Hardware.playTone(4186,30,9);
		delay(100);
		p = s[i++];
	}
}

void Startup::println(const char *s) {
	print(s);
	delay(100);
	Graphics.setCursor(0, (row++)*20);
}


Startup::~Startup() {
}

Startup startup = Startup();
