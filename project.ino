#include <M5Core2.h>
// Declaring global variables
float xdir = 0.0F;
float ydir = 0.0F;
float zdir = 0.0F;
bool warning = false;
bool isRed = false;
bool isWhite = false;
unsigned int time_of_warning=0;
 
// Project start screen
void game_start() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillScreen(PURPLE);
  M5.Lcd.setTextColor(WHITE, PURPLE);
  M5.Lcd.setCursor(10, 20);
  M5.Lcd.println("Welcome...");
  M5.Lcd.setCursor(10, 60);
  M5.Lcd.println("Press button A to start");
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(145, 225);
  M5.Lcd.println("NYUAD");
  while (1) {
    // wait for push button
    if(M5.BtnA.wasPressed()) {
      break;
    }
    M5.update();      
  }
}
 
//the program in the setUp() function will be run, and this part will only be run once.
void setup() {
  M5.begin();     //Init M5Core
  M5.IMU.Init();  //Init IMU sensor
  game_start();
  M5.Lcd.fillScreen(WHITE);  //Set the screen background color to black
  M5.Lcd.setTextColor(BLACK, WHITE);  //Sets the foreground color and background color of the displayed text
  M5.Lcd.setTextSize(3);  //Set the font size
}
 
void loop() {
 
  M5.IMU.getAhrsData(&xdir, &ydir, &zdir);  //reading the sensor values
 
  M5.Lcd.setCursor(20, 20);
  M5.Lcd.printf("XDir:%5.2f", xdir);
  m5.Lcd.setCursor(20, 60);
  M5.Lcd.printf("YDir:%5.2f", ydir);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(10, 225);
  M5.Lcd.println("Press button C for 2 sec to power off");
  M5.Lcd.setTextSize(3);
 
// if the horizontal head posture increase more than 20 in either positive or negative direction, it displays vibration and warning message
 
  if(xdir<-20 || xdir>20 || ydir<70 || ydir>110){
      warning=true;
  }else{
      warning=false;
  }
  if(warning==true){
    time_of_warning+=50;
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
  M5.update();
  if(M5.BtnC.pressedFor(2000)) {
      M5.shutdown();
    }
 
  delay(50);
}
