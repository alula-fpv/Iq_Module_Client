#include <iq_module_communication.hpp>

IqSerial ser(Serial);
ServoInputParserClient svo(0);

void setup() {
	ser.begin();

	ser.set(svo.mode_, (uint8_t)1); // Set to Voltage mode
	ser.save(svo.mode_);
}

void loop() {
}