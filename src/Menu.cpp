/*
 * Menu.cpp
 *
 *  Created on: 23/05/2013
 *      Author: roger
 */

#include "Menu.h"

Menu::Menu() {
}
void Menu::init() {
#ifdef DEBUG_MENU
	Serial.print(getName());Serial.println(INIT);
#endif
}
void Menu::display() {
	// dynamic display
	Graphics.setCursor(0,Graphics.height()-10);
	Graphics.setTextColor(WHITE);
	Graphics.fillRect(0, Graphics.height()-10, Graphics.width(), 10 , BLACK);
	long adjustedDate = now();

	Graphics.print(Hardware.timeString(adjustedDate));
	Graphics.print(BLANK);
	Graphics.print(Hardware.dateString(adjustedDate));
	Graphics.print(PSTR("        Battery: "));
	Graphics.print(Hardware.getBatteryVoltage());
	Graphics.print(PSTR(" volts"));
}
void Menu::notify(const char *s) {
	setup();
};
void Menu::setup() {
	Graphics.setRotation(3);
	Graphics.setCursor(0,0);
	Graphics.fillScreen(BLACK);
	int row = 0;
	int column = 0;
	Graphics.setRotation(3);
	Graphics.setTextSize(1);
	Graphics.setCursor(0,0 );

	if (!Hardware.isSDOK()) {
		Hardware.beginSD();
	}
	Graphics.setTextColor(WHITE);
	Graphics.print(PSTR("V"));
	Graphics.print(PSTR(VERSION));
	if (!Hardware.isSDOK()) {
		Graphics.print(PSTR("      SD failed to init"));
	} else {
		Graphics.print(PSTR("      SD available"));
	}

	for (int i=0;i<Appregistry.getAppCount();i++) {
		App *app = Appregistry.getApp(i);
		if (strcmp(app->getName(),Appregistry.getMenuName())==0) {
			continue;
		}
		Icon* icon = (Icon*)app->getIcon();
		int w = max(14,6*strlen(app->getName()));
		int x = OFFSET_COLUMN+column*Graphics.width()/MAX_COLUMN;
		int y = OFFSET_ROW+row*Graphics.height()/MAX_ROW;
		if (icon != NULL) {
			int icon_x = x+((w/2)-(icon->size)/2);
			int icon_y = y-((icon->size)+5);
#ifdef DEBUG_MENU
			Serial.print(PSTR("icon "));
			Serial.print(PSTR("size="));
			Serial.print(icon->size);
			Serial.print(PSTR(" row="));
			Serial.print(row);
			Serial.print(PSTR(" Graphics.height()="));
			Serial.print(Graphics.height());
			Serial.print(PSTR(" y="));
			Serial.print(y);
			Serial.print(PSTR(" x="));
			Serial.print(icon_x);
			Serial.print(PSTR(" y="));
			Serial.print(icon_y);
//			Serial.print(PSTR(" bitmapsize="));
//			Serial.print(strlen(icon->bitmap));
			Serial.print(BLANK);
			Serial.println(app->getName());
#endif
			icon->draw(icon_x,icon_y);
		}
		int x1 = OFFSET_COLUMN+column*Graphics.width()/MAX_COLUMN;
		int x2 = x1+w;
		int y2 = 10+OFFSET_ROW+row*Graphics.height()/MAX_ROW;
		int y1 = y2-45;
		app->setMenuPos(x1, y1, x2, y2);
#ifdef DEBUG_MENU
		Graphics.drawRect(x1,y1,x2-x1,y2-y1,RED);
		Graphics.setCursor(x,y+10);
		Graphics.print("x1=");
		Graphics.print(x1);
		Graphics.print(" y1=");
		Graphics.print(y1);
		Graphics.setCursor(x,y+20);
		Graphics.print("x2=");
		Graphics.print(x2);
		Graphics.print(" y2=");
		Graphics.print(y2);
#endif
		Graphics.setCursor(x,y);
		Graphics.setTextColor(WHITE);
		Graphics.print(app->getName());
		if (column >= MAX_COLUMN-1) {
			row++;
			column=0;
		}
		else {
			column++;
		}
	}

}
boolean Menu::touch(TS_Point p) {

	int row = 0;
	int column = 0;

#ifdef DEBUG_MENU
//	Graphics.fillRect(0,0,Graphics.width(),10,BLACK);
//	Graphics.setCursor(0,0);
//	Graphics.print("touch ");
//	Graphics.print(p.x);
//	Graphics.print(" ");
//	Graphics.print(p.y);
//	Graphics.print("");
//	Graphics.print(" width: ");
//	Graphics.print(Graphics.width());
//	Graphics.print(" height: ");
//	Graphics.print(Graphics.height());

	Serial.print(PSTR("menu::touch matching: "));
	Serial.print(p.x);
	Serial.print(BLANK);
	Serial.println(p.y);
//	Serial.print(NLL);
//	Serial.print(PSTR(" width: "));
//	Serial.print(Graphics.width());
//	Serial.print(PSTR(" height: "));
//	Serial.println(Graphics.height());
#endif

	for (int i=0;i<Appregistry.getAppCount();i++) {
		App *app = Appregistry.getApp(i);
		if (strcmp(app->getName(),Appregistry.getMenuName())==0) {
			continue;
		}
		int x1 = OFFSET_COLUMN+column*Graphics.width()/MAX_COLUMN;
		int x2 = x1+30;
		int y2 = 10+OFFSET_ROW+row*Graphics.height()/MAX_ROW;
		int y1 = y2-30;
		if (app->menuMatch(p)) {
#ifdef DEBUG_MENU
			Serial.print(app->getName());
			Serial.println(MATCH);
			Graphics.print(BLANK);
			Graphics.print(app->getName());
			Graphics.print(MATCH);
			Graphics.drawPixel(p.x,p.y,YELLOW);
#endif
			Appregistry.setCurrentApp(app);
		}
		if (column >= MAX_COLUMN-1) {
			row++;
			column=0;
		}
		else {
			column++;
		}
	}
	return true;
}

Menu::~Menu() {
}

App *menu = new Menu();
