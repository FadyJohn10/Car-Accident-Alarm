#include <M5Core2.h>
#include <EMailSender.h>
#include <WiFi.h>
// Declaring global variables
float xdir = 0.0F;
float ydir = 0.0F;
float zdir = 0.0F;
bool warning = false;
bool isRed = false;
bool isWhite = false;
String messagesent;
unsigned int time_of_warning = 0;
unsigned int total_time_warning = 0;
unsigned int total_time_right = 0;
unsigned int total_time_working = 0;
const char* ssid = "Realme";
const char* password = "123456789";
const char* email_username = "m5project0testing@gmail.com";
const char* email_password = "ofxaionjedbzsbfg";
EMailSender emailSend(email_username, email_password);

// Project start screen
void program_start() {
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
  program_start();
  M5.Lcd.fillScreen(WHITE);  //Set the screen background color to black
  M5.Lcd.setTextColor(BLACK, WHITE);  //Sets the foreground color and background color of the displayed text
  M5.Lcd.setTextSize(3);  //Set the font size
  Serial.begin(115200);
  Serial.print("Connecting to WiFi: ");
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("connected");
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
      total_time_right += 50;
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
      M5.Spk.DingDong(); //play the sound
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
  if(M5.BtnC.pressedFor(1000)) {
      // Send the email
      EMailSender::EMailMessage message;
      message.subject = "Project Report";
      messagesent = "You were in the right posture for " + String(total_time_right/total_time_working) + "% of the time";
      message.message = messagesent;

      EMailSender::Response resp = emailSend.send("fofo15279@gmail.com",message);
      M5.shutdown();
  }
  total_time_working += 50;
  delay(50);
}
