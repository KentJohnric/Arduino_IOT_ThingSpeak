void setup() {
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(3) == LOW){
    digitalWrite(13, HIGH);
    Serial.println("Interrupt");
    delay(10);
  }
  else{
    digitalWrite(13, LOW);
    Serial.println("Free");
    delay(10);
  }
}
