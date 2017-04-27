#include "patterns.h"
#include <avr/pgmspace.h>

#define IN1 7
#define IN2 8

#define IN3 9
#define IN4 10

#define SNAREA 2
#define SNAREB 3
#define CYMBOL 4

#define TOMA 6
#define TOMB 7

unsigned long getNextFromPattern(int index, int pattern);
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
  Serial.write("Initialized\n");
}

int x = 0;


void loop() {
  Serial.write("Looping!");
  
  uint32_t data = getNextFromPattern(1, x);
  unsigned int data_time = ((unsigned int) (data << 2 )) >> 2;

  int nextStick = (int) ((data >> 31) & 0b1);
  int nextDir = (int) ((data >> 30) & 0b1);

  char buffer[100];
  sprintf(buffer, "Yolo %lu\n", data);
  Serial.write(buffer);
  
  delay(millis() - data_time);

  if (nextStick == 0) {
    digitalWrite(IN1, nextDir);
    digitalWrite(IN2, !nextDir);
  }
  else if (nextStick == 1) {
    digitalWrite(IN3, nextDir);
    digitalWrite(IN4, !nextDir);
  }

  x++;
}



unsigned long getNextFromPattern(int pattern, int index){
  const long unsigned int* patternAddress = patterns[pattern]; //pgm_read_byte_near((unsigned long)patterns + pattern);
  long unsigned int test = patternAddress[index];

  return test;
}


