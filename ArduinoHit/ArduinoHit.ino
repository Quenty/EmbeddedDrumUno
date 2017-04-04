// CSCE 236
// Authors: Angelo Tenerelli, Dylan Gray, Ibraim Salinas, James Onnen, Lee Fitchett
// April 4th, 2017

#include "avr/wdt.h"
#include <avr/pgmspace.h>
#include "patterns.h"

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
  
  Serial.begin(9600);
}

void loop() { 
  if (Serial.available() > 0) {
    char inChar = Serial.read();
    int inNum = (int)(inChar) - 49;  // convert char to int (minus 1 for 0 array index)

    if (inNum >= 0 && inNum < 4){
        go(patterns[inNum], lengths[inNum]);
    }
  }
} 

void go(const int* pattern, const int len) {
  if (len <= 0)
  {
    Serial.write("Bad length\n");
  }
  
  for (int i=0; i<len; i+=3) {
    int stick = pgm_read_word_near(pattern + i);
    int dir = pgm_read_word_near(pattern + (i + 1)); 
    int pause = pgm_read_word_near(pattern + (i + 2)); 

    // char buffer[100];
    // sprintf(buffer, "stick %d direction %d pause %d \n", stick, dir, pause);
    // Serial.write(buffer);
    
    hit(stick, dir); 
    delay(pause); 
  } 
} 

void hit(int stick, int dir) { 
  //char buffer[100];
  //sprintf(buffer, "stick %d direction %d\n", stick, dir);
  //Serial.write(buffer);
  if (stick==1) {
    digitalWrite(IN1, dir);   
    digitalWrite(IN2, !dir);
  } else if (stick==2) {    
    digitalWrite(IN3, dir);
    digitalWrite(IN4, !dir);
  } else {
    Serial.write("BAD INPUT\n");
  }
}

