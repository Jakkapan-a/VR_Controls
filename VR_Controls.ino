#include <TcBUTTON.h>
#include <TcPINOUT.h>
#define TRICKER_PIN 8
void OnTrickerChange(bool);
TcBUTTON tricker(TRICKER_PIN,false);

#define VR_PIN A0
int vrValue = 0;

#define RELAY_PIN 5
TcPINOUT relay(RELAY_PIN,true);

const int MaxSeconds = 60;
int secondCountDown = 0;

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  tricker.setOnEventChange(OnTrickerChange);
  pinMode(VR_PIN,INPUT);
  relay.off();
}

void loop() {
  tricker.update();
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 1000){
    previousMillis = currentMillis;
    if(secondCountDown > 0){
      secondCountDown--;
      if(secondCountDown == 0){
        Serial.println(secondCountDown);
        Serial.println("Time is up");
        relay.off();
      }
    }
  }
}

void OnTrickerChange(bool state){
  if(!state){
    Serial.println(state);
    Serial.println("Tricker is pressed");
    // Read VR value
    vrValue = analogRead(VR_PIN);
    // Print VR value
    Serial.print("VR value: ");
    Serial.println(vrValue);
    // Calculate seconds from VR value
    secondCountDown = map(vrValue,0,1023,0,MaxSeconds);
    // Print seconds
    Serial.print("Seconds: ");
    Serial.print(secondCountDown); 
    Serial.println(" s");
    relay.on();
    if(secondCountDown > 0){
      Serial.println("Start countdown");
    }else {
      secondCountDown =1;
    }
  }
}
