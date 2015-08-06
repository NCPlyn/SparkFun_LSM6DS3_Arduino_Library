/******************************************************************************
LowLevelExample.ino

Example using the LSM6DS3 with ONLY read and write methods.  It's up to you to
read the datasheets and get the sensor to behave as you will.

This sketch saves a significant amount of memory because the settings and complex
math (such as floating point variables) don't exist.

Marshall Taylor @ SparkFun Electronics
May 20, 2015
https://github.com/sparkfun/LSM6DS3_Breakout

Resources:
Uses Wire.h for i2c operation
Uses SPI.h for SPI operation

Development environment specifics:
Arduino IDE 1.6.4
Teensy loader 1.23

Hardware connections:
Connect I2C SDA line to A4
Connect I2C SCL line to A5
Connect GND and 3.3v power to the IMU

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given.
******************************************************************************/
#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "SPI.h"

//uint16_t errorsAndWarnings = 0;

LSM6DS3Core myIMU( I2C_MODE, 0x6B );
//LSM6DS3Core myIMU( SPI_MODE, 10 );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000); //relax...
  Serial.println("Sketch came out of reset.\n");
  
  //Call .beginCore() to configure the IMU
  if( myIMU.beginCore() != 0 )
  {
    Serial.print("Error at beginCore().\n");
  }
  else
  {
    Serial.print("\nbeginCore() passed.\n");
  }

  //Error accumulation variable
	uint8_t errorAccumulator = 0;
  
  uint8_t dataToWrite = 0;  //Temporary variable

  //Setup the accelerometer******************************
  dataToWrite = 0; //Start Fresh!
  dataToWrite |= LSM6DS3_ACC_GYRO_BW_XL_200Hz;
  dataToWrite |= LSM6DS3_ACC_GYRO_FS_XL_2g;
  dataToWrite |= LSM6DS3_ACC_GYRO_ODR_XL_416Hz;

  // //Now, write the patched together data
  errorAccumulator += myIMU.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, dataToWrite);

  //Set the ODR bit
  errorAccumulator += myIMU.readRegister(&dataToWrite, LSM6DS3_ACC_GYRO_CTRL4_C);
  dataToWrite &= ~((uint8_t)LSM6DS3_ACC_GYRO_BW_SCAL_ODR_ENABLED);


    // Write 00h into WAKE_UP_DUR 
	errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_WAKE_UP_DUR, 0x00 );

    // Set FF threshold (FF_THS[2:0] = 011b)
    // Set six samples event duration (FF_DUR[5:0] = 000110b)
    // Write 33h into FREE_FALL 
    errorAccumulator += myIMU.writeRegister(LSM6DS3_ACC_GYRO_FREE_FALL, 0x33);

    // FF interrupt driven to INT1 pin
    // Write 10h into MD1_CFG
	errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_MD1_CFG, 0x10 );
    // Also route to INT2 pin
    // Write 10h into MD1_CFG
	errorAccumulator += myIMU.writeRegister( LSM6DS3_ACC_GYRO_MD2_CFG, 0x10 );
	
    // Latch interrupt
    // Write 01h into TAP_CFG 
    errorAccumulator += myIMU.writeRegister(LSM6DS3_ACC_GYRO_TAP_CFG1, 0x01);
	
	if( errorAccumulator )
  {
	  Serial.println("Problem configuring the device.");
  }
  else
  {
	  Serial.println("Device O.K.");
  }	
}

void loop()
{
	uint8_t readDataByte = 0;
	myIMU.readRegister(&readDataByte, LSM6DS3_ACC_GYRO_WAKE_UP_SRC);
	readDataByte &= 0x20; //Mask off the FF_IA bit for free fall detection
    if( readDataByte )
	{
		//debounce
	    delay(10);
		Serial.println("Interrupt caught.  Free fall detected.");
	}
	
}