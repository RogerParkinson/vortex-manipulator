/*
 * Compass.h
 *
 *  Created on: 28/04/2013
 *      Author: roger
 */

#ifndef COMPASS_H_
#define COMPASS_H_
#include "AppRegistry.h"
#include <cassert>

//#define COMPASS_DEBUG
#define ANGLE_CORRECTION	1200
#define CIRCLE_PORTION	0.60
#define ARROW_LENGTH 40
#define ARROW_WIDTH (15 * DEG_TO_RAD)

class Compass : public App {
private:
	uint16_t m_cx;
	uint16_t m_cy;
	uint16_t m_height;
	uint16_t m_width;
	short m_cradius;
	short m_cycleCount = 0;
	double last_heading_radians;
	double m_arrowSide;
	void arrow(uint16_t x, uint16_t y, double angle_radians,
			uint16_t colour);
	int displayHeading(int h);
	virtual void setup();

public:
	static int s_nValue;
	LSM303::vector<int16_t> m_last;

	Compass();
	virtual unsigned long getUpdateInterval() {return 1000000UL;};
	virtual void init();
	virtual void display();
	virtual void close();
	virtual const char* getName() {return PSTR("Compass");};
	// Fix to cope with odd stuff in the touch
//	virtual void setMenuPos(int x1, int y1, int x2, int y2) {
//		m_x1 = 165;
//		m_y1 =19;
//		m_x2 = 189;
//		m_y2 =44;
//	}
	virtual ~Compass();
};

#endif /* COMPASS_H_ */
