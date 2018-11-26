/*
 * Gesture.h
 *
 *  Created on: Jul 4, 2018
 *      Author: roger
 */

#ifndef GESTURE_H_
#define GESTURE_H_

#include "../AppRegistry.h"
#include <LSM303.h>
//#define GESTURE_DEBUG

#define BUF_SIZE 10
#define THRESHOLD 1000
#define DIFF 1500

class Gesture {
public:
	Gesture() {
		buf_ = new LSM303::vector<int16_t>[BUF_SIZE];
	}
	int evaluate();
	void clear();
	void dump();
	void dump(LSM303::vector<int16_t>);
	virtual ~Gesture();
private:
	bool isEqual(LSM303::vector<int16_t>, LSM303::vector<int16_t>);
	bool isEqual(int, int);
	LSM303::vector<int16_t> *buf_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t entries = 0;
};

extern Gesture gesture;

#endif /* GESTURE_H_ */

