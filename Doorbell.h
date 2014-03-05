#ifndef DOORBELL
#define DOORBELL

#include "Arduino.h"

extern const byte bell_pin;
extern const unsigned bell_pulse;
extern const byte bell_pattern_len;
extern const byte bell_pattern[];

extern volatile bool bell_rung;

void bell_listen();

#endif
