
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <M5StickC.h>

#include "ThingSpeak.h"
#include "M5_PIR_secrets.h"

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key index number (needed only for WEP)

WiFiClient  client;

const int motion_state = 36;  //variable for my conditionals. Set to the PIR Hat Pin
const int button = 37;  //variable for the button so I dont have to mess with the M5 function

void setup() {
  
  Serial.begin(115200);
  delay(50);

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
  
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);

  pinMode(motion_state,INPUT_PULLUP);
  pinMode(button,INPUT_PULLUP);

}

void loop() {

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }   
    
    Serial.println("\nConnected."); // Serial Monitor Output when the device is 'Connected'   
  } 
     
  //This is the beginning of my PIR Code
  if (digitalRead(motion_state) == 1){  //if Motion is triggered run this code
  
  M5.Lcd.fillScreen(RED);
  M5.Lcd.setCursor(40, 20);
  M5.Lcd.println("ALERT!");

  Serial.println("Motion Detected");

  int httpCode_alert = ThingSpeak.writeField(myChannelNumber, 1, 1, myWriteAPIKey);

  delay(5000);
  
  if (httpCode_alert == 200) {
    Serial.println("Channel write successful.");
  } 
  }

  
  if (digitalRead(motion_state) == 0){ //to reset the PIR to activate again

  Serial.println("Nothing Detected");
  M5.Lcd.fillScreen(BLACK);

  int httpCode_alert = ThingSpeak.writeField(myChannelNumber, 1, 0, myWriteAPIKey);

  delay(1000);
  
  if (httpCode_alert == 200) {
    Serial.println("Channel write successful.");
  } 
  
  }
}
