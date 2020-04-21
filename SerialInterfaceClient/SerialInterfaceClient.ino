#include <iq_module_communication.hpp>

IqSerial ser(Serial);
SerialInterfaceClient sic(0);

void setup() {
	ser.begin();

	ser.set(sic.baud_rate_, (uint32_t)9600);
}

void loop() {
}