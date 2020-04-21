#include <iq_module_communication.hpp>

IqSerial ser(Serial);
PowerMonitorClient pwr(0);

void setup() {
	ser.begin();

	// Initialize Serial (for displaying information on the terminal)
	Serial.begin(115200);
}

void loop() {
	float voltage = 0; 
	if(ser.get(pwr.volts_,voltage))
		Serial.println(voltage);
}
