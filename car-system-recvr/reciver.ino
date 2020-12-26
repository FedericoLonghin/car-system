byte * readBytes(long length) {
  int time = millis();
  byte * result = new byte[length];
  for (int i = 0; i < length; i++) {
    //Serial.print("----------------------------Ascolto il byte: ");
    // Serial.println(i);
    for (int ibit = 0; ibit < 8; ibit++) {
      while (!digitalRead(SCL)) {
        if (time + 100 < millis()) {
          //return;
        }
      }// Waiting for SCL to became up
      bool read = digitalRead(SDA);
      digitalWrite(TR, 1);
      // Serial.println(read);
      bitWrite(result[i], ibit, read);

      while (digitalRead(SCL)) {} // Waiting for SCL to became down after reading
      digitalWrite(TR, 0);

    }
    //result[i] = byte(readBools(8));
    //Serial.println((char)result[i]);
  }
  return result;
}

bool* readBools(long length) {

  bool * result = new bool[length];
  for (int i = 0; i < length; i++) {
    // Serial.print("Ascolto il bit: ");
    // Serial.println(i);

    while (!digitalRead(SCL)) {} // Waiting for SCL to became up
    bool read = digitalRead(SDA);
    digitalWrite(TR, 1);
    // Serial.println(read);
    result[i] = read;

    while (digitalRead(SCL)) {} // Waiting for SCL to became down after reading
    digitalWrite(TR, 0);

  }
  return result;
}

String readString(long int length) {

  byte * r = readBytes(length);
  r[length] = '\0';

  return String((char*)r);
}
int readInt() {

  byte * r = readBytes(4);

  int foo;
  foo = (uint32_t) r[3] << 24;
  foo |=  (uint32_t) r[2] << 16;
  foo |= (uint32_t) r[1] << 8;
  foo |= (uint32_t) r[0];

  return foo;
}
short readShort() {

  byte * r = readBytes(2);

  short foo;
  foo = (short) r[1] << 8;
  foo |= (short) r[0] << 0;

  return foo;
}
void fetchData() {
  Serial.println("Fetching data /n");

  digitalWrite(TR, 1);
  while (!digitalRead(SCL)) {}
  digitalWrite(TR, 0);

  //int s = readShort();
  bool * info = readBools(16);
  byte * message_size_b = readBytes(1);
  int message_size = * message_size_b;

  if (info[0]) {
    Serial.println("Prendo speed");
    speed = readShort();
    Serial.print("Speed: ");
    Serial.println(speed);
  }
  if (info[1]) {
    Serial.println("Prendo rpm");
    rpm = readShort();
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
  if (info[2]) {
    Serial.println("Prendo fuel");
    fuel_level = readInt();
    Serial.print("Fuel level: ");
    Serial.println(fuel_level);
  }

  if (info[15]) {
    Serial.println("Reading message");
    message = readString(message_size);
    Serial.print("Message: ");
    Serial.println(message);
  }


}
