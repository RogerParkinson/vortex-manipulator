/*
 * Gesture.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: roger
 */

#include "Gesture.h"


int Gesture::evaluate() {

#ifdef GESTURE_DEBUG
	Serial.println("Gesture::evaluate");
#endif
	LSM303::vector<int16_t> v = Hardware.getAccelerometerValues();
#ifdef GESTURE_DEBUG
	Serial.println("got LSM303");
#endif
	if (isEqual(v, buf_[head_])) {
#ifdef GESTURE_DEBUG
		Serial.println("isequal true");
#endif
		return 0;
	}
#ifdef GESTURE_DEBUG
		Serial.println("isequal false");
#endif
    buf_[head_] = v;
    entries++;
    if (entries >= BUF_SIZE) {
    	entries = BUF_SIZE;
    }
    head_ = (head_ + 1) % BUF_SIZE;

    if(head_ == tail_)
    {
        tail_ = (tail_ + 1) % BUF_SIZE;
    }
	if (entries == BUF_SIZE) {
#ifdef GESTURE_DEBUG
		dump();
//		Serial.print("head ");
//		Serial.print(buf_[head_].z);
//		Serial.print(" tail ");
//		Serial.println(buf_[tail_].z);
#endif
		if ((buf_[tail_].z - buf_[head_].z) > DIFF) {
#ifdef GESTURE_DEBUG
			Serial.print("head ");
			Serial.print(buf_[head_].z);
			Serial.print(" tail ");
			Serial.print(buf_[tail_].z);
			Serial.print(" diff ");
			Serial.println(buf_[tail_].z - buf_[head_].z);
			Serial.println("gesture 1 detected");
#endif
			return 1;
		}
		if ((buf_[head_].z - buf_[tail_].z) > DIFF) {
#ifdef GESTURE_DEBUG
			Serial.print("head ");
			Serial.print(buf_[head_].z);
			Serial.print(" tail ");
			Serial.print(buf_[tail_].z);
			Serial.print(" diff ");
			Serial.println(buf_[head_].z - buf_[tail_].z);
			Serial.println("gesture 2 detected");
#endif
			return 2;
		}
	}
	return 0;
}

void Gesture::clear() {
	head_ = 0;
	tail_ = 0;
}

bool Gesture::isEqual(LSM303::vector<int16_t> a1, LSM303::vector<int16_t> a2) {
	if (!isEqual(a1.x, a2.x) || !isEqual(a1.y, a2.y) || !isEqual(a1.y, a2.y)) {
		return false;
	}
	return true;
}

bool Gesture::isEqual(int a1, int a2) {
	if (abs(a1 - a2) < THRESHOLD) {
		return true;
	}
	return false;
}
void Gesture::dump() {
#ifdef GESTURE_DEBUG
	Serial.println("buffer dump");
	size_t i = tail_;
	for (size_t j=0; j < entries; j++) {
		Serial.print(i);Serial.print(" ");
		dump(buf_[i]);
		i = (i +1) % BUF_SIZE;
	}
	Serial.println("end buffer dump");
	Serial.print("head=");
	Serial.println(head_);
#endif
}

void Gesture::dump(LSM303::vector<int16_t> val) {
    Serial.print(val.x);
    Serial.print(" ");
    Serial.print(val.y);
    Serial.print(" ");
    Serial.print(val.z);
    Serial.println(" ");
}

Gesture::~Gesture() {
	// TODO Auto-generated destructor stub
}

Gesture gesture = Gesture();
