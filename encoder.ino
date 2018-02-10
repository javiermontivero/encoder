#include<encoder.h>
#include<LiquidCrystal.h>
#include<hcsr04.h>
#include<CMMC_LED.h>
#include<Button.h>
#include<powerexp.h>

//TIME FOR THE MEASURES TO BE TAKEN
#define TIME 5

//DEFINE LCD PINS
#define RS 2
#define ENABLE 3
#define D0 4
#define D1 5
#define D2 6
#define D3 7

//DEFINE SONIC PINS
#define TRIGGER 8
#define ECHO 9

//DEFINE LED PINS
#define LED_PIN 9

//DEFINE BUTTON PINS
#define START_PIN 10
#define DOWN_PIN 11
#define UP_PIN 12

LiquidCrystal lcd(RS,ENABLE,D0,D1,D2,D3);
HCSR04 sonic(TRIGGER,ECHO);
CMMC_LED led(LED_PIN,LOW);
Button startButton(START_PIN);
Button weightDownButton(DOWN_PIN);
Button weightUpButton(UP_PIN);
PowerExp power;
Encoder encoder(lcd,sonic,startButton, weightDownButton,weightUpButton,led);

void setup() {
}

void loop() {
  Serial.println("waiting..");
  if(encoder.startPressed()){
    Serial.println("startPressed");
    double speed = encoder.calculateWeightSpeed(TIME);
    Serial.print("Weight speed = ");
    Serial.println(speed);
    int weight = encoder.getWeight();
    Serial.print("Weight = ");
    Serial.println(weight);
    double rmValue = power.calculate1RM(speed,weight);
    Serial.print("RM = ");
    Serial.println(rmValue);
    encoder.show1RMValue(rmValue);
  }
  if(encoder.upPressed()){
    Serial.println("upPressed");
    encoder.increaseWeight();
  }
  
  if(encoder.downPressed()){
    Serial.println("downPressed");
    encoder.reduceWeight();
  }
}
