/*
 * Button.cpp
 *
 *  Created on: 28/05/2013
 *      Author: roger
 */

#include "Button.h"


	Button::Button(int x, int y, int size, int colour) {
		m_x = x;
		m_y = y;
		m_sizex = size;
		m_sizey = size;
		m_colour = colour;
	};
	Button::Button(int x, int y, int size, const char *text) {
		m_x = x;
		m_y = y;
		m_sizex = size;
		m_sizey = 40;
		m_colour = WHITE;
		m_text = text;
	};

	void Button::draw() {
		Graphics.fillRoundRect(m_x,m_y,m_sizex,m_sizey,10,BLACK);
		Graphics.drawRoundRect(m_x,m_y,m_sizex,m_sizey,10,m_colour);
		if (m_text != NULL) {
			int i = strlen(m_text)*10/2;
			int jx = (m_sizex/2)-3;
			int jy = (m_sizey/2)-3;
			Graphics.setCursor(m_x+(jx-i),m_y+jy);
			Graphics.setTextColor(m_colour);
			Graphics.setTextSize(2);
			Graphics.print(m_text);
		}
	};

	void Button::flash() {
		Graphics.fillRoundRect(m_x,m_y,m_sizex,m_sizey,10,m_colour);
		if (m_text != NULL) {
			int i = strlen(m_text)*10/2;
			int jx = (m_sizex/2)-3;
			int jy = (m_sizey/2)-3;
			Graphics.setCursor(m_x+(jx-i),m_y+jy);
			Graphics.setTextColor(BLACK);
			Graphics.setTextSize(2);
			Graphics.print(m_text);
		}
		delay(500);
		draw();
	};

	Button * Button::highlight() {
		Graphics.fillRoundRect(m_x,m_y,m_sizex,m_sizey,10,m_colour);
		if (m_text != NULL) {
			int i = strlen(m_text)*10/2;
			int jx = (m_sizex/2)-3;
			int jy = (m_sizey/2)-3;
			Graphics.setCursor(m_x+(jx-i),m_y+jy);
			Graphics.setTextColor(BLACK);
			Graphics.setTextSize(2);
			Graphics.print(m_text);
		}
		return this;
	};

	void Button::setText(const char* text) {
		m_text = text;
	}

	bool Button::isClicked(TS_Point p) {
		return (p.x>=m_x && p.x<=m_x+m_sizex && p.y>=m_y && p.y<=m_y+m_sizey);
	}

	Button::~Button() {
	}

