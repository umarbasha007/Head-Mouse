/* Code to view on the Serial Monitor the values of the Gyroscope MPU6050
 * and the output for the mouse. This is equal to the standard code
 * but with instructions to check the values on the Serial monitor.
 * Change the delay to read the values at reduced speed.
 * 
 * In case head mouse we are in need of only gyroscope reading for knowing the orientation in axes
 * 
 * Umar Basha - Tech Monk 
*/

 /*
  Arduino Micro - MPU6050 Connections
   
  pin 2 of Arduino to pin SDA,
  pin 3 to SCL,
  pin 5V to PWR,
  pin GND to GND.
   
 */

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
//#include <Mouse.h> // no need to include in case of arduino micro pro.

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz; 
int vx, vy, vz;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) { while (1); }
}


void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

/* ax,ay,az -> accelerometer axes readings
 * gx,gy,gz -> gyroscope axes readings
*/ 
  vx = (gx+600)/150; // Change "+600" value so that vx value in the serial monitor is equal to '0' 
  vy = (gy-200)/150; // Change "-200" value so that vy value in the serial monitor is equal to '0'
  vz = -(gz-95)/150; // Change "-95" value so that vz value in the serial monitor is equal to '0'
  
  Serial.print("gx = ");
  Serial.print(gx);
  Serial.print(" | gy = ");
  Serial.print(gy);
  Serial.print(" | gz = ");
  Serial.print(gz);
  
  Serial.print("        | X = ");
  Serial.print(vx);
  Serial.print(" | Y = ");
  Serial.println(vy);
  Serial.print(" | Z = ");
  Serial.println(vz);
  
  //After all the values of vx,vy,vz are set to '0'. Uncomment the below Mouse.move() to check the movement of curser.
  //Mouse.move(vx, -vz); // In my case I used x,z - axes to calibrate the orientation and use those to move the mouse curser.
  
  delay(20);
}
