void riceviByte() {

  for (int i = 0; i < 16; i++) {

    //Serial.print("Ascolto il byte: ");
    //Serial.println(i);
    for (int ibit = 0; ibit < 8; ibit++) {
      while (!digitalRead(SCL)) {} // Waiting for SCL to became up
      bool read = digitalRead(SDA);
      digitalWrite(TR, 1);
      //Serial.println(read);
      bitWrite(result[i], ibit, read);
      while (digitalRead(SCL)) {} // Waiting for SCL to became down after reading
      digitalWrite(TR, 0);
    }
//Serial.print("Result: ");
    //Serial.println((char)result[i]);
  }
  //Serial.println("Sono fuori");

}
