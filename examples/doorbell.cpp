#include "Doorbell.h"

const byte bell_pin = 2; //can be 2 or 3 (uno)
const unsigned bell_pulse = 400; //pulse length (us)
const byte bell_pattern_len = 10;
const byte bell_pattern[bell_pattern_len] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9
}; //Pattern for your doorbell (find using capture example)

void setup() {
	Serial.begin(9600);
	bell_listen();
}

void loop() {
	if (bell_rung) {
		Serial.println("You rang?");
		delay(2000); //The doorbell yells the same pattern over and over, this stops it triggering the message multiple times
		bell_listen();
	}
}
