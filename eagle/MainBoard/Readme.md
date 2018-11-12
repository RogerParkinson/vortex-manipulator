Main board for the Vortex Manipulator
==

Main components:

 * Teensy 3.2 board. This holds the processor and the USB connector. It also has an on board clock powered by the small battery.
 * MicroSD. This holds configuration files and images. Heart rate logs go here.
 * LSM303 which provides a compass and an accelerometer.
 * LIPO charger circuit which charges the LIPO battery when the USB is connected.
 * Through hole connectors for the ILI9841 touch screen and various other connectors.
 
In addition to the ILI9341 connector strip on the main board there is a second strip just above it which has the following:

 * GND
 * Wake pulling this low (by the pushbutton) wakes us from shutdown mode.
 * Tone connects to the speaker.
 * LED1 connects to one of the LEDs.
 * LED2 connects to one of the LEDs.
 * Pulse no longer used.
 * Power no longer used.
 * Rx not yet used but connects to the Rx of the Teensy.
 * Tx not yet used but connects to the Tx of the Teensy.
 
A third strip just in front of the Teensy has some connectors that expose the under side connections of the Teensy for future expansion. These are:

 * A13
 * 33
 * 32
 * 31
 * 30
 * 29
 * A12

The [MAX30102 heart rate monitor](https://www.aliexpress.com/item/Low-Power-MAX30102-Heart-Rate-Oxygen-Pulse-Breakout-for-Arduino-Replace-MAx30100/32892216359.html?spm=a2g0s.9042311.0.0.27424c4dVejVpp) is connected directly to the Teensy SDA and SCL pins, plus 3.3v power and GND.

Finally the Teensy on-board clock needs a backup coin cell battery connected to the battery and GND connectors on the Teensy.
 
<a href="https://oshpark.com/shared_projects/zJDmyNc4"><img src="https://oshpark.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park"></img></a>