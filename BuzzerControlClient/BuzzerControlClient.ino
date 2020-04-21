#include <iq_module_communication.hpp>

IqSerial ser(Serial2);
BuzzerControlClient buz(0);

void setup() {
ser.begin();
}

void loop() {
	ser.set(buz.hz_, (uint16_t)1000);
	ser.set(buz.volume_, (uint8_t)127);
	ser.set(buz.duration_, (uint16_t)500);
	ser.set(buz.ctrl_note_);
	delay(1000);
}
