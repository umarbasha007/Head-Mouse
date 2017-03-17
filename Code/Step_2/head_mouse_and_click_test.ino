/* DESIGN - THE HEAD MOUSE
 * Code to control the mouse pointer with the movement of the head and for click action.
 * 
 * 
 * Umar Basha - Tech Monk
*/

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
//#include <Mouse.h> //is included by default in arduino micro

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy,vz, vx_prec, vz_prec;
int count=0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
    }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
 // check if vx,vy,vz values are '0' using "Head_mouse_gyroscope_settings.ino".
  vx = (gx+600)/150; 
  vy = (gy-200)/150; 
  vz = -(gz-80)/150;
  
  Mouse.move(vx, -vz); //In my case I used x,z - axes to calibrate the orientation and use those to move the mouse curser.
  
  
  if ( (vx_prec-5)<=vx && vx<=vx_prec+5 && (vz_prec-5)<=vz && vz<=vz_prec+5) { // checking the pointer doesn't move too much from its actual position: (in this case a 10 pixel square)
    count++;                                                                  
    if(count == 100){ // the click will happen after 1.5 seconds the pointer has stopped in the 10px square: 15ms of delay 100 times it's 1500 ms = 1.5 sec
      if (!Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.press(MOUSE_LEFT);
        count = 0;
      }
    }
    else {
      if (Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.release(MOUSE_LEFT);
      }
    }
  }
  else {
    vx_prec = vx; // updating values to check the position of the pointer and allow the click
    vz_prec = vz;
    count = 0;
    }
  
  delay(15);// 15x100 = 1500 ms = 1.5 sec. Change delay value to change delay time for mouse click action.
}
