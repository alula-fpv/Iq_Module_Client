# include <iq_module_communication.hpp>

IqSerial ser(Serial);
BrushlessDriveClient mot(0);

void setup(){
	ser.begin();
}

void loop() {
	ser.set(mot.drive_spin_pwm_, 1.0f); // Drives the motor with the mentioned volt, 1.0 V in this case
}
