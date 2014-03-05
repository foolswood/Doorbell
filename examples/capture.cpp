const byte doorbell_pin = 2; //can be 2 or 3 (uno)
const unsigned pulse = 100; //Length of pulse (micros)

void setup() {
	Serial.begin(9600);
}

inline byte to_pulse(const unsigned long diff) {
	//Convert a time delta to a number of pulses
	unsigned l = diff/pulse;
	if ((diff - (l*pulse)) > pulse/2) {
		l++;
	}
	if (l > 255) { //Timeout
		return 0;
	}
	return l;
}

byte capture(const byte capsize, byte* const cap) {
	//Returns number of bytes captured
	unsigned long now, prev;
	byte i, state;
	//Wait to go low
	while (digitalRead(doorbell_pin) == HIGH) {}
	while (digitalRead(doorbell_pin) == LOW) {}
	//Rising
	prev = micros();
	state = HIGH;
	for (i=0; i<capsize; i++) {
		while (digitalRead(doorbell_pin) == state) {} //Wait for change
		now = micros();
		cap[i] = to_pulse(now-prev);
		if (cap[i] == 0) { //Timeout (or pulse too long)
			break;
		}
		state = (state == LOW) ? HIGH : LOW; //HIGH->LOW, LOW->HIGH
		prev = now;
	}
	return i;
}

void print_pattern(const byte* const pattern, const byte length) {
	//Print out an array of bytes
	byte i;
	for (i=0; i<length; i++) {
		Serial.print(pattern[i]);
		Serial.print(" ");
	}
	Serial.print("\n");
}

void loop() {
	byte cap[255];
	byte caplen = capture(255, cap);
	Serial.print("Pattern (");
	Serial.print(caplen);
	Serial.print(")\n");
	print_pattern(cap, caplen);
}
