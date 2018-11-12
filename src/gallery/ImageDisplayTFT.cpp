/*
 * ImageDisplayTFT.cpp
 *
 *  Created on: 3/06/2013
 *      Author: roger
 */

#include "ImageDisplayTFT.h"

ImageDisplayTFT::ImageDisplayTFT(File *infile, int x, int y): ImageDisplay(infile, x, y) {

}
/**
 * display the rows for a TFT
 * This is quite fast, about 8 seconds but it does not handle rotation,
 * ie the rotation MUST be 1 or 3
 */
void ImageDisplayTFT::displayRows(int bmpWidth,
		int bmpHeight, bool flip, uint32_t bmpImageoffset, uint32_t rowSize) {
	uint8_t lcdidx = 0;
	bool first = true;
	// Crop area to be loaded
	int w = bmpWidth;
	int h = bmpHeight;
	if ((m_x + w - 1) >= Graphics.width())
		w = Graphics.width() - m_x;
	if ((m_y + h - 1) >= Graphics.height())
		h = Graphics.height() - m_y;

	// Set TFT address window to clipped image bounds
	Graphics.setAddrWindow(m_x, m_y, m_x + w - 1, m_y + h - 1); // 0.0.239.239

	uint16_t lcdbuffer[80]; // pixel out buffer (16-bit per pixel)
	m_imgFile->seek(bmpImageoffset);
	lcdidx = m_imgFile->read(lcdbuffer, sizeof(lcdbuffer)) / 2;
	while (lcdidx > 0) {
		pushColors(lcdbuffer, lcdidx, first);
		first = false;
		lcdidx = m_imgFile->read(lcdbuffer, sizeof(lcdbuffer)) / 2;
	}
}

ImageDisplayTFT::~ImageDisplayTFT() {
	// TODO Auto-generated destructor stub
}

