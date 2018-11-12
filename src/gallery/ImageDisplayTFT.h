/*
 * ImageDisplayTFT.h
 *
 *  Created on: 3/06/2013
 *      Author: roger
 */

#ifndef IMAGEDISPLAYTFT_H_
#define IMAGEDISPLAYTFT_H_

#include "ImageDisplay.h"

class ImageDisplayTFT: public ImageDisplay {
public:
	ImageDisplayTFT(File *infile, int x, int y);
	virtual void displayRows(int bmpWidth,
			int bmpHeight, bool flip, uint32_t bmpImageoffset, uint32_t rowSize);
	virtual ~ImageDisplayTFT();
};

#endif /* IMAGEDISPLAYTFT_H_ */
