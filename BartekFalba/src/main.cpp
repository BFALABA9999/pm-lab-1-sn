#include <Arduino.h>

#define CAR_RED 12
#define CAR_YELLOW 11
#define CAR_GREEN 10

#define PED_RED 9
#define PED_GREEN 8

#define PED_BUTTON 2

#define CHANGE_TIME 10000
#define STATE1_TIME 10000
#define STATE2_TIME 1000
#define STATE3_TIME 7000
#define STATE4_TIME 1000

enum LightState_t {GREEN, YELLOW, YELLOW_RED, RED};
LightState_t lightState = GREEN;
unsigned long changeTime = 0;

void setup() {
  pinMode(CAR_RED, OUTPUT);
  pinMode(CAR_YELLOW, OUTPUT);
  pinMode(CAR_GREEN, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);
  pinMode(PED_BUTTON, INPUT);
  digitalWrite(CAR_RED, LOW);
  digitalWrite(CAR_YELLOW, LOW);
  digitalWrite(CAR_GREEN, HIGH);
  digitalWrite(PED_RED, HIGH);
  digitalWrite(PED_GREEN, LOW);

  changeTime = millis();
}

void loop() {
  uint8_t state = digitalRead(PED_BUTTON);
  switch (lightState){

  case GREEN:
    digitalWrite(CAR_GREEN, HIGH);
    digitalWrite(CAR_YELLOW, LOW);
    digitalWrite(CAR_RED,LOW);
    digitalWrite(PED_RED, HIGH);
    digitalWrite(PED_GREEN,  LOW);
    if(((millis() - changeTime) > STATE1_TIME) || (state == HIGH)){
      lightState = YELLOW;
      changeTime = millis();
    }
    break;

  case YELLOW:
    digitalWrite(CAR_GREEN, LOW);
    digitalWrite(CAR_YELLOW, HIGH);
    digitalWrite(CAR_RED,LOW);
    digitalWrite(PED_RED, HIGH);
    digitalWrite(PED_GREEN, LOW);
    if((millis() - changeTime) > STATE2_TIME){
      lightState = RED;
      changeTime = millis();
    }
    break;

  case RED:
    digitalWrite(CAR_GREEN, LOW);
    digitalWrite(CAR_YELLOW, LOW);
    digitalWrite(CAR_RED,HIGH);
    digitalWrite(PED_RED, LOW);
    digitalWrite(PED_GREEN, HIGH);
    if((millis() - changeTime) > STATE3_TIME){
      for(uint8_t i=0;i<3;i++){
        digitalWrite(PED_GREEN, LOW);
        delay(500);
        digitalWrite(PED_GREEN, HIGH);
        delay(500);
      }
      lightState = YELLOW_RED;
      changeTime = millis();
    }
    break;

  case YELLOW_RED:
    digitalWrite(CAR_GREEN, LOW);
    digitalWrite(CAR_YELLOW, HIGH);
    digitalWrite(CAR_RED, HIGH);
    digitalWrite(PED_RED, HIGH);
    digitalWrite(PED_GREEN, LOW);
    if((millis() - changeTime) > STATE4_TIME){
      lightState = GREEN;
      changeTime = millis();
    }
    break;
  }
}