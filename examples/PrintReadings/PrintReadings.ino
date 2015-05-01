#include <Wire.h>
#include "Sparkfun_LSM6DS3.h"
#include "stdint.h"
#include "SPI.h"

//Don't pass things to the constructor
Sparkfun_LSM6DS3 mySensor;


void setup( void ) {
  Serial.begin(57600);  // start serial for output

  //Over-ride default settings if desired
  mySensor.settings.gyroEnabled = 1;  //Can be 0 or 1
  mySensor.settings.gyroRange = 2000;   //Max deg/s.  Can be: 125, 245, 500, 1000, 2000
  mySensor.settings.gyroSampleRate = 416;   //Hz.  Can be: 13, 26, 52, 104, 208, 416, 833, 1666
  mySensor.settings.gyroBandWidth = 400;  //Hz.  Can be: 50, 100, 200, 400;
  mySensor.settings.gyroFifoEnabled = 1;  //Set to include gyro in FIFO
  mySensor.settings.gyroFifoDecimation = 1;  //set 1 for on /1

  mySensor.settings.accelEnabled = 1;
  mySensor.settings.accelRange = 16;      //Max G force readable.  Can be: 2, 4, 8, 16
  mySensor.settings.accelSampleRate = 416;  //Hz.  Can be: 13, 26, 52, 104, 208, 416, 833, 1666, 3332, 6664, 13330
  mySensor.settings.accelBandWidth = 100;  //Hz.  Can be: 50, 100, 200, 400;
  mySensor.settings.accelFifoEnabled = 1;  //Set to include accelerometer in the FIFO
  mySensor.settings.accelFifoDecimation = 1;  //set 1 for on /1
  mySensor.settings.tempEnabled = 1;
  
  //Select interface mode
  mySensor.settings.commInterface = I2C_MODE; //Can be I2C_MODE, SPI_MODE
  mySensor.settings.commMode = 1;  //Can be modes 1, 2 or 3
  //Select address for I2C.  Does nothing for SPI
  mySensor.settings.I2CAddress = 0x6B; //Ignored for SPI_MODE
  //Select CS pin for SPI.  Does nothing for I2C
  mySensor.settings.chipSelectPin = 10;
  
  //Non-basic mode settings
  mySensor.settings.commMode = 1;

  //FIFO control data
  mySensor.settings.fifoThreshold = 3000;  //Can be 0 to 4096 (16 bit bytes)
  
  uint8_t c = mySensor.begin();  //Can be called again to load new settings
  mySensor.fifoBegin();
  
  Serial.print("begin() ran.  Returns WHO_AM_I of: 0x");
  Serial.println(c, HEX);

}

void loop() {
  float temp;  //This is to hold read data
  int16_t tempRaw;
  
//  Serial.print("\nIndividual reads");
//  Serial.print("\n\n");  
//  Serial.println("Accelerometer data");
//  temp = mySensor.readAccel(X_DIR);
//  Serial.println(temp, 4);
//  temp = mySensor.readAccel(Y_DIR);
//  Serial.println(temp, 4);
//  temp = mySensor.readAccel(Z_DIR);
//  Serial.println(temp, 4);

  tempRaw = mySensor.fifoRead();
  Serial.println(tempRaw);

//  Serial.println("\nAccelerometer data (Raw)");
//  tempRaw = mySensor.readAccelRaw(X_DIR);  //Raw
//  Serial.println(tempRaw);
//  tempRaw = mySensor.readAccelRaw(Y_DIR);  //Raw
//  Serial.println(tempRaw);
//  tempRaw = mySensor.readAccelRaw(Z_DIR);  //Raw
//  Serial.println(tempRaw);
//
//  Serial.println("\nGyroscope data");
//  temp = mySensor.readGyro(X_DIR);
//  Serial.println(temp, 4);
//  temp = mySensor.readGyro(Y_DIR);
//  Serial.println(temp, 4);
//  temp = mySensor.readGyro(Z_DIR);
//  Serial.println(temp, 4);
// 
//  Serial.println("\nGyroscope data (Raw)");
//  tempRaw = mySensor.readGyroRaw(X_DIR);  //Raw
//  Serial.println(tempRaw);
//  tempRaw = mySensor.readGyroRaw(Y_DIR);  //Raw
//  Serial.println(tempRaw);
//  tempRaw = mySensor.readGyroRaw(Z_DIR);  //Raw
//  Serial.println(tempRaw);  
//  
//  Serial.println("\nTemperature data");
//  temp = mySensor.readTemp();  //Raw
//  Serial.println(temp);
//
//  Serial.print("\nGroup read");
//  Serial.print("\nA_X,A_Y,A_Z,G_X,G_Y,G_Z,A_X_R,A_Y_R,A_Z_R,G_X_R,G_Y_R,G_Z_R,T\n");
//  //To get all data, read into "the internal structure"
//  mySensor.readAll();
//  mySensor.readAllRaw();
//  
//  Serial.print(mySensor.xAccel);
//  Serial.print(",");
//  Serial.print(mySensor.yAccel);
//  Serial.print(",");
//  Serial.print(mySensor.zAccel);
//  Serial.print(",");
//  Serial.print(mySensor.xGyro);
//  Serial.print(",");
//  Serial.print(mySensor.yGyro);
//  Serial.print(",");
//  Serial.print(mySensor.zGyro);
//  Serial.print(",");
//  Serial.print(mySensor.xAccelRaw);
//  Serial.print(",");
//  Serial.print(mySensor.yAccelRaw);
//  Serial.print(",");
//  Serial.print(mySensor.zAccelRaw);
//  Serial.print(",");
//  Serial.print(mySensor.xGyroRaw);
//  Serial.print(",");
//  Serial.print(mySensor.yGyroRaw);
//  Serial.print(",");
//  Serial.print(mySensor.zGyroRaw);
//  Serial.print(",");
//  Serial.print(mySensor.celsiusTemp);
//  Serial.print("\n");

  //To stop it all
  //mySensor.stop();
    delay(100);

}
