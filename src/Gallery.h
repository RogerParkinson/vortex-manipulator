/*
 * Gallery.h
 *
 *  Created on: 28/04/2013
 *      Author: roger
 */


// See the readme for file format.

#ifndef Gallery_H_
#define Gallery_H_
#include "AppRegistry.h"
//#include "gallery/ImageDisplayBMP.h"
//#include "gallery/ImageDisplayTFT.h"
//#include "gallery/ImageDisplay.h"

//#define GALLERY_DEBUG

// Larger buffers are slightly more efficient, but if
// the buffer is too large, extra data is read unnecessarily.
// For example, if the image is 240 pixels wide, a 100
// pixel buffer will read 3 groups of 100 pixels.  The
// last 60 pixels from the 3rd read may not be used.

#define BUFFPIXEL 80

class Gallery : public App {
private:
	virtual char *findNextFile();
	virtual void setup();
	File m_root;
	char m_lastName[20];
	Logger *logger;

public:
	Gallery();
	virtual unsigned long getUpdateInterval() {return 1000000UL;};
	virtual void init();
	virtual void display();
	virtual boolean touch(TS_Point p);
	virtual const char* getName() {return PSTR("Gallery");};
	void imgDraw(char *filename, int x, int y);
	virtual ~Gallery();
};

#endif /* Gallery_H_ */



