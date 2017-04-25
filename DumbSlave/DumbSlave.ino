void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);


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

void loop() {
  if(digitalRead(2)){
    digitalWrite(7, LOW);  
    digitalWrite(8, HIGH);
  }else{
    digitalWrite(7, HIGH);    
    digitalWrite(8, LOW);
  }    

  if(digitalRead(3)){
    digitalWrite(9, LOW);   
    digitalWrite(10, HIGH);
  }else{
    digitalWrite(9, HIGH);   
    digitalWrite(10, LOW);
  }

    wdt_reset();
}
