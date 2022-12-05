#include <M5Core2.h>
 
float xdir = 0.0F;
float ydir = 0.0F;
float zdir = 0.0F;
bool warning = false;
bool isRed = false;
bool isWhite = false;
unsigned int time_of_warning=0;
 
//the program in the setUp() function will be run, and this part will only be run once.
void setup() {
  M5.begin();     //Init M5Core
  M5.IMU.Init();  //Init IMU sensor
  M5.Lcd.fillScreen(WHITE);  //Set the screen background color to black
  M5.Lcd.setTextColor(BLACK, WHITE);  //Sets the foreground color and background color of the displayed text
  M5.Lcd.setTextSize(3);  //Set the font size
  // M5.Lcd.print("testttt");
  // M5.update();
  // if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
  // } else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
  //   M5.Axp.PowerOff();
  // }
}
 
void loop() {
  M5.IMU.getAhrsData(&xdir, &ydir, &zdir);  //reading the sensor values
 
  M5.Lcd.setCursor(20, 20);
  M5.Lcd.printf("XDir:%5.2f", xdir);
  m5.Lcd.setCursor(20, 60);
  M5.Lcd.printf("YDir:%5.2f", ydir);
 
// if the horizontal head posture increase more than 20 in either positive or negative direction, it displays vibration and warning message
 
  if(xdir<-20 || xdir>20 || ydir<70 || ydir>110){
      warning=true;
  }else{
      warning=false;
  }
  if(warning==true){
    time_of_warning+=100;
  }else{
      time_of_warning=0;
  }
  if(time_of_warning>=3000){
      if(isRed == false){
        M5.Lcd.setTextColor(BLACK, RED);
        M5.Lcd.fillScreen(RED);
        isRed = true;
        isWhite = false;
      }
      M5.Lcd.setCursor(80, 140);
      M5.Lcd.printf("Warning!");
      M5.Axp.SetLDOEnable(3, true);  //Open the vibration.
  }else{
      if(isWhite == false){
        M5.Lcd.setTextColor(BLACK, WHITE);
        M5.Lcd.fillScreen(WHITE);
        isWhite = true;
        isRed = false;
      }
      M5.Lcd.setCursor(80, 140);
      M5.Lcd.printf("Good...!");
      M5.Axp.SetLDOEnable(3, false);  //stop the vibration.
  }
 
  delay(100);
}
