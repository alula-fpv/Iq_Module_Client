#include <iq_module_communication.hpp>

IqSerial ser(Serial);
SystemControlClient sys(0);

void setup() {
	ser.begin();

	// Initialize Serial (for displaying information on the terminal)
	Serial.begin(115200);
}

void loop() {
	float sys_time = 0.0f;

	if(ser.get(sys.time_, sys_time))
		Serial.println(sys_time);
}