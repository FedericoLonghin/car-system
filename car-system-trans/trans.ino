void replyRequest(){
  initSequence();


    sendFlags();

    if (boolFlag[0] ) sendShort(56);
    if (boolFlag[1])  sendShort(46);
    if (boolFlag[2]) sendInt(20);
    if (boolFlag[15]) sendString(Message);

    endSequence();
    Serial.println("All done");
}

void initSequence() {
  //Serial.print("inizio la sequenza...");
  digitalWrite(SCL, 1);
  while (digitalRead(TR)) {}
  digitalWrite(SCL, 0);
  //Serial.println("Fatto");
}



void mandaByte(byte data[256], int length) {
  for (int j = 0; j < length; j++) {
    Serial.print("mando il byte n.: ");
    Serial.println(j);
    for (int i = 0; i < 8; i++) {
      Serial.print("invio: ");
      Serial.print(bitRead(data[j], i));
      digitalWrite(SDA, bitRead(data[j], i));

      digitalWrite(SCL, 1);
      while (!digitalRead(TR)) {
      //  ESP.wdtFeed();
        // Serial.print(".");
      }
      Serial.print(" ...ricevuto");
      digitalWrite(SDA, 0);
      digitalWrite(SCL, 0);
      while (digitalRead(TR)) {  //Serial.print(",");
      //  ESP.wdtFeed();
      }
      Serial.println(" | esco");
    }
  }
}

void endSequence() {
  //Serial.print("finisco la sequenza...");

  digitalWrite(SCL, 0);
  digitalWrite(SDA, 1);
  //Serial.println("Fatto");

}



void sendInt(int n) {
  byte b[4];
  b[0] = n;
  b[1] = n >> 8;
  b[2] = n >> 16;
  b[3] = n >> 24;
  mandaByte(b, 4);

}

void sendShort(int val) {
  byte b[4];
  b[0] = val;
  b[1] = val >> 8;
  mandaByte(b, 2);

}

void sendString(byte data[256]) {
int n=getLength(data);
  mandaByte(data, n);

}

void sendFlags() {
  Serial.println("----------------------------------------------------FLAGS--------------------------------------------------");
  for( int i = 0; i < 16; i++) {
  bitWrite(flags[i / 8], i % 8, boolFlag[i]);
  }

 mandaByte(flags, 2);
 sendShort(getLength(Message));
}


int getLength(byte value[256]){
  int i=0; 
  while(value[i]!='\0'){i++;}
  return i;
}
