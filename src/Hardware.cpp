/*
 * Hardware.cpp
 *
 * Provides a simple access point for all the hardware connected
 * If we connect more hardware to the device we need to add access methods here.
 *
 *  Created on: 22/05/2013
 *      Author: roger
 */

#include "Hardware.h"


ILI9341_t3 Graphics(TFT_CS, TFT_DC);
MAX30105 particleSensor;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 371 ohms across the X plate
// measured again on 13/08/14 it floats around a bit but say 85
XPT2046_Touchscreen Touchscreen = XPT2046_Touchscreen(TS_CS,TIRQ_PIN);


Hardware_::Hardware_() {
	m_lsm303 = LSM303();
	// Calibration values. Use the Calibrate example program to get the values for
	// your compass.
	m_lsm303.m_min.x = -880;
	m_lsm303.m_min.y = -691;
	m_lsm303.m_min.z = -958;
	m_lsm303.m_max.x = +262;
	m_lsm303.m_max.y = +365;
	m_lsm303.m_max.z = -27;

	m_lsm303.m_min.x = -495;
	m_lsm303.m_min.y = -463;
	m_lsm303.m_min.z = +393;
	m_lsm303.m_max.x = +495;
	m_lsm303.m_max.y = +279;
	m_lsm303.m_max.z = +627;
	m_compassCorrection = 550;

	//CircularBuffer cb = CircularBuffer(10);

}
/*
 * Put us into hibernate mode. Need to press the restart button to come out of this.
 */
void Hardware_::shutdown() {
	Graphics.setRotation(3);
	Graphics.fillScreen(BLACK);
	Graphics.setTextSize(2);
	Graphics.setCursor(80,Graphics.height()/2);
	Graphics.print(PSTR("sleeping..."));
	delay(1000);
	Graphics.fillScreen(BLACK);
	heartRateInterrupt.reset();
#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("sleeping...."));
#endif
	compass(false);
	Graphics.sleep(true);
	digitalWrite(LED_CONTROL_PIN, LOW);
	pinMode(22, INPUT_PULLUP);
	m_lowPower.DeepSleep(GPIO_WAKE, PIN_22);
	// We get here when we wake up
	digitalWrite(LED_CONTROL_PIN, HIGH);
	blink0();
	blink1();
	Graphics.sleep(false);
	Graphics.begin();
	Graphics.fillScreen(BLACK);
#ifdef HARDWARE_DEBUG
	Serial.begin(9600);
	Serial.println(PSTR("waking...."));
#endif
	setSyncProvider((getExternalTime)Teensy3Clock.get); // resync the clock when we wake up
	//Teensy3Clock.compensate(0);
	startup.run();
}

/*
 * Put us into soft sleep mode.
 */
void Hardware_::sleep() {

#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("dozing...."));
#endif
	compass(false);
	Graphics.sleep(true);
	digitalWrite(LED_CONTROL_PIN, LOW); // this also turns off HR
	sleeping = true;
}

bool Hardware_::isSleeping() {
	return sleeping;
}

/*
 * Wake up from sleep.
 */
void Hardware_::wake() {

	digitalWrite(LED_CONTROL_PIN, HIGH);
	blink0();
	blink1();
	Graphics.sleep(false);
	Graphics.begin();
#ifdef HARDWARE_DEBUG
	Serial.begin(9600);
	Serial.println(PSTR("waking...."));
#endif
	setSyncProvider((getExternalTime)Teensy3Clock.get); // resync the clock when we wake up
	//Teensy3Clock.compensate(0);
	sleeping = false;
}

void Hardware_::init()
{
	pinMode(SD_CS, OUTPUT);
	pinMode(LED0_PIN, OUTPUT);
	pinMode(LED1_PIN, OUTPUT);
	pinMode(LED_CONTROL_PIN, OUTPUT);
	digitalWrite(LED_CONTROL_PIN, HIGH);
	Wire.begin();
	beginSD();
#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("starting LMS303"));
#endif
	m_lsm303.init();
	m_lsm303.enableDefault();
	compass(false);
#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("LMS303 done"));
#endif
	Graphics.begin();
	Graphics.fillScreen(BLACK);
	Graphics.setFont(getDefaultFont());
	Touchscreen.begin();
	m_lowPower = TEENSY3_LP();
	sleeping = false;

#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("tft done...."));
#endif

	if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {//Use default I2C port, 400kHz speed
		Serial.println("MAX30105 was not found. Please check wiring/power. ");
	} else {
		Serial.println(
			"MAX30105 detected");
		particleSensor.setup(); //Configure sensor with default settings
		particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
		particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
	}
}

void Hardware_::playTone(uint16_t frequency, uint32_t duration, uint32_t delay_after) {
#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("tone"));
#endif
	tone(TONE_PIN, frequency,duration);
	delay(delay_after);
	noTone(TONE_PIN);
}
void Hardware_::siren() {
#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("siren"));
#endif
	for (int i=0;i<10;i++) {
		tone(TONE_PIN, 3136+(i*10),10);
		delay(10);
	}
	noTone(TONE_PIN);
}
float Hardware_::getBatteryVoltage() {
//#ifdef HARDWARE_DEBUG
//	Serial.print("Raw voltage ");
//	Serial.println(analogRead(VOLTAGE));
//#endif
	return 0.106129032*analogRead(VOLTAGE);
}

int Hardware_::readInt(File dataFile)
{
	String v = "";
	char t = dataFile.read();
	while (t != ',' && t != -1)
	{
		v.append(t);
		t = dataFile.read();
	}
	return v.toInt();
}
int Hardware_::compassHeading()
{
	m_lsm303.read();
	return m_lsm303.heading((LSM303::vector<int16_t>) {0,-1,0});
}
void Hardware_::compass(bool start)
{
#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("compass(bool start)..."));
#endif
	if (start) {
		m_lsm303.enableDefault();
	} else {
		m_lsm303.writeMagReg(LSM303::MR_REG_M, 0x03);
// This ought to turn off the accelerator and it does,
// but the enableDefault() call above doesn't turn it back on.
//		m_lsm303.writeAccReg(LSM303_CTRL_REG1_A, 0x00);

	}
#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("compass(bool start) done"));
#endif
}
LSM303::vector<int16_t> Hardware_::getAccelerometerValues() {
#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("getAccelerometerValues()..."));
#endif
	m_lsm303.read();
#ifdef HARDWARE_DEBUG
	Serial.println(PSTR("getAccelerometerValues() done"));
#endif
	return m_lsm303.a;
}

void Hardware_::printDirectory(File dir, int numTabs) {
	dir.rewindDirectory();
	while (true) {

		File entry = dir.openNextFile();
		if (!entry) {
			// no more files
			//Serial.println("**nomorefiles**");
			break;
		}
		for (uint8_t i = 0; i < numTabs; i++) {
			Serial.print('\t');
		}
		Serial.print(entry.name());
		if (entry.isDirectory()) {
			Serial.println("/");
			printDirectory(entry, numTabs + 1);
		} else {
			// files have sizes, directories do not
			Serial.print("\t\t");
			Serial.println(entry.size(), DEC);
		}
		entry.close();
	}
}

Hardware_::~Hardware_() {
	// TODO Auto-generated destructor stub
}
void Hardware_::setCompassCorrection(const char *str) {
	 m_compassCorrection = atoi(str);
}
int Hardware_::getCompassCorrection() {
	 return m_compassCorrection;
}

// Copy string from flash to serial port
// Source string MUST be inside a PSTR() declaration!
void Hardware_::progmemPrint(const char *str) {
	char c;
	while ((c = pgm_read_byte(str++)))
		Serial.print(c);
}

// Same as above, with trailing newline
void Hardware_::progmemPrintln(const char *str) {
	progmemPrint(str);
	Serial.println();
}

const char *Hardware_::timeString(long adjustedDate) {
	sprintf(dstring, PSTR("%02d:%02d:%02d"),hour(adjustedDate),minute(adjustedDate),second(adjustedDate));
	return dstring;
}
const char *Hardware_::dateString(long adjustedDate) {
	sprintf(dstring, PSTR("%04d-%02d-%02d"),year(adjustedDate),month(adjustedDate),day(adjustedDate));
	return dstring;
}

bool Hardware_::beginSD() {
	m_sdOK = SD.begin(SD_CS);
#ifdef HARDWARE_DEBUG
	if (!m_sdOK) {
		Serial.println(PSTR("SD initialization failed!"));
	} else {
		Serial.println(PSTR("SD initialization done."));
		dumpSD(PSTR("after SD init"));
	}
#endif
	return m_sdOK;
}
// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t Hardware_::read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t Hardware_::read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

HeartRateInterrupt heartRateInterrupt = HeartRateInterrupt(now());

Hardware_ Hardware = Hardware_();
