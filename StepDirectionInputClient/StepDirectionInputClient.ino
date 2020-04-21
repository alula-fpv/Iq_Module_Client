#include <iq_module_communication.hpp>

IqSerial ser(Serial);
StepDirectionInputClient sdi(0);

void setup() {
	ser.begin();

	ser.set(sdi.angle_step_, 0.125f); // Set to 8 edges per rotation
	ser.save(sdi.angle_step_);
}

void loop() {

}