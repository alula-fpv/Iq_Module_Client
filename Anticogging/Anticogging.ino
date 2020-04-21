#include <iq_module_communication.hpp>
IqSerial ser(Serial);
BrushlessDriveClient mot(0);
AnticoggingClient cog(0);
void setup() {
ser.begin();
ser.set(mot.drive_spin_volts_,0.0f);
}
void loop() {
// Spin the motor with your hand and feel Anticogging turning on and off
ser.set(cog.is_enabled_,(uint8_t)1);
delay(4000);
ser.set(cog.is_enabled_,(uint8_t)0);
delay(4000);
}
