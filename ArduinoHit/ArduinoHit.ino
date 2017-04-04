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
  
  // open the serial port:
  Serial.begin(9600);
}

void loop() { 
  // check for incoming serial data:
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
   
    if (inChar >= '1' && inChar <= '4'){
        int inNum = inChar - '1';  //convert char to int (minus 1 for 0 array index)
        go(patterns[inNum], lengths[inNum]);         
    }
  }
}

void go(const int* pattern, const int len) {
  
  for (int i=0; i<len; i+=3) {
    int stick = pattern[i];
    int dir = pattern[i+1];
    hit(stick, dir);
    delay(pattern[i+2]);
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

