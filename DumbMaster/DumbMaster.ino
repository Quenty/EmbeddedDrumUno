void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);  
}

void loop() {
  digitalWrite(2, LOW);  
  delay(80);
  digitalWrite(2, HIGH);  
  delay(500);
  digitalWrite(3, LOW);  
  delay(80);
  digitalWrite(3, HIGH);  
  delay(1000);
}
