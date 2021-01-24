



bool fetchData() {
  Serial.println("Fetching data...");
  if (!initSequence())return false;
  
  if (!readFlags()) {
    Serial.println("Error in Flags");
    return false;
  }

  short message_size;
  if (!readShort(message_size)) {
    Serial.println("Error in Short");
    return false;
  }
  Serial.println("CI SONO");
  Serial.println(flags[0]);

  for (int a = 0; a < 16; a++) {
    Serial.print(flags[a]);
    Serial.print(" ");
  }
  Serial.println("");
  if (flags[0]) {
    Serial.println("Prendo speed");
    delay(300);
    if (!readShort(speed))return false;
    Serial.print("Speed: ");
    Serial.println(speed);
  }
  if (flags[1]) {
    Serial.println("Prendo rpm");
    if (!readShort(rpm))return false;
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
  if (flags[2]) {
    Serial.println("Prendo fuel");
    if (!readInt(fuel_level))return false;
    Serial.print("Fuel level: ");
    Serial.println(fuel_level);
  }
  if (flags[15]) {
    Serial.println("Reading message");
    if (!readString(message_size, message))return false;
    Serial.print("Message: ");
    Serial.println(message);
  }
  Serial.println("Done!");
  return true;
}



bool notAnInitSequence() {
  Serial.println("Init Sequence");
  long tf = millis() + timeout_delay;
  digitalWrite(TR, 1);
  while (!digitalRead(SCL))
  {
    Serial.print(".");
    if (millis() > tf) {
      Serial.print("Millis: ");
      Serial.print(millis());
      Serial.print(" timeout: ");
      Serial.println(tf);
      Serial.println("Waiting for !SCL... Exit");
      return false;
    }
    ESP.wdtFeed();
  }
  digitalWrite(TR, 0);
  Serial.println("");

  //  while (digitalRead(SCL)) {
  //    ESP.wdtFeed();
  //    Serial.println("waiting for !SCL");
  //  }
  Serial.println("Sequence initalized");
  return true;
}


bool initSequence() {
  Serial.println("TR=1");
  digitalWrite(TR, 1);
  Serial.println("? !SDA !SCL /n");
  while ( !digitalRead(SCL) ||  !digitalRead(SDA)) {
    Serial.print("."); //aspetto che vengano alzati
  }
  Serial.println("TR=0");
  digitalWrite(TR, 0);
  Serial.println("? SDA SCL /n");
  while (digitalRead(SCL)) { //MANCHEREBBE SDA MA SHALLA PER ORA
    Serial.print(".");
  }
  Serial.println("if SDA !SCL");


  Serial.println("TR=1");
  digitalWrite(TR, 1);

  Serial.println("?SDA");
  while (digitalRead(SDA)) {
    Serial.print(".");
  }
  Serial.println("TR=0");
  digitalWrite(TR, 0);
  Serial.println("FATTO");
  return 1;
}


void endSequence() {
  Serial.print("Ending Sequence... ");
  digitalWrite(TR, 0);
  Serial.println("DONE!!!.");
}
