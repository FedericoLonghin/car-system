void replyRequest() {

  if (initSequence() ) { //&& sendFlags()
    Serial.println("----------------------------------------------------DATI--------------------------------------------------");
    /* if (boolFlag[0] )
       if (!sendShort(dati[VEHICLE_SPEED]))return false;
      if (boolFlag[1])
       if (!sendShort(dati[ENGINE_RPM]))return false;
      if (boolFlag[2])
       if (!sendInt(dati[FUEL_SYSTEM_STATUS]))return false;
      if (boolFlag[15])
       if (!sendString(Message))return false;
    */
    endSequence();
    Serial.print("All done ");
  } else {
    Serial.println("Sequence aborted: ");
  }
  Serial.println(millis());
}

bool initSequence() {
  Serial.println("Inizio la seq");
  digitalWrite(SCL, 1);
  Serial.println("SCL 1");
  digitalWrite(SDA, 1);
  Serial.println("SDA 1");
  long tf = millis() + timeout_delay;
  while (digitalRead(TR)) {
    Serial.print(".");
    if (millis() > tf) {
      Serial.println("Timeout Aspettando TR che andasse a 0");
      endSequence();
      return false;
    }
    //Aspetto lo tiri giù
  }
  Serial.println("");
  digitalWrite(SCL, 0);
  Serial.println("SCL 0");
  tf = millis() + timeout_delay;
  while (!digitalRead(TR)) {
    //Aspetto lo ritiri su
     if (millis() > tf) {
      Serial.println("Timeout Aspettando TR che andasse a 1");
      endSequence();
      return false;
    }
  }
  digitalWrite(SDA, 0);
  Serial.println("SDA 0");
  tf = millis() + timeout_delay;
  while (digitalRead(TR)) {
    //Aspetto lo tiri giù
     if (millis() > tf) {
      Serial.println("Timeout Aspettando TR che andasse a 0 alla fine");
      endSequence();
      return false;
    }
  }
  Serial.println("Finisco la seq");
  return true;
}

bool sendFlags() {
  Serial.println("----------------------------------------------------FLAGS--------------------------------------------------");
  for ( int i = 0; i < 16; i++) {
    bitWrite(flags[i / 8], i % 8, boolFlag[i]);
  }
  if (!mandaByte(flags, 2))return false;
  if (!sendShort(getLength(Message)))return false;
  Serial.println("--------------------------------------------------FINE FLAGS--------------------------------------------------");
  return true;
}

bool mandaByte(byte *data, int length) {
  for (int j = 0; j < length; j++) {
    Serial.print("mando il byte n.: ");
    Serial.println(j);
    Serial.println(data[j]);
    for (int i = 0; i < 8; i++) {
      Serial.print("invio: ");
      Serial.print(bitRead(data[j], i));
      digitalWrite(SDA, bitRead(data[j], i));

      //Serial.println("Alzo SCL = 1");

      digitalWrite(SCL, 1);
      long tf = millis() + timeout_delay;
      while (!digitalRead(TR)) {
        if (millis() > tf) {
          Serial.println("Timeout (Mi aspetto il TR ad 1 ed è a 0)");
          endSequence();
          return false;
        }
      }
      Serial.print(" ...ricevuto");

      //Serial.println("Abbasso SCL e SDA= 0");

      digitalWrite(SDA, 0);
      digitalWrite(SCL, 0);
      tf = millis() + timeout_delay;
      while (digitalRead(TR)) {
        if (millis() > tf) {
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


bool sendInt(int n) {
  Serial.println("Invio INT");
  byte b[4];
  b[0] = n;
  b[1] = n >> 8;
  b[2] = n >> 16;
  b[3] = n >> 24;
  Serial.println("Done INT");
  return mandaByte(b, 4);

}

bool sendShort(int val) {
  Serial.println("Invio SHORT");
  byte b[4];
  b[0] = val;
  b[1] = val >> 8;
  Serial.println("Done SHORT");
  return mandaByte(b, 2);

}

bool sendString(byte *data) {
  Serial.println("Invio STRING");
  int n = getLength(data);
  Serial.println("Done STRING");
  return mandaByte(data, n);

}


int getLength(byte *value) {
  int i = 0;
  while (value[i] != '\0') {
    i++;
  }
  return i;
}

void endSequence() {
  digitalWrite(SCL, 0);
  Serial.println("Abbasso SCL = 0");
  digitalWrite(SDA, 1);
  Serial.println("Alzo SDA = 1");

}



bool _oldinitSequence() {
  Serial.println("Alzo SCL = 1");
  digitalWrite(SCL, 1);
  long tf = millis() + timeout_delay;
  while (digitalRead(TR)) {
    if (millis() > tf) {
      Serial.println("Timeout init sequenza");
      Serial.println("Abbasso SCL = 0");
      digitalWrite(SCL, 0);
      return false;
    }
  }
  digitalWrite(SCL, 0);

  Serial.println("Abbasso SCL = 0, Lui ha abbassato TR");
  return true;
}
