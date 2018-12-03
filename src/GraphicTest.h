/*
 * GraphicTest.h
 *
 *  Created on: 22/05/2013
 *      Author: roger
 */

#ifndef GRAPHICTEST_H_
#define GRAPHICTEST_H_
#include "AppRegistry.h"

class GraphicTest : public App {
private:
	unsigned long testFillScreen();
	unsigned long testText();
	unsigned long testLines(uint16_t color);
	unsigned long testFastLines(uint16_t color1, uint16_t color2);
	unsigned long testRects(uint16_t color);
	unsigned long testFilledRects(uint16_t color1, uint16_t color2);
	unsigned long testFilledCircles(uint8_t radius, uint16_t color);
	unsigned long testCircles(uint8_t radius, uint16_t color);
	unsigned long testTriangles();
	unsigned long testFilledTriangles();
	unsigned long testRoundRects();
	unsigned long testFilledRoundRects();
	virtual void print(long l);
	virtual void print(const char *str);


public:
	GraphicTest():App() {};
	virtual void display();
	virtual const char* getName() {return PSTR("Graphics");}
	virtual ~GraphicTest() {};
	virtual void init();
};

#endif /* GRAPHICTEST_H_ */
