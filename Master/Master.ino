// #include "patterns.h"
#include <Wire.h>


#define TIME_HEADER 'T'
#define PATTERN_HEADER 'P'
#define CLEAR_QUEUE_HEADER 'C'

enum Drums { Snare, Bass };


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.write("Master initialized\n");

  for (int i=8; i<17; i++)
  {
  clearBuffer(i);
//  clearBuffer(9);
  }
}

void writeUInt16ToWire(uint16_t value)
{
  Wire.write((uint8_t) value);
  Wire.write((uint8_t) (value >> 8));
}

void writeLongToWire(unsigned long value)
{
//  char buffer[50];
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

void writePattern(int wireId, unsigned long data)
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

void clearBuffer(int wireId)
{
  Serial.write("Clearing buffering\n");
  Wire.beginTransmission(wireId);
  Wire.write(CLEAR_QUEUE_HEADER);
  Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write("Sync start\n");
  for (int i=8; i<17; i++) {
  startSyncronization(i);
//  startSyncronization(9);
  }
  Serial.write("Pattern write start\n");
//  Serial.write("Done\n");
  
//  writePattern(8, 1, LOW, millis() + 200);
//  writePattern(8, 1, HIGH, millis() + 400);


//  writePattern(8, 2, LOW, millis() + 100);
//  writePattern(8, 2, HIGH, millis() + 300);

  unsigned long now = millis();

  // STICK, DIRECTION, TIME
  // LOW is DOWN.
  writePattern(8, (((unsigned long) 0b00) << 30) | (now + 400));
  writePattern(8, (((unsigned long) 0b01) << 30) | (now + 500));
  writePattern(8, (((unsigned long) 0b10) << 30) | (now + 1400));
  writePattern(8, (((unsigned long) 0b11) << 30) | (now + 1550));

  /*
  writePattern(9, (((unsigned long) 0b11) << 30) | (now + 500));
  writePattern(9, (((unsigned long) 0b10) << 30) | (now + 700));
  writePattern(9, (((unsigned long) 0b01) << 30) | (now + 900));
  writePattern(9, (((unsigned long) 0b00) << 30) | (now + 1100));*/
//  writePattern(7, 2, HIGH, now + 400);
//  writePattern(7, 1, HIGH, now + 600);
//  writePattern(7, 2, LOW, now + 800);
//  writePattern(7, 1, LOW, now + 1000);

  
  
  
  delay(1000);
}
