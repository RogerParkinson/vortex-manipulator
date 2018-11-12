/*
 * Startup.h
 *
 *  Created on: Oct 14, 2018
 *      Author: roger
 */

#ifndef STARTUP_H_
#define STARTUP_H_
#include "../Hardware.h"


class Startup {
private:
	int row;
public:
	Startup();
	virtual void run();
	virtual void print(const char *s);
	virtual void println(const char *s);
	virtual ~Startup();
};

extern Startup startup;

#endif /* STARTUP_H_ */
