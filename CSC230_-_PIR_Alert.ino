#include <M5StickC.h>

const int motion_state = 36;  //variable for my conditionals. Set to the PIR Hat Pin
const int button = 37;  //variable for the button so I dont have to mess with the M5 function

void setup() {
  
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);

  Serial.begin(115200);  //this was used for troubleshooting during the programming process

  pinMode(motion_state,INPUT_PULLUP);
}

void loop() {

  if (digitalRead(motion_state) == 1){  //if Motion is triggered run this code

  M5.Lcd.fillScreen(RED);
  M5.Lcd.setCursor(40, 20, 4);
  M5.Lcd.println("ALERT!");
    
  }

  if (digitalRead(button) == 0){ //to reset the PIR to activate again

  Serial.println("button activated");
  M5.Lcd.fillScreen(BLACK);

  delay(2000); // gives 2 seconds before the PIR can activate again
    
  }

 

  delay(100);
}
