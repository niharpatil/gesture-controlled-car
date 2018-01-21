#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
Adafruit_BNO055 bno = Adafruit_BNO055(55);
 
void setup(void) 
{
  Serial.begin(9600);

  //9-axis sensor
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);

  //Radio setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
}
 
void loop(void) 
{

imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
const double x_data[] = {euler.x()};
const double y_data[] = {euler.y()};
const double z_data[] = {euler.z()};

//radio.write(&x_data, sizeof(x_data));
radio.write(&y_data, sizeof(y_data));
//radio.write(&z_data, sizeof(z_data));
/* Display the floating point data */
//Serial.print("X: ");
delay(100);
//Serial.print(" Y: ");
//Serial.print(" Z: ");
//Serial.print(euler.z());
  
}
