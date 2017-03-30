#include "avr/wdt.h"

#define IN1 6
#define IN2 7

#define IN3 8
#define IN4 9

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // open the serial port:
  Serial.begin(9600);
}

void go(int* pattern, int len) {
  
  for (int i=0; i<len; i+=3) {
    int stick = pattern[i];
    int dir = pattern[i+1];
    hit(stick, dir);
    delay(pattern[i+2]);
  }
}

void loop() {

  int stick1attack[] = {1, 0, 100, 1, 1, 500};
  int stick2attack[] = {2, 0, 100, 2, 1, 0};
  int len = 6;
  
  // check for incoming serial data:
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
  
    if (inChar == '\n'){
        go(stick1attack, len); 
        go(stick2attack, len);
    }
  }
}

void hit(int stick, int dir) {

  if (stick==1) {
    Serial.write("stick1 moving\n");
    
    digitalWrite(IN1, dir);
    digitalWrite(IN2, !dir);
  }

  if (stick==2) {
    Serial.write("stick2 moving\n");
    
    digitalWrite(IN3, dir);
    digitalWrite(IN4, !dir);
  }
}

