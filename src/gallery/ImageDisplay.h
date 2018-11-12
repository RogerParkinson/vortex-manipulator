/*
 * ImageDisplay.h
 *
 *  Created on: 3/06/2013
 *      Author: roger
 */

#ifndef IMAGEDISPLAY_H_
#define IMAGEDISPLAY_H_
#include "../AppRegistry.h"
//#define IMAGE_DEBUG

class ImageDisplay {
protected:
	File *m_imgFile;
	int m_x;
	int m_y;
	int m_totalLen;
public:
	ImageDisplay(File *infile, int x, int y);
	virtual void displayRows(int bmpWidth, int bmpHeight, bool flip,
			uint32_t bmpImageoffset, uint32_t rowSize) =0 ;//{Serial.println("called ImageDisplay::displayRows()");
	//};
	virtual void pushColors(uint16_t *data, uint8_t len, boolean first);
	virtual bool displayFile();
	virtual ~ImageDisplay();
};

#endif /* IMAGEDISPLAY_H_ */
