#include <iq_module_communication.hpp>

IqSerial ser(Serial);
TemperatureMonitorUcClient tmp(0);

void setup() {
	ser.begin();

	// Initialize Serial (for displaying information on the terminal)
	Serial.begin(115200);
}

void loop() {
	float temperature = 0.0f; 

	if(ser.get(tmp.uc_temp_, temperature))
		Serial.println(temperature);
}