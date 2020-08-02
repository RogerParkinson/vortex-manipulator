/*
 * Menu.cpp
 *
 *  Created on: 23/05/2013
 *      Author: roger
 */

#include "Menu.h"

Menu::Menu() {
	logger = loggerFactory.getLogger("Menu");
}
void Menu::init() {
	logger->debug("name %s %s",getName(),INIT);
}
void Menu::display() {
	// dynamic display
	Graphics.setCursor(0,Graphics.height()-10);
	Graphics.setTextColor(WHITE);
	Graphics.fillRect(0, Graphics.height()-10, Graphics.width(), 10 , BLACK);
	long adjustedDate = nz.toLocal(now());

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
			logger->debug("icon size=%d row=%d Graphics.height()=%d y=%d x=%d y=%d %s",
					icon->size,row, Graphics.height(),y,icon_x,icon_y,app->getName());
			icon->draw(icon_x,icon_y);
		}
		int x1 = OFFSET_COLUMN+column*Graphics.width()/MAX_COLUMN;
		int x2 = x1+w;
		int y2 = 10+OFFSET_ROW+row*Graphics.height()/MAX_ROW;
		int y1 = y2-45;
		app->setMenuPos(x1, y1, x2, y2);
		if (logger->isDebug()) {
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
		}
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
	logger->debug("menu::touch matching: %d %d ",p.x,p.y);

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
			logger->debug("%s %s",app->getName(),MATCH);
			if (logger->isDebug()) {
				Graphics.print(BLANK);
				Graphics.print(app->getName());
				Graphics.print(MATCH);
				Graphics.drawPixel(p.x,p.y,YELLOW);
			}
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
