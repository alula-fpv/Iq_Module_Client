/*
* IQ Motion Control spin and report demo.
*
* This code will comand a motor to spin at various voltage and 
* simultaniously report the motor's position and velocity over USB
*
*
* The circuit: 
*   Serial1 RX is directly connected to motor TX(Red)
*   Serial2 TX is directly connected to motor RX(White)
*
* Created 2018/10/8 by Matthew Piccoli
* 
* This example coode is in public domain.
*/

// USER SETABLE VALUES HERE
// Voltage step size
const float kVoltageStep = 0.01f;
// Max voltage
const float kVoltageMax = 0.25f;
// END USER SETABLE VALUES

// Includes required for communication
// Message forming interface
#include <generic_interface.hpp>
// Clients that speaks to module's objects
#include <brushless_drive_client.hpp>

#include <iq_module_communication.hpp>
IqSerial ser(Serial);
// Make a communication interface object
GenericInterface com;
// Make a objects that talk to the module 
BrushlessDriveClient mot(0);
void setup(){
	// Initialize USB communication
	ser.begin(115200);
}

void loop(){
	static float voltage_to_set = 0.0f;
	static float voltage_sign = 1.0f;

	//Update voltage command
	if(abs(voltage_to_set) >= kVoltageMax)
	{
		voltage_sign = - 1 * voltage_sign;
	}
	voltage_to_set += kVoltageStep * voltage_sign;

	SendMessages(voltage_to_set);
	ReceiveMessages();
	DoSomethingWithMessages();

	delay(100);
}

void SendMessages(float voltage_command)
{
	//This buffer is for passing around messages;
	uint8_t communication_buffer[64];
	//Stores length of message to send or receive
	uint8_t communication_length;

	//Generate the set message
	mot.drive_spin_volts_.set(com, voltage_command);

	//Generate the get message
	mot.obs_angle_.get(com);
	mot.obs_velocity_.get(com);

	//Grab outbound message in the com queue, stor into buffer
	//If it is transferred something to communication buffer.. 
	if(com.GetTxBytes(communication_buffer, communication_length))
	{
		//Use Arduino serial hardware to send messages 
		Serial.write(communication_buffer, communication_length);       // changed serial1 to serial
	}

	Serial.print("Setting voltage:");
	Serial.print(voltage_command);
	Serial.println();
}

void ReceiveMessages()
{
	// This buffer is for passing around messages.
	uint8_t communication_buffer[64];
	// Stores length of message to send or receive
	uint8_t communication_length;

	// Reads however many bytes are currently available 
	communication_length = Serial.readBytes(communication_buffer, Serial.available());
	// Puts the recently read bytes into coms reveive queue
	com.SetRxBytes(communication_buffer, communication_length);
	uint8_t *rx_data; // temporary pointer to receive type+data bytes
	uint8_t rx_length; // number of received type+data bytes
	// while we have message packets to parse
	while(com.PeekPacket(&rx_data, &rx_length))
	{
		// Share that packet with all client objects
		mot.ReadMsg(rx_data, rx_length);
		// Once we are done with the message packcet, drop it
		com.DropPacket();
	}
}

void DoSomethingWithMessages()
{
	// Check if we have any fresh data
	// Checking for fresh data is not required, it simply
	// lets you know if you received a message that you 
	// have not yet read. 

	//Check for a new angle message
	if(mot.obs_angle_.IsFresh()) {
		Serial.print("Angle: ");
		Serial.print(mot.obs_angle_.get_reply());
		Serial.println();
	}
}

