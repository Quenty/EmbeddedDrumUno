#include "patterns.h"
#include <Wire.h>


#define TIME_HEADER 'T'

enum Drums { Snare, Bass };


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void writeLongToWire(unsigned long value)
{
//  char buffer[100];
//  sprintf(buffer, "Writing %lu\n", value);
//  Serial.write(buffer);

  for (unsigned int i=0; i < 4; i++)
  {
    uint8_t int_value = (uint8_t) (value >> (i*8)); //(byte) (value >> (i*4));
    Wire.write(int_value);
//    char buffer[100];
//    sprintf(buffer, "Wrote %u\n", int_value);
//    Serial.write(buffer);
  }
}

void startSyncronization()
{
  Serial.write("Syncronizing\n");
  
  Wire.beginTransmission(8);
  Wire.write(TIME_HEADER);
  unsigned long timeOne = millis();

  char buffer[100];
  sprintf(buffer, "Master time %lu\n", timeOne);
  Serial.write(buffer);
  
  writeLongToWire(timeOne);
  Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:
  startSyncronization();
  delay(1000);
}
