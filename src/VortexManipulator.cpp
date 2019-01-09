#include "VortexManipulator.h"

int cycle = 0;
int timestampCycle = TIMESTAMP_CYCLE;
unsigned long lastEventMicros=0;
IntervalTimer hrTimer;
IntervalTimer logTimer;
String command;
Intervals intervals;
IntervalCycle *intervalHardwareSleep;

LoggerFactory loggerFactory = LoggerFactory(false);
Logger *loggerVM;
Logger *loggerTouch;
Logger *loggerGesture;

class HRAction : public Action {
public:
	HRAction(){};
	virtual const char* getName() {return PSTR("HRAction");};
	virtual boolean execute() {
		heartRateInterrupt.calculate(0);
		return true;
	}
	virtual ~HRAction(){};
};
class HRLogAction : public Action {
public:
	HRLogAction(){};
	virtual const char* getName() {return PSTR("HRLogAction");};
	virtual boolean execute() {
		loggerVM->debug(getName());
		heartRateInterrupt.log();
		return true;
	}
	virtual ~HRLogAction(){};
};

class GestureWake : public Action {
public:
	GestureWake(){};
	virtual const char* getName() {return PSTR("GestureWake");};
	virtual boolean execute() {
		int currentGesture = gesture.evaluate();
		bool asleep = Hardware.isSleeping();
		if (asleep && (currentGesture == 1)) {
			loggerGesture->debug(PSTR("waking from gesture"));
			Hardware.wake();
			Appregistry.getCurrentApp()->setup();
			Appregistry.getCurrentApp()->display();
			return true;
		}
		if (!asleep && (currentGesture == 2)) {
			loggerGesture->debug(PSTR("sleeping from gesture"));
			Hardware.sleep();
			return true;
		}
		return false;
	}
	virtual ~GestureWake(){};
};
class HardwareSleep : public Action {
public:
	HardwareSleep(){};
	virtual const char* getName() {return PSTR("HardwareSleep");};
	virtual boolean execute() {
		loggerVM->debug(getName());
		Hardware.sleep();
		cycle = 0; // if we get here then start again.
		Appregistry.getCurrentApp()->setup();
		Appregistry.getCurrentApp()->display();
		return true;
	}
	virtual ~HardwareSleep(){};
};
class TouchDelay: public Action {
private:
	TS_Point convertPoint(TS_Point p,uint8_t rotation) {
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
		p.x = x;
		p.y = y;
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

public:
	TouchDelay(){};
	virtual const char* getName() {return PSTR("TouchDelay");};
	virtual boolean execute() {
//		loggerTouch->debug(getName());
		boolean istouched = Touchscreen.touched();
		bool asleep = Hardware.isSleeping();
		if (istouched) {
			loggerTouch->debug("%s ::execute istouched=true",getName());
			if (asleep) {
				loggerTouch->debug("%s %s",getName(),PSTR("waking from touch"));
				Hardware.wake();
				Appregistry.getCurrentApp()->setup();
				Appregistry.getCurrentApp()->display();
				lastEventMicros = micros();
			}
			intervalHardwareSleep->reset();
//			loggerTouch->debug("%s %s",getName(),PSTR("reset done"));
			uint8_t rotation = Graphics.getRotation();
			TS_Point lastPoint = convertPoint(Touchscreen.getPoint(),rotation);
			loggerTouch->debug("r=%d x=%d y=%d z=%d" ,rotation,lastPoint.x,lastPoint.y,lastPoint.z);
			if (isLandingPad(lastPoint,rotation)) {
				loggerTouch->debug("%s %s",getName(),PSTR("(main)Switching to menu"));
				Graphics.setRotation(3);
				Appregistry.jumpToMenu();
				return true;
			}
//			loggerTouch->debug("%s invoking app %s",getName(),Appregistry.getCurrentApp()->getName());
			if (!Appregistry.getCurrentApp()->touch(lastPoint)) {
				Appregistry.jumpToMenu();
				return true;
			}
			return true;
		}
		return false;
	}
	virtual ~TouchDelay(){};
};
class SerialCheck : public Action {
public:
	SerialCheck(){};
	virtual const char* getName() {return PSTR("SerialCheck");};
	virtual boolean execute() {
		const char* buffer = Hardware.readBluetooth();
		if (buffer == NULL) {
			return true;
		}
		loggerVM->debug("from bluetooth [%s]",buffer);
		App *notification = Appregistry.getApp("Notification");
		Notification *n = (Notification *)notification;
		n->addMessage(buffer);
		return true;
	}
	virtual ~SerialCheck(){};
};

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may now be available.
*/
//char buffer[1000];
//void serialEvent() {
//	  int i = 0;
//	  while(Serial.available()) buffer[i++] = Serial.read();
//	  buffer[i] = 0;
//	  Serial.print("serialEvent received: ");
//	  Serial.println(buffer);
//	  if (strcmp(&buffer[0],"GD")==0) {
//		Serial.print("gesture = ");
//		gesture.dump();
//		return;
//	  }
//	  if (strcmp(&buffer[0],"GC")==0) {
//		Serial.println("Gesture clear");
//		gesture.clear();
//		Serial.print("gesture = ");
//		gesture.dump();
//		return;
//	  }
//	  App *notification = Appregistry.getApp("Notification");
//	  Notification *n = (Notification *)notification;
//	  n->addMessage(buffer);
//}
void setup() {
	setSyncProvider((getExternalTime)Teensy3Clock.get);
	Serial.begin(9600);
	loggerFactory.add("VM",LOG_LEVEL_INFOS);
	loggerFactory.add("AppRegistry",LOG_LEVEL_ERRORS);
	loggerFactory.add("TOUCH",LOG_LEVEL_DEBUG);
	loggerFactory.add("GESTURE",LOG_LEVEL_ERRORS);
	loggerFactory.add("Notification",LOG_LEVEL_ERRORS);
	loggerFactory.add("Hardware",LOG_LEVEL_ERRORS);
	loggerFactory.add("Menu",LOG_LEVEL_ERRORS);
	loggerFactory.add("Gallery",LOG_LEVEL_ERRORS);
	loggerFactory.add("Dalek",LOG_LEVEL_ERRORS);
	loggerFactory.add("HRM",LOG_LEVEL_ERRORS);

	loggerVM = loggerFactory.getLogger("VM");
	loggerTouch = loggerFactory.getLogger("TOUCH");
	loggerGesture = loggerFactory.getLogger("GESTURE");

	loggerVM->info("Vortex Manipulator version %s\n",VERSION);
	Hardware.init();
	configuration.load();
#ifdef RUN_STARTUP
	startup.run();
#endif
	Appregistry.init();
	noInterrupts();
	interrupts();
	loggerVM->debug("Screen: width = %d height = %d\n",Graphics.width(),Graphics.height());

	intervals.create(10L,new HRAction()); // 10 milliseconds
	intervals.create(10*60*1000L,new HRLogAction()); // 10 minutes
	intervals.create(50L,new GestureWake());
	intervals.create(100L,new SerialCheck());
	intervalHardwareSleep = new IntervalCycle(MAX_CYCLE,new HardwareSleep());
	intervals.create(intervalHardwareSleep);
	intervals.create(new IntervalCycle(TOUCH_DELAY,new TouchDelay()));
	loggerVM->debug("setup complete\n");
}

void recordTimestamp() {
	if (timestampCycle++ > TIMESTAMP_CYCLE) {  // every 30 mins
		loggerVM->debug("writing timestamp... \n%d %s",timestampCycle,Hardware.timeString(now()));
		timestampCycle = 0;
		File timestampFile = SD.open(PSTR("ts.txt"), FILE_WRITE);
		loggerVM->debug("%s",timestampFile);
		if (timestampFile) {
			loggerVM->debug("writing timestamp");
			timestampFile.print(Hardware.dateString(now()));
			timestampFile.print(BLANK);
			timestampFile.println(Hardware.timeString(now()));
			timestampFile.close();
			loggerVM->debug("finished writing timestamp");
		}
	}
}

void loop() {
//	recordTimestamp();
	intervals.check();
	
	bool asleep = Hardware.isSleeping();

	// refresh the current app if its update interval was reached.
	unsigned long m = micros();
	if ((m-lastEventMicros) > Appregistry.getCurrentApp()->getUpdateInterval()) {
		if (!asleep) {
			Appregistry.getCurrentApp()->display();
		}
		lastEventMicros = m;
	}
	delay(LOOP_DELAY);
}
#ifdef __cplusplusINTERVAL_DEBUG
int main(void) {
	_init_Teensyduino_internal_();

	setup();

	while (1) {
		loop();
	}
}
#endif
