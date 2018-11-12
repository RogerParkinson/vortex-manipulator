/*
 * Button.h
 *
 *  Created on: 28/05/2013
 *      Author: roger
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "../Hardware.h"

class Button {
private:
	int m_x;
	int m_y;
	int m_sizex;
	int m_sizey;
	int m_colour;
	const char *m_text=NULL;
public:
	Button(int x, int y, int size, int colour);
	Button(int x, int y, int size, const char *text);
	void draw();
	void flash();
	Button * highlight();
	void setText(const char* text);
	bool isClicked(TS_Point p);
	virtual ~Button();

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
};

#endif /* BUTTON_H_ */

