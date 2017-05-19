/*-----------------------------------------------------------------------------
 * SingleTact I2C Demo
 * 
 * Copyright (c) 2017 Pressure Profile Systems
 * Licensed under the MIT license. This file may not be copied, modified, or
 * distributed except according to those terms.
 * 
 * 
 * Demonstrates sensor input by reading I2C and display value on comm port.
 * 
 * The circuit: as described in the manual for PC interface using Arduino. 
 * 
 * To compile: Sketch --> Verify/Compile
 * To upload: Sketch --> Upload
 * 
 * For comm port monitoring: Click on Tools --> Serial Monitor
 * Remember to set the baud rate at 57600.
 * 
 * May 2017
 * ----------------------------------------------------------------------------- */


#include <Wire.h> //For I2C/SMBus

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  //TWBR = 12; //Increase i2c speed if you have Arduino MEGA2560, not suitable for Arduino UNO
  Serial.begin(57600);  // start serial for output
  Serial.flush();
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("PPS UK: Changing SingleTact slave address.");
  Serial.println("-----------------END-----------------------");	
}

void loop()
{   
    byte i2cAddress = 0x04; // Slave address (SingleTact), default 0x04
    byte i2cNewAddress = 0x08; // New device address;
    changeSensorAddress(i2cAddress,i2cNewAddress);
    
    delay(100); // Change this if you are getting values too quickly 
}

void changeSensorAddress(short address, short newAddress)
{
  byte i2cPacketLength = 5;//i2c packet length. Just need 6 bytes from each slave
  byte outgoingI2CBuffer[i2cPacketLength];//outgoing array buffer
  outgoingI2CBuffer[0] = 0x02;
  outgoingI2CBuffer[1] = 0x00;
  outgoingI2CBuffer[2] = 0x01;
  outgoingI2CBuffer[3] = newAddress;
  outgoingI2CBuffer[4] = 0xFF;
  
  Wire.beginTransmission(address); // transmit to device existing address
                              // device address is specified in datasheet
  Wire.write(outgoingI2CBuffer, i2cPacketLength);            // sends value byte  
  Wire.endTransmission();     // stop transmitting
}


