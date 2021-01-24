byte * readBytes(int length) {
  byte * result = new byte[length];
  for (int i = 0; i < length; i++) {
    result[i] = readByte();
  }
  return result;
}

byte readByte() {
  byte result;
  for (int ibit = 0; ibit < 8; ibit++) {
    bool read = readBit();
    bitWrite(result, ibit, read);
  }
  return result;
}

bool readBit() {
  int t0 = millis();
  while (!digitalRead(SCL)) {
    ESP.wdtFeed();
    // Waiting for SCL to became up
    if (millis() - timeout_delay > t0) {
      Serial.println("Timeout");
    }
  }
  bool read = digitalRead(SDA);
  digitalWrite(TR, 1);
  // Serial.println(read);
  t0 = millis();
  while (digitalRead(SCL)) {
    // Waiting for SCL to became down after reading
    if (millis() - timeout_delay > t0) {
      Serial.println("Timeout");
    }
    ESP.wdtFeed();
  }
  digitalWrite(TR, 0);
  return read;
}

bool* readBools(long length) {
  bool * result = new bool[length];
  for (int i = 0; i < length; i++) {
    result[i] = readBit();
  }
  return result;
}

String readString(long int length) {
  byte * r = readBytes(length);
  r[length] = '\0';
  return String((char*)r);
}

int readInt() {
  int value;

  //byte * r = readBytes(4);
  //foo = (uint32_t) r[3] << 24;
  //foo |=  (uint32_t) r[2] << 16;
  //foo |= (uint32_t) r[1] << 8;
  //foo |= (uint32_t) r[0];

  value = (uint32_t) readByte();
  value |=  (uint32_t) readByte() << 8;
  value |= (uint32_t) readByte() << 16;
  value |= (uint32_t) readByte() << 24;
  return value;
}
short readShort() {
  short value;

  //byte * r = readBytes(2);
  //foo = (short) r[1] << 8;
  //foo |= (short) r[0] << 0;

  value = (uint32_t) readByte();
  value |= (uint32_t) readByte() << 8;

  return value;
}
bool fetchData() {
  Serial.println("Fetching data \n");
  digitalWrite(TR, 1);
  long t0 = millis();
  while (!digitalRead(SCL))
  {
    Serial.print(".");
    if (millis() - timeout_delay > t0) {
      return false;
    }
    ESP.wdtFeed();
  }
  digitalWrite(TR, 0);

  bool * info = readBools(16);
  int message_size = readShort();

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

  return true;
}
