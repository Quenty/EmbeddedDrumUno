#include "patterns.h"
#include <Wire.h>


#define TIME_HEADER 'T'
#define PATTERN_HEADER 'P'
#define CLEAR_QUEUE_HEADER 'C'

enum Drums { Snare, Bass };


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void writeUInt16ToWire(uint16_t value)
{
  Wire.write((uint8_t) value);
  Wire.write((uint8_t) (value >> 8));
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

 oid writePattern(int wiredId, unsigned long data)
{
  Wire.beginTransmission(wireId);
  Wire.write(PATTERN_HEADER);
  writeLongToWire(data);
  Wire.endTransmission();
}
//void writePattern(int wireId, uint16_t stick, uint16_t direction, uint16_t hitTime) 
//{
////  Serial.write("Starting pattern write\n");
//  
//  Wire.beginTransmission(wireId);
//  Wire.write(PATTERN_HEADER);
//  
//  writeUInt16ToWire(stick);
//  writeUInt16ToWire(direction);
//  writeUInt16ToWire(hitTime);
//  
//  Wire.endTransmission();
//
////  Serial.write("Wrote pattern\n");
//}

void startSyncronization(int wireId)
{
//  Serial.write("Syncronizing\n");
  
  Wire.beginTransmission(wireId);
  Wire.write(TIME_HEADER);
  
  unsigned long timeOne = millis();
  writeLongToWire(timeOne);
//  Serial.write("Done writing long\n");
  Wire.endTransmission();
//  Serial.write("Transmission done\n");

  char buffer[50];
  sprintf(buffer, "Master time %lu\n", timeOne);  
  Serial.write(buffer);
}

void loop() {
  // put your main code here, to run repeatedly:
  startSyncronization(8);
  startSyncronization(7);
//  Serial.write("Done\n");
  
//  writePattern(8, 1, LOW, millis() + 200);
  writePattern(8, 1, HIGH, millis() + 400);

//  writePattern(8, 2, LOW, millis() + 100);
//  writePattern(8, 2, HIGH, millis() + 300);

  unsigned long now = millis();
//  writePattern(7, 2, HIGH, now + 400);
//  writePattern(7, 1, HIGH, now + 600);
//  writePattern(7, 2, LOW, now + 800);
//  writePattern(7, 1, LOW, now + 1000);

  
  
  
  delay(1000);
}
