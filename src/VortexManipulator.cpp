#include "VortexManipulator.h"

int cycle = 0;
int timestampCycle = TIMESTAMP_CYCLE;
unsigned long lastEventMicros=0;
IntervalTimer hrTimer;
IntervalTimer logTimer;
String command;
Intervals intervals;

void checkPulse() { // triggered when Timer fires
	volatile int signal = 0;//analogRead(PULSE_PIN); // read the Pulse Sensor
	heartRateInterrupt.calculate(signal);
} // end isr

//void logPulse() { // triggered when Timer fires
//	heartRateInterrupt.log();
//} // end isr
class HRAction : public Action {
public:
	HRAction(){};
	virtual const char* getName() {return PSTR("HRAction");};
	virtual void execute() {
		heartRateInterrupt.calculate(0);
	}
	virtual ~HRAction(){};
};
class HRLogAction : public Action {
public:
	HRLogAction(){};
	virtual const char* getName() {return PSTR("HRLogAction");};
	virtual void execute() {
		Serial.print("firing ");
		Serial.println(getName());
		heartRateInterrupt.log();
	}
	virtual ~HRLogAction(){};
};

TS_Point convertPoint(TS_Point p,uint8_t rotation) {
//#ifdef VORTEXMANIPULATOR_DEBUG
//		Serial.println(PSTR("---"));
//		Serial.print(PSTR("loop:touch(raw) "));
//		Serial.print(p.x);
//		Serial.print(BLANK);
//		Serial.print(p.y);
//		Serial.print(BLANK);
//		Serial.print(p.z);
//		Serial.print(PSTR(" rotation: "));
//		Serial.println(rotation);
//#endif
		int x = 0;
		int y = 0;

		switch (rotation) {
		case 0:
			y = map(p.x,TS_MINX, TS_MAXX, Graphics.width(), 0);
			x = Graphics.height() - map(p.y, TS_MINY, TS_MAXY, Graphics.height(), 0);
			break;
		case 1:
			y = map(p.y, TS_MINY, TS_MAXY, 0, Graphics.height());
			x = map(p.x, TS_MINX, TS_MAXX, 0, Graphics.width());
			break;
		case 2:
			// TODO:
			break;
		case 3:
		    y = map(p.y, TS_MINY, TS_MAXY, Graphics.height(), 0 );
		    x = map(p.x, TS_MINX, TS_MAXX, Graphics.width(), 0 );
			break;
		}
//#ifdef VORTEXMANIPULATOR_DEBUG
//		Graphics.fillRect(0,0,Graphics.width(),10,BLACK);
//		Graphics.setCursor(0,0);
//		Graphics.print(PSTR("raw "));
//		Graphics.print(p.x);
//		Graphics.print(BLANK);
//		Graphics.print(p.y);
//		Graphics.print(PSTR(" adj "));
//		Graphics.print(x);
//		Graphics.print(BLANK);
//		Graphics.print(y);
//		Graphics.print(PSTR(" w: "));
//		Graphics.print(Graphics.width());
//		Graphics.print(PSTR(" h: "));
//		Graphics.print(Graphics.height());
//		Graphics.print(PSTR(" r: "));
//		Graphics.print(rotation);
////		Graphics.drawPixel(x, y, YELLOW);
//#endif
		p.x = x;
		p.y = y;
//#ifdef VORTEXMANIPULATOR_DEBUG
//		Serial.print(PSTR("loop:touch(revised) "));
//		Serial.print(p.x);
//		Serial.print(BLANK);
//		Serial.println(p.y);
//#endif
	return p;
}
boolean isLandingPad(TS_Point p, uint8_t rotation) {
	switch (rotation) {
	case 0:
		return p.y < LANDING_PAD;
	case 3:
		return p.x < LANDING_PAD;
	default:
		return false;
	}
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data maynow() be available.
*/
char buffer[1000];
void serialEvent() {
	  int i = 0;
	  while(Serial.available()) buffer[i++] = Serial.read();
	  buffer[i] = 0;
	  Serial.print("serialEvent received: ");
	  Serial.println(buffer);
	  if (strcmp(&buffer[0],"GD")==0) {
		Serial.print("gesture = ");
		gesture.dump();
		return;
	  }
	  if (strcmp(&buffer[0],"GC")==0) {
		Serial.println("Gesture clear");
		gesture.clear();
		Serial.print("gesture = ");
		gesture.dump();
		return;
	  }
	  App *notification = Appregistry.getApp("Notification");
	  Notification *n = (Notification *)notification;
	  n->addMessage(buffer);
}
void setup() {
	setSyncProvider((getExternalTime)Teensy3Clock.get);
	Serial.begin(9600);
#ifdef VORTEXMANIPULATOR_DEBUG
	while (!Serial) {
	    ; // wait for serial port to connect. Needed for native USB
	}
	Serial.print(VERSION);
	Serial.println(" starting...");
#endif
	Hardware.init();
	configuration.load();
#ifdef RUN_STARTUP
	startup.run();
#endif
	Appregistry.init();
	noInterrupts();
//	hrTimer.begin(checkPulse,2000);
//	logTimer.begin(logPulse,600000000); // 10 minutes=600000000
	interrupts();
#ifdef VORTEXMANIPULATOR_DEBUG
	Serial.print("Screen: width = ");
	Serial.print(Graphics.width());
	Serial.print(" height = ");
	Serial.println(Graphics.height());
	Serial.println("end of setup");
	Serial.read();
#endif
//	intervals.create(10000L,new TestAction());
	intervals.create(10L,new HRAction()); // 10 seconds (too long?)
	intervals.create(10*60*1000L,new HRLogAction()); // 10 minutes
}

void recordTimestamp() {
	if (timestampCycle++ > TIMESTAMP_CYCLE) {  // every 30 mins
#ifdef VORTEXMANIPULATOR_DEBUG
		Serial.println("writing timestamp... ");
		Serial.print(timestampCycle);
		Serial.print(BLANK);
		Serial.println(Hardware.timeString(now()));
#endif
		timestampCycle = 0;
		File timestampFile = SD.open(PSTR("ts.txt"), FILE_WRITE);
#ifdef VORTEXMANIPULATOR_DEBUG
		Serial.println(timestampFile);
#endif
		if (timestampFile) {
#ifdef VORTEXMANIPULATOR_DEBUG
			Serial.println("writing timestamp");
#endif
			timestampFile.print(Hardware.dateString(now()));
			timestampFile.print(BLANK);
			timestampFile.println(Hardware.timeString(now()));
			timestampFile.close();
#ifdef VORTEXMANIPULATOR_DEBUG
			Serial.println("finished writing timestamp");
#endif
		}
	}
}

void loop() {
	cycle++;
//	recordTimestamp();
	intervals.check();
	
	// Check the gesture status every 100 cycles.
	bool asleep = Hardware.isSleeping();
	if (cycle > 1000000) {
		int currentGesture = gesture.evaluate();
		if (asleep && (currentGesture == 1)) {
#ifdef VORTEXMANIPULATOR_DEBUG
			Serial.println(PSTR("waking from gesture"));
#endif
			Hardware.wake();
			cycle = 0;
			Appregistry.getCurrentApp()->setup();
			Appregistry.getCurrentApp()->display();
#ifdef VORTEXMANIPULATOR_DEBUG
			Serial.println(PSTR("called display #1"));
#endif
		}
		if (!asleep && (currentGesture == 2)) {
#ifdef VORTEXMANIPULATOR_DEBUG
			Serial.println(PSTR("sleeping from gesture"));
#endif
//			Hardware.sleep();
			cycle = 0;
		}
	}

	boolean istouched = Touchscreen.touched();
	if (istouched && cycle > TOUCH_DELAY) {
		if (asleep) {
#ifdef VORTEXMANIPULATOR_DEBUG
			Serial.println(PSTR("waking from touch"));
#endif
			Hardware.wake();
			Appregistry.getCurrentApp()->setup();
			Appregistry.getCurrentApp()->display();
#ifdef VORTEXMANIPULATOR_DEBUG
			Serial.println(PSTR("called display #2"));
#endif
			lastEventMicros = micros();
		}
		cycle = 0; // Ensure we don't sleep if we are operating.
		uint8_t rotation = Graphics.getRotation();
		TS_Point lastPoint = convertPoint(Touchscreen.getPoint(),rotation);
#ifdef TOUCH_DEBUG
		Serial.print("r = ");
		Serial.print(rotation);
		Serial.print(" x = ");
		Serial.print(lastPoint.x);
		Serial.print(" y = ");
		Serial.print(lastPoint.y);
		Serial.print(" z = ");
		Serial.println(lastPoint.z);
#endif
		if (isLandingPad(lastPoint,rotation)) {
#ifdef VORTEXMANIPULATOR_DEBUG
			Serial.println(PSTR("(main)Switching to menu"));
#endif
			Graphics.setRotation(3);
			Appregistry.jumpToMenu();
			return;
		}
#ifdef VORTEXMANIPULATOR_DEBUG
		Serial.print(PSTR("invoking app "));
		Serial.println(Appregistry.getCurrentApp()->getName());
#endif
		if (!Appregistry.getCurrentApp()->touch(lastPoint)) {
			Appregistry.jumpToMenu();
			return;
		}
	}
	unsigned long m = micros();
	if ((m-lastEventMicros) > Appregistry.getCurrentApp()->getUpdateInterval()) {
		if (!asleep) {
			Appregistry.getCurrentApp()->display();
#ifdef VORTEXMANIPULATOR_DEBUG
//			Serial.println(PSTR("called display #3"));
#endif
		}
		lastEventMicros = m;
	}
	// if we pass max cycles then invoke the shutdown.
	if (cycle > MAX_CYCLE) {
#ifdef VORTEXMANIPULATOR_DEBUG
		Serial.println(PSTR("sleep"));
#endif
		Hardware.sleep();
		cycle = 0; // if we get here then start again.
		Appregistry.getCurrentApp()->setup();
		Appregistry.getCurrentApp()->display();
#ifdef VORTEXMANIPULATOR_DEBUG
//			Serial.println(PSTR("called display #4"));
#endif
	}
	delay(LOOP_DELAY);
}
#ifdef __cplusplus
int main(void) {
	_init_Teensyduino_internal_();

	setup();

	while (1) {
		loop();
	}
}
#endif
