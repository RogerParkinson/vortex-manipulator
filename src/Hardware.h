/*
 * Hardware.h
 *
 *  Created on: 22/05/2013
 *      Author: roger
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_
#include <LSM303.h>
#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SD.h>
#include <Wire.h>
#include <Time.h>
#include <LowPower_Teensy3.h>
#include "heartrate/HeartRateInterrupt.h"
#include <MAX30105.h>

#include <heartRate.h>
#include "ui/Startup.h"
#include <SoftwareSerial.h>
#include <Logger.h>
#include <Timezone.h>   // https://github.com/JChristensen/Timezone
#include <TimeLib.h>    // https://github.com/PaulStoffregen/Time

//#define HARDWARE_DEBUG
#define ICON_DEBUG
#define TS_CS 8
#define TIRQ_PIN  2
#define TFT_DC  9
#define TFT_CS 10
#define SD_CS 15
extern ILI9341_t3 Graphics;

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

#define TONE_PIN 23
#define LED0_PIN 20
#define LED1_PIN 21
#define VOLTAGE 0 // actually A0. This is the battery voltage measure pin 14
#define PULSE_PIN 17 // pin 17 (A3)
#define LED_CONTROL_PIN 3 // controls the LED brightness & power to compass and HRM

#define HEADER_PIXEL(data,pixel) {\
pixel[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4)); \
pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)); \
pixel[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))); \
data += 4; \
}
#define bluetooth Serial1
#define DSTRING_SIZE 60

class Icon {
public:
	unsigned int size;
	const uint16_t *icon;
	bool reversed;
	Icon(const unsigned int s, const uint16_t data[]) {
		size = s;
		icon = data;
		reversed=false;
	};
	void reverse(bool r) {
		reversed = r;
	}
	virtual ~Icon() {
	};
	const void draw(const int x, const int y) {
		if (icon != NULL) {
			int count = 0;
			for (unsigned int j = 0; j < size; j++) {

				for (unsigned int i = 0; i < size; i++) {
					uint16_t pixel = icon[count++];
					if (reversed) {
						pixel = ~pixel;
					}
					Graphics.drawPixel(x + i, y + j, pixel);
				}
			}
		}
	}
};


class Hardware_ {
private:
	Logger *loggerHardware;
	LSM303 m_lsm303;
	char dstring[DSTRING_SIZE];
	bool m_sdOK=false;
	TEENSY3_LP m_lowPower;
	int m_compassCorrection;
	bool sleeping = false;

public:
	Hardware_();
	void init();
	void shutdown();
	void sleep();
	void wake();
	bool isSleeping();
	int compassHeading();
	void compass(bool start);
	void blink0() {
		digitalWrite(LED0_PIN, HIGH);
		delay(50);
		digitalWrite(LED0_PIN, LOW);
	}
	void blink1() {
		digitalWrite(LED1_PIN, HIGH);
		delay(50);
		digitalWrite(LED1_PIN, LOW);
	}
	LSM303::vector<int16_t> getAccelerometerValues();
	bool isSDOK() { return m_sdOK;};
	bool beginSD();
	const char *timeString(long adjustedDate);
	const char *timeString(int hour, int minute, int second);
	const char *dateString(long adjustedDate);
	void setCompassCorrection(const char *str);
	int getCompassCorrection();
	void progmemPrint(const char *str);
	void progmemPrintln(const char *str);
	void printDirectory(File dir, int numTabs);
	int readInt(File dataFile);
	float getBatteryVoltage();
	void playTone(uint16_t frequency, uint32_t duration = 0, uint32_t delay_after = 40);
	void siren();
	const ILI9341_t3_font_t &getDefaultFont() {
		return Arial_10;
	}
	void dumpSD(const char *message) {
		Serial.print(PSTR("dumpSD "));
		Serial.println(message);
		File root = SD.open("/");
		printDirectory(root, 0);
		root.close();
		Serial.print(PSTR("dumpSD done ("));
		Serial.print(message);
		Serial.println(")");
	}
	uint16_t read16(File f);
	uint32_t read32(File f);
	void bufferAccelerometer();
	const char *readBluetooth();
	virtual ~Hardware_();
};

extern Hardware_ Hardware;
extern XPT2046_Touchscreen Touchscreen;
extern ILI9341_t3 Graphics;
extern MAX30105 particleSensor;
extern Timezone nz;


#endif /* HARDWARE_H_ */
