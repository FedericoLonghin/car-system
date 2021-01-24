bool readBytes(int length, byte * result) {
  result = new byte[length];
  for (int i = 0; i < length; i++) {
    if (!readByte(result[i])) return false;
  }
  return true;
}

bool readByte(byte &result) {
  for (int ibit = 0; ibit < 8; ibit++) {
    bool read;
    if (!readBit(read)) return false;
    bitWrite(result, ibit, read);
  }
  return true;
}

bool readBit(bool &value) {
  int t0 = millis();
  while (!digitalRead(SCL)) {
    ESP.wdtFeed();
    // Waiting for SCL to became up
    if (millis() - timeout_delay > t0) {
      Serial.println("Timeout (Mi aspetto SCL a 1)");
      return false;
    }
  }
  value = digitalRead(SDA);
  digitalWrite(TR, 1);
  t0 = millis();
  while (digitalRead(SCL)) {
    // Waiting for SCL to became down after reading
    if (millis() - timeout_delay > t0) {
      Serial.println("Timeout (Mi aspetto SCL a 0)");
      return false;
    }
    ESP.wdtFeed();
  }
  digitalWrite(TR, 0);
  return true;
}

bool readBools(long length, bool * result ) {
  result = new bool[length];
  for (int i = 0; i < length; i++) {
    if (! readBit(result[i])) return false;
  }
  return true;
}

bool readString(long int length, char * result) {
  byte * r;
  if (! readBytes(length, r)) return false;
  r[length] = '\0';
  result = (char*)r;
  return true;
}

bool readInt(int & value) {
  value = 0;
  byte b;
  if (!readByte(b))return false;
  value = (int) (b);
  if (!readByte(b))return false;
  value |=  (int) (b) << 8;
  if (!readByte(b))return false;
  value |= (int) (b) << 16;
  if (!readByte(b))return false;
  value |= (int) (b) << 24;
  return true;
}
bool readShort(short & value) {
  value = 0;
  byte b;
  if (!readByte(b))return false;
  value = (int) (b);
  if (!readByte(b))return false;
  value |=  (int) (b) << 8;
  return true;
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

  bool * info;
  if (!readBools(16, info))return false;
  short message_size;
  if (!readShort(message_size))return false;

  if (info[0]) {
    Serial.println("Prendo speed");
    if (!readShort(speed))return false;
    Serial.print("Speed: ");
    Serial.println(speed);
  }
  if (info[1]) {
    Serial.println("Prendo rpm");
    if (!readShort(rpm))return false;
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
  if (info[2]) {
    Serial.println("Prendo fuel");
    if (!readInt(fuel_level))return false;
    Serial.print("Fuel level: ");
    Serial.println(fuel_level);
  }
  if (info[15]) {
    Serial.println("Reading message");
    if (!readString(message_size, message))return false;
    Serial.print("Message: ");
    Serial.println(message);
  }

  return true;
}
