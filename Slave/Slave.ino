#include "stream.h"

#define IN1 6
#define IN2 7

#define IN3 8
#define IN4 9

enum Drums { Snare, Bass, Hihat, Tom1, Tom2, FloorTom };

#define PRESCALER 0b101
#define TIMER1MAXVALUE 65535

Queue queue; 

uint16_t nextStick;
uint16_t nextDir;
uint16_t nextHitTime;
bool isNextHitValid;

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

  //run sync initilization code here.
  
  
  
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
  
  
  
}

void readSerial();

void loop() {  
  //Kick watchdog
  wdt_reset();
  
  
  
  if(isNextHitValid){
    if(TCNT1 > nextHitTime && TCNT1 - nextHitTime < TIMER1MAXVALUE / 2){
    hit(nextStick, nextDir);
    isNextHitValid = false;
    readSerial();
    setNextHit();
    }
  }else{
    setNextHit();
  }
  
}

void readSerial() {
  while (Serial.available() > 0) {  // && !queue.isFull()
    char inChar = Serial.read();
    //Serial.write(queue.length());
    Serial.write("Read in ");
    Serial.write(inChar);
    Serial.write('\n');
    uint16_t inNum = (uint16_t)inChar - 48;

    queue.push(inNum);
  }
}

void setNextHit(){
  if(queue.length() >=3){    
    queue.pop(nextStick);
    queue.pop(nextDir);
    queue.pop(nextHitTime);

    isNextHitValid = true;
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
