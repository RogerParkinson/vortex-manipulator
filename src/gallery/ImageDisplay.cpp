/*
 * ImageDisplay.cpp
 *
 *  Created on: 3/06/2013
 *      Author: roger
 */

#include "ImageDisplay.h"

ImageDisplay::ImageDisplay(File *infile, int x, int y) {
	m_imgFile = infile;
	m_x = x;
	m_y = y;
	m_totalLen = 0;
}
/**
 * This is common to both BMP and TFT files.
 */
bool ImageDisplay::displayFile() {
	uint32_t rowSize; // Not always = bmpWidth; may have padding
	uint32_t bmpImageoffset; // Start of image data in file
	int bmpWidth, bmpHeight; // W+H in pixels
	uint8_t bmpDepth; // Bit depth (currently must be 24)
	boolean flip = true; // BMP is stored bottom-to-top
	boolean goodBmp = false;
#ifdef IMAGE_DEBUG
	Hardware.progmemPrint(PSTR("File size: "));
	Serial.println(Hardware.read32(*m_imgFile));
#endif
	(void) Hardware.read32(*m_imgFile); // Read & ignore creator bytes
	bmpImageoffset = Hardware.read32(*m_imgFile); // Start of image data
#ifdef IMAGE_DEBUG
	Hardware.progmemPrint(PSTR("Image Offset: "));
	Serial.println(bmpImageoffset, DEC);
	// Read DIB header
	Hardware.progmemPrint(PSTR("Header size: "));
	Serial.println(Hardware.read32(*m_imgFile));
#endif
	bmpWidth = Hardware.read32(*m_imgFile);
	bmpHeight = Hardware.read32(*m_imgFile);
	if (Hardware.read16(*m_imgFile) == 1) { // # planes -- must be '1'
		bmpDepth = Hardware.read16(*m_imgFile); // bits per pixel
#ifdef IMAGE_DEBUG
		Hardware.progmemPrint(PSTR("Bit Depth: "));
		Serial.println(bmpDepth);
#endif
		if ((bmpDepth == 24) && (Hardware.read32(*m_imgFile) == 0)) { // 0 = uncompressed

			goodBmp = true; // Supported BMP format -- proceed!
#ifdef IMAGE_DEBUG
			Hardware.progmemPrint(PSTR("Image size: "));
			Serial.print(bmpWidth);
			Serial.print('x');
			Serial.println(bmpHeight);
#endif

			// BMP rows are padded (if needed) to 4-byte boundary
			rowSize = (bmpWidth * 3 + 3) & ~3;

			// If bmpHeight is negative, image is in top-down order.
			// This is not canon but has been observed in the wild.
			if (bmpHeight < 0) {
				bmpHeight = -bmpHeight;
				flip = false;
			}
			uint32_t startTime = millis();
			m_totalLen = 0;
			displayRows(bmpWidth, bmpHeight, flip,
					bmpImageoffset, rowSize);
#ifdef IMAGE_DEBUG
			Hardware.progmemPrint(PSTR("Total pixels "));
			Serial.println(m_totalLen);
			Hardware.progmemPrint(PSTR("Loaded in "));
			Serial.print(millis() - startTime);
			Serial.println(" ms");
#endif
		}
	}
	return goodBmp;
}
void ImageDisplay::pushColors(uint16_t *data, uint8_t len, boolean first) {
//	Graphics.pushColors(data, len, first);
	m_totalLen += len;
}

ImageDisplay::~ImageDisplay() {
	// TODO Auto-generated destructor stub
}

