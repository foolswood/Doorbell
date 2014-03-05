#include "Doorbell.h"

volatile bool bell_rung = false;

static inline bool is_len(byte n, unsigned p) {
	//Returns true if the measured pulse time is within bounds of the expected pulse time.
	if (p > (bell_pulse*n - bell_pulse/2) && p < ((bell_pulse*n) + bell_pulse/2))
		return true;
	return false;
}

static void bell_interrupt() {
	static byte p = 0;
	static unsigned long prev = 0;
	unsigned long now = micros();
	if (p || digitalRead(bell_pin) == LOW) {
		//The first pulse in the pattern is high, so trigger on the falling edge.
		if (is_len(bell_pattern[p++], now - prev)) {
			if (p == bell_pattern_len) {
				detachInterrupt(bell_pin-2);
				bell_rung = true;
				p = 0;
			}
		} else {
			p = 0;
		}
	}
	prev = now;
}

void bell_listen() {
	//Start listening for the bell
	bell_rung = false;
	attachInterrupt(bell_pin-2, bell_interrupt, CHANGE); //uno
}
