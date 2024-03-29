#include "stream.h"
#include <Wire.h>
#include <avr/wdt.h>

#define TIME_HEADER 'T'
#define PATTERN_HEADER 'P'
#define CLEAR_QUEUE_HEADER 'C'


#define IN1 6
#define IN2 7

#define IN3 8
#define IN4 9

enum Drums { Snare = 1, Bass = 2, Hihat = 3, Tom1 = 4, Tom2 = 5, FloorTom = 6, Crash = 7}; 

#define CURRENTDRUM 7

#define PRESCALER 0b101
#define TIMER1MAXVALUE 65535

Queue queue; 

uint16_t nextStick;
uint16_t nextDir;
unsigned long nextHitTime = 0;
bool isNextHitValid;
signed long masterTimeOffset = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  TCCR1A = 0; //set to normal counter mode
  TCCR1B = PRESCALER && 0b111; //set prescaler and disable output compare
  
  // open the serial port:
  Serial.begin(9600);
  Serial.write("Start\n");  

  TCNT1 = 0;  //reset timer after config done
  
   //Watchdog
  //Disable all interrupts
  cli();
  //kick watchdog
  wdt_reset();
  //enable change on the watchdog
  WDTCSR |= (1 << WDCE) | (1<<WDE);
  //config the watchdog with timeout of 
  WDTCSR = (0 <<WDIE) | (1<<WDE) | (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0);
  //enable all interrupts again
  sei();

  //run sync initilization code here.
  Wire.begin(CURRENTDRUM);
  Wire.onReceive(onSlaveReceive);
}

//void readSerial();

void loop() {  
  //Kick watchdog
  wdt_reset();

  if(isNextHitValid){
    if((signed long) getMasterTime() > ((signed long) nextHitTime)){
      //starting hit, disable interupts
//      cli();
      hit(nextStick, nextDir);
      isNextHitValid = false;
//      readSerial();
//      setNextHit();
//      sei();
    }
  }

  if (!isNextHitValid) {
    setNextHit();
  }
  
//  char buffer[100];
//  sprintf(buffer, "Master time is %ld\n", (unsigned long) getMasterTime());
//  Serial.write(buffer);
}

uint16_t readUInt16(int& success)
{
  uint16_t value = 0;

  if (Wire.available() < 2)
  {
    Serial.write("Bad length\n");
    success = 0;
    return 0;
  }

  uint8_t first = Wire.read();
  uint8_t second = Wire.read();

  value = ((uint16_t) first) + (((uint16_t) second) << 8);
  return value;
}

unsigned long readLong()
{
  unsigned long value = 0;
  unsigned int offset = 0;

  while (Wire.available() > 0)
  {
    uint8_t readValue = Wire.read();
//    char buffer[100];
//    sprintf(buffer, "Read %u\n", readValue);
//    Serial.write(buffer);
    
    value = value + (((unsigned long) readValue) << (offset*8));
    offset += 1;
  }

  if (offset != 4)
  {
    char buffer[100];
    sprintf(buffer, "Bad offset %u\n", offset);
    Serial.write(buffer);
  }

  return value;
}

void onSlaveReceive(int howMany) {
//  Serial.write("Received transmission\n");
  
  char transmissionType = 0;
  if (1 < Wire.available())
  {
    transmissionType = Wire.read();
  }

  if (transmissionType == TIME_HEADER)
  {
    unsigned long timeOne = readLong();
    masterTimeOffset = ((signed long) timeOne) - ((signed long) millis());

    char buffer[100];
    sprintf(buffer, "Master time is %lu %ld\n", timeOne, getMasterTime());
    Serial.write(buffer);
  }
  else if (transmissionType == CLEAR_QUEUE_HEADER)
  {
    Serial.write("Clearing queue\n");
    while (queue.length() > 0) 
    {
      unsigned long dummy;
      queue.pop(dummy);
    }
  }
  else if (transmissionType == PATTERN_HEADER)
  {
    int success = 1;
    uint16_t stick = readUInt16(success);
    uint16_t direction = readUInt16(success);
    uint16_t hitTime = readUInt16(success);

    if (success)
    {
      queue.push(stick);
      queue.push(direction);
      queue.push(hitTime);
      Serial.write("New hit!\n");
    }
    else
    {
      Serial.write("Bad hit command format");
    }
  }
  else
  {
    Serial.write("Bad transmission type\n");
  }
}

signed long getMasterTime() {
  return ((signed long) millis()) + masterTimeOffset;
}

//
//void readSerial() {
//  while (Serial.available() > 0) {  // && !queue.isFull()
//    char inChar = Serial.read();
//    //Serial.write(queue.length());
//    Serial.write("Read in ");
//    Serial.write(inChar);
//    Serial.write('\n');
//    uint16_t inNum = (uint16_t)inChar - 48;
//
//    queue.push(inNum);
//  }
//}

void setNextHit(){
  if(queue.length() > 0){    
    unsigned long data = 0;
    queue.pop(data);
    
    nextHitTime = ((data << 2) >> 2);
    nextStick = (int) ((data >> 31) & 0b1);
    nextDir = (int) ((data >> 32) & 0b1);
//    queue.pop(nextStick);
//    queue.pop(nextDir);
//    queue.pop(nextHitTime);

    isNextHitValid = true;
  }
}

void hit(int stick, int dir) {
  char buffer[100];
  sprintf(buffer, "stick %d direction %d\n", stick, dir);
  Serial.write(buffer);
  
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
