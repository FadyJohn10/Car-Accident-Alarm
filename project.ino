#include <M5Core2.h>
 
float xdir = 0.0F;
float ydir = 0.0F;
float zdir = 0.0F;
 
//the program in the setUp() function will be run, and this part will only be run once.
void setup() {
  M5.begin();     //Init M5Core
  M5.IMU.Init();  //Init IMU sensor
  M5.Lcd.fillScreen(BLACK);  //Set the screen background color to black
  M5.Lcd.setTextColor(GREEN,BLACK);  //Sets the foreground color and background color of the displayed text
  M5.Lcd.setTextSize(2);  //Set the font size
}
 
void loop() {
  M5.IMU.getAhrsData(&xdir, &ydir, &zdir);  //reading the sensor values
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.printf("xdir,  ydir");
  M5.Lcd.setCursor(0, 130);
  M5.Lcd.printf("%5.2f  %5.2f deg", xdir, ydir);
// if the horizontal head posture increase more than 20 in either positive or negative direction, it displays vibration and warning message
  if(xdir<-20 || xdir>20){
      M5.Lcd.setCursor(0, 170);
      M5.Lcd.printf("warning!");
      M5.Axp.SetLDOEnable(3, true);  //Open the vibration.
  }else{
      M5.Lcd.setCursor(0, 170);
      M5.Lcd.printf("good...!");
      M5.Axp.SetLDOEnable(3, false);  //stop the vibration.
  }
// if the vertical head posture increase more than 20 in either positive or negative direction, it displays vibration and warning message
  if(ydir<70 || ydir>110){
      M5.Lcd.setCursor(0, 170);
      M5.Lcd.printf("warning!");
      M5.Axp.SetLDOEnable(3, true);  //Open the vibration.
  }else{
      M5.Lcd.setCursor(0, 170);
      M5.Lcd.printf("good...!");
      M5.Axp.SetLDOEnable(3, false);  //stop the vibration.     
}
}
