/*
 * Panel.h
 *
 *  Created on: Dec 3, 2018
 *      Author: roger
 */

#ifndef PANEL_H_
#define PANEL_H_

#include "../Hardware.h"


class Panel {
private:
	int m_x;
	int m_y;
	int m_sizex;
	int m_sizey;
	int m_colour;
public:
	Panel(int x, int y, int sizex, int sizey, int colour) {
		m_x = x;
		m_y = y;
		m_sizex = sizex;
		m_sizey = sizey;
		m_colour = colour;
	}
	int getSizex() const {
		return m_sizex;
	}

	int getSizey() const {
		return m_sizey;
	}

	int getX() const {
		return m_x;
	}

	int getY() const {
		return m_y;
	}
	void clear();
	void clear(int borderColour);
	void drawPixel(int x, int y, int colour);
	void setCursor(int x, int y);
	void fillCircle(int x, int y, int r, int colour);
	void border(int colour);
};

#endif /* PANEL_H_ */
