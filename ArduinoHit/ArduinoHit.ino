#include "stream.h"
#include "main.cpp"

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

void readSerial();

void loop() {
  readSerial();

  char buffer[100];
  for(int i = 0; i < 10 && queue.length() > 0; i++){
	  int bufferResult =0;
    queue.pop(bufferResult);

	  sprintf(buffer, "buffer says %d.\n", bufferResult);
	  Serial.write(buffer);
  }
}

void readSerial() {
  while (Serial.available() > 0 && !queue.isFull()) {
    char inChar = Serial.read();
    int inNum = (int)inChar - 48;

    queue.push(inNum);
  }
}

void hit(int stick, int dir) {
  //char buffer[100];
  //sprintf(buffer, "stick %d direction %d\n", stick, dir);
  //Serial.write(buffer);
  if (stick == 1) {
    //Serial.write("stick1 moving\n");

    digitalWrite(IN1, dir);
    digitalWrite(IN2, !dir);
  }
  else if (stick == 2) {
    //Serial.write("stick2 moving\n"); 

    digitalWrite(IN3, dir);
    digitalWrite(IN4, !dir);
  }
  else
  {
    Serial.write("BAD INPUT\n");
  }
}
