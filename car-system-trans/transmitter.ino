bool replyRequest() {
  Serial.print("inizio la sequenza..:");
  Serial.println(millis());
  if (initSequence()) {
    sendFlags();

    //float value = 3;
    //if (boolFlag[0] && getPidsValue(VEHICLE_SPEED, value)) sendShort(value);
    //if (boolFlag[1] && getPidsValue(ENGINE_RPM, value))  sendShort(value);
    //if (boolFlag[2] && getPidsValue(FUEL_SYSTEM_STATUS, value)) sendInt(value);

    if (boolFlag[0] )
      if (!sendShort(dati[VEHICLE_SPEED]))return false;
    if (boolFlag[1])
      if (!sendShort(dati[ENGINE_RPM]))return false;
    if (boolFlag[2])
      if (!sendInt(dati[FUEL_SYSTEM_STATUS]))return false;
    if (boolFlag[15])
      if (!sendString(Message))return false;

    endSequence();
    Serial.print("All done");
  } else {
    Serial.print("Sequence aborted: ");
  }
  Serial.println(millis());
}

bool initSequence() {
  digitalWrite(SCL, 1);
  long t0 = millis();
  while (digitalRead(TR)) {
    if (millis() - timeout_delay > t0) {
      Serial.println("Timeout init sequenza");
      digitalWrite(SCL, 0);
      return false;
    }
  }
  digitalWrite(SCL, 0);
  return true;
}

bool mandaByte(byte *data, int length) {
  for (int j = 0; j < length; j++) {
    Serial.print("mando il byte n.: ");
    Serial.println(j);
    for (int i = 0; i < 8; i++) {
      Serial.print("invio: ");
      Serial.print(bitRead(data[j], i));
      digitalWrite(SDA, bitRead(data[j], i));

      digitalWrite(SCL, 1);
      long t0 = millis();
      while (!digitalRead(TR)) {
        //  ESP.wdtFeed();
        // Serial.print(".");
        if (millis() - timeout_delay > t0) {
          Serial.println("Timeout (Mi aspetto il TR ad 1 ed è a 0)");
          endSequence();
          return false;
        }
      }
      Serial.print(" ...ricevuto");
      digitalWrite(SDA, 0);
      digitalWrite(SCL, 0);
      t0 = millis();
      while (digitalRead(TR)) {  //Serial.print(",");
        //  ESP.wdtFeed();
        if (millis() - timeout_delay > t0) {
          Serial.println("Timeout  (Mi aspetto il TR ad 0 ed è a 1)");
          endSequence();
          return false;
        }
      }
      Serial.println(" | esco");
    }
  }
  return true;
}

void endSequence() {
  //Serial.print("finisco la sequenza...");

  digitalWrite(SCL, 0);
  digitalWrite(SDA, 1);
  //Serial.println("Fatto");

}



bool sendInt(int n) {
  byte b[4];
  b[0] = n;
  b[1] = n >> 8;
  b[2] = n >> 16;
  b[3] = n >> 24;
  return mandaByte(b, 4);

}

bool sendShort(int val) {
  byte b[4];
  b[0] = val;
  b[1] = val >> 8;
  return mandaByte(b, 2);

}

bool sendString(byte *data) {
  int n = getLength(data);
  return mandaByte(data, n);

}

void sendFlags() {
  Serial.println("----------------------------------------------------FLAGS--------------------------------------------------");
  for ( int i = 0; i < 16; i++) {
    bitWrite(flags[i / 8], i % 8, boolFlag[i]);
  }
  mandaByte(flags, 2);
  sendShort(getLength(Message));
}


int getLength(byte *value) {
  int i = 0;
  while (value[i] != '\0') {
    i++;
  }
  return i;
}
