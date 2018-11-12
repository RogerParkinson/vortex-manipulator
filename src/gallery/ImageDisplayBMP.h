/*
 * ImageDisplayBMP.h
 *
 *  Created on: 3/06/2013
 *      Author: roger
 */

#ifndef IMAGEDISPLAYBMP_H_
#define IMAGEDISPLAYBMP_H_

#include "ImageDisplay.h"

class ImageDisplayBMP: public ImageDisplay {
public:
	ImageDisplayBMP(File *infile, int x, int y);
	virtual void displayRows(int bmpWidth, int bmpHeight,
			bool flip, uint32_t bmpImageoffset, uint32_t rowSize);

	virtual ~ImageDisplayBMP();
};

#endif /* IMAGEDISPLAYBMP_H_ */
