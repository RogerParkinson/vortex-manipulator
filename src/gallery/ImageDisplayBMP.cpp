/*
 * ImageDisplayBMP.cpp
 *
 *  Created on: 3/06/2013
 *      Author: roger
 */

#include "ImageDisplayBMP.h"
#define BUFFPIXEL 80

ImageDisplayBMP::ImageDisplayBMP(File *infile, int x, int y): ImageDisplay(infile, x, y) {
	// TODO Auto-generated constructor stub

}
/**
 * display the rows for a BMP
 * This works fine but it is too slow (20 seconds per image)
 * Most of the time is taken up with the file reads
 * It works fine if the image is rotated.
 */
void ImageDisplayBMP::displayRows(int bmpWidth,
		int bmpHeight, bool flip, uint32_t bmpImageoffset, uint32_t rowSize) {

	uint8_t sdbuffer[3 * BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
	uint16_t lcdbuffer[BUFFPIXEL]; // pixel out buffer (16-bit per pixel)
	uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
	uint8_t lcdidx = 0;
	uint32_t pos = 0;
	bool first = true;
	uint8_t r, g, b;
	// Crop area to be loaded
	int w = bmpWidth;
	int h = bmpHeight;
	if ((m_x + w - 1) >= Graphics.width())
		w = Graphics.width() - m_x;
	if ((m_y + h - 1) >= Graphics.height())
		h = Graphics.height() - m_y;

	// Set TFT address window to clipped image bounds
	Graphics.setAddrWindow(m_x, m_y, m_x + w - 1, m_y + h - 1);
	for (int row = 0; row < h; row++) { // For each scanline...
		// Seek to start of scan line.  It might seem labor-
		// intensive to be doing this on every line, but this
		// method covers a lot of gritty details like cropping
		// and scanline padding.  Also, the seek only takes
		// place if the file position actually needs to change
		// (avoids a lot of cluster math in SD library).
		if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
			pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
		else
			// Bitmap is stored top-to-bottom
			pos = bmpImageoffset + row * rowSize;
		if (m_imgFile->position() != pos) { // Need seek?
			m_imgFile->seek(pos);
			buffidx = sizeof(sdbuffer); // Force buffer reload
		}

		for (int col = 0; col < w; col++) { // For each column...
			// Time to read more pixel data?
			if (buffidx >= sizeof(sdbuffer)) { // Indeed
				m_imgFile->read(sdbuffer, sizeof(sdbuffer));
				buffidx = 0; // Set index to beginning
			}

			// Convert pixel from BMP to TFT format
			b = sdbuffer[buffidx++];
			g = sdbuffer[buffidx++];
			r = sdbuffer[buffidx++];
			Graphics.pushColor(Graphics.color565(r, g, b));
		} // end pixel
	} // end scanline
}

ImageDisplayBMP::~ImageDisplayBMP() {
	// TODO Auto-generated destructor stub
}

