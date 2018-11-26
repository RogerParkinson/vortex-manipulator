// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef VortexManipulator_H_
#define VortexManipulator_H_
#include "Arduino.h"
#include "AppRegistry.h"
#include "heartrate/HeartRateInterrupt.h"
#include "Notification.h"
#include "ui/Gesture.h"
#include "ui/Interval.h"
#include "ui/Startup.h"

//#define VORTEXMANIPULATOR_DEBUG
//#define TOUCH_DEBUG
//#define RUN_STARTUP
#define LOOP_DELAY 5
#define MAX_CYCLE 32000/LOOP_DELAY //32000/LOOP_DELAY
#define TIMESTAMP_CYCLE 30 * ((0.75 * 60 * 1000) /5) // should be 1 minute it is 1:20 or 1.3 so change it to .75 of that => 30
#define TOUCH_DELAY 25
#define LANDING_PAD 30

class Action1: public Action {
public:
	Action1();
	virtual ~Action1();
};
//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
int main(void);
void setup();
void loop();

#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project VortexManipulator here

extern Configuration configuration;
extern Gesture gesture;
extern Startup startup;

//Do not add code below this line
#endif /* VortexManipulator_H_ */
