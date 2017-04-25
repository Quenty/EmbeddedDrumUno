void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);


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
}
