

void initSequence() {
  Serial.print("inizio la sequenza...");
  digitalWrite(SCL, 1);
  while (digitalRead(TR)) {}
  digitalWrite(SCL, 0);
  Serial.println("Fatto");
}


void mandaByte(byte data) {
  for (int i = 0; i < 8; i++) {
    Serial.print("invio: ");
    Serial.println(bitRead(data, i));
    digitalWrite(SDA, bitRead(data, 8-i));
    delay(100);
    digitalWrite(SCL, 1);
    delay(speed);
    digitalWrite(SDA, 0);
    delay(100);
    digitalWrite(SCL, 0);
    delay(speed);
  }
}

void endSequence() {
  Serial.print("finisco la sequenza...");

  digitalWrite(SCL, 0);
  digitalWrite(SDA, 1);
  delay(speed);
  Serial.println("Fatto");

}
