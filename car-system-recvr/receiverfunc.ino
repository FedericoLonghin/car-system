bool readBytes(int length, byte * result) {
  Serial.println("Reading Bytes...");
  result = new byte[length];
  for (int i = 0; i < length; i++) {
    if (!readByte(result[i])) {
      Serial.println("FAILED!");
      return false;
    }
  }
  Serial.println("Done.");
  return true;
}

bool readByte(byte &result) {
  Serial.println("Reading Byte...");
  for (int ibit = 0; ibit < 8; ibit++) {
    bool read;
    if (!readBit(read)) {
      Serial.println("FAILED");
      return false;
    }
    bitWrite(result, ibit, read);
  }
  Serial.println("Done.");
  return true;
}

bool readBit(bool &value) {
  Serial.print("Reading Bit...");
  int tf = millis() + timeout_delay ;
  while (!digitalRead(SCL)) {
    ESP.wdtFeed();
    // Waiting for SCL to became up
    if (millis()   > tf) {
      Serial.println("Timeout (Mi aspetto SCL a 1)");
      endSequence();
      return false;
    }
  }
  value = digitalRead(SDA);
  digitalWrite(TR, 1);
  tf = millis() + timeout_delay;
  Serial.print(value);
  while (digitalRead(SCL)) {
    // Waiting for SCL to became down after reading
    if (millis()   > tf) {
      Serial.println("Timeout (Mi aspetto SCL a 0)");
      endSequence();
      return false;
    }
    ESP.wdtFeed();
  }
  digitalWrite(TR, 0);

  Serial.println(" Done.");
  return true;
}

bool readBools(long length, bool * result ) {
  Serial.println("Reading Bools...");
  result = new bool[length];
  for (int i = 0; i < length; i++) {
    if (! readBit(result[i])) return false;
    //    Serial.print("Bit ");
    //    Serial.print(i);
    //    Serial.print(": ");
    //    Serial.print(result[i]);
  }
  Serial.println("Done.");
  return true;
}
bool readInfo() {
  Serial.println("Reading Info...");
  for (int i = 0; i < 16; i++) {
    if (! readBit(info[i])) return false;
  }
  Serial.println("Done.");
  return true;
}

bool readString(long int length, char * result) {
  Serial.println("Reading String...");
  byte * r;
  if (! readBytes(length, r)) return false;
  r[length] = '\0';
  result = (char*)r;
  Serial.println("Done.");
  return true;
}

bool readInt(int & value) {
  Serial.println("Reading Int...");
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
  Serial.println("Done.");
  return true;
}
bool readShort(short & value) {
  Serial.print("Reading Short...");
  value = 0;
  byte b;
  if (!readByte(b))return false;
  value = (int) (b);
  if (!readByte(b))return false;
  value |=  (int) (b) << 8;
  Serial.println("Done.");
  return true;
}
