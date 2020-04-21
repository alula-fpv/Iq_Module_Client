#include <iq_module_communication.hpp>

IqSerial ser(Serial2);
MultiTurnAngleControlClient mult(0);

void setup() {
	ser.begin();
}

void loop() {
	ser.set(mult.tranjectory_angular_displacement_, 3.14f);
	ser.set(mult.tranjectory_duration_, 0.5f);
	ser.set(mult.tranjectory_angular_displacement_, 0.0f);
	ser.set(mult.tranjectory_duration_, 0.5f);
	delay(1000);
}
