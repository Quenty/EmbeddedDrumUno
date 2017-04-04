#include "stream.h"

#define IN1 6
#define IN2 7

#define IN3 8
#define IN4 9
 
Queue queue;

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
  
} 

bool readSerial(){
  if (Serial.available() > 0) {
    char inChar = Serial.read();
    //add to buffer
  }
  return false;
}

void hit(int stick, int dir) { 
  //char buffer[100];
  //sprintf(buffer, "stick %d direction %d\n", stick, dir);
  //Serial.write(buffer);
  if (stick==1) {
    //Serial.write("stick1 moving\n");
    
    digitalWrite(IN1, dir);   
    digitalWrite(IN2, !dir);
  } else if (stick==2) {
    //Serial.write("stick2 moving\n"); 
    
    digitalWrite(IN3, dir);
    digitalWrite(IN4, !dir);
  }
  else
  {
    Serial.write("BAD INPUT\n");
  }
}

