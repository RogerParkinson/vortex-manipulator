/*
 * Panel.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: roger
 */

#include "Panel.h"


void Panel::clear() {
	Graphics.fillRect(m_x,m_y,m_sizex,m_sizey,m_colour);
}
void Panel::drawPixel(int x, int y, int colour) {
	int x1 = constrain(x, 0, m_sizex);
	int y1 = constrain(y, 0, m_sizey);
	Graphics.drawPixel(m_x+x1,m_y+y1,colour);
}
void Panel::setCursor(int x, int y) {
	Graphics.setCursor(m_x+x,m_y+y);
}
void Panel::fillCircle(int x, int y, int r, int colour) {
	Graphics.fillCircle(m_x+constrain(x,0,m_sizex),
			constrain(m_y+y,0,m_sizey),r,colour);
}
