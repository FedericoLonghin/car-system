bool readBytes(long length, byte * bytes) {
  int time = millis();
  bytes = new byte[length];
  for (int i = 0; i < length; i++) {
    Serial.print("----------------------------Ascolto il byte: ");
    Serial.println(i);
    for (int ibit = 0; ibit < 8; ibit++) {
      while (!digitalRead(SCL)) {
        if (time + 100 < millis()) {
          //return false;
        }
      }                             // Waiting for SCL to became up
      bool read = digitalRead(SDA);
      digitalWrite(TR, 1);
      Serial.println(read);
      bitWrite(bytes[i], ibit, read);
      while (digitalRead(SCL)) {}  // Waiting for SCL to became down after reading
      digitalWrite(TR, 0);
    }
    //Serial.println((char)bytes[i]);
  }
  return true;
}

bool readBools(long length, bool* bools) {

  bools = new bool[length];
  for (int i = 0; i < length; i++) {
    Serial.print("Ascolto il bit: ");
    Serial.println(i);

    while (!digitalRead(SCL)) {} // Waiting for SCL to became up
    bool read = digitalRead(SDA);
    digitalWrite(TR, 1);
    Serial.println(read);
    bools[i] = read;

    while (digitalRead(SCL)) {} // Waiting for SCL to became down after reading
    digitalWrite(TR, 0);

  }
  return true;
}

bool readString(long int length, char* chars) {

  byte * r ;
  readBytes(length, r);
  r[length] = '\0';
  chars = (char*)r;
  return true;
}
bool readInt(int * value) {

  byte * r;
  readBytes(4, r);
  value = new int;

  *value = (int) r[3] << 24;
  *value |=  (int) r[2] << 16;
  *value |= (int) r[1] << 8;
  *value |= (int) r[0];

  return true;
}
bool readShort(short * value) {
  byte * r ;
  readBytes(2, r);
  value = 0;
  Serial.println("COSOOOOSOSOO!");
    Serial.println(*value);

  short t;
  t = (short) r[1] << 8;
  t |= (short) r[0] << 0;
  *value = t;
  return true;
}
void fetchData() {
  Serial.println("Fetching data /n");

  digitalWrite(TR, 1);
  while (!digitalRead(SCL)) {}
  digitalWrite(TR, 0);

  //int s = readShort();
  bool * info;
  readBools(16, info);
  byte * message_size_b;



/*

  readBytes(1, message_size_b);
  int message_size = 0;
  message_size = (int) * message_size_b;


  Serial.println(*message_size_b);

*/
  Serial.println("PRENDO LA LUNGHEZZA");

int * message_size_p;
readShort(message_size_p);

  Serial.println(*message_size_p);



  if (info[0]) {
    Serial.println("Prendo speed");
    readShort(speed);
    Serial.print("Speed: ");
    Serial.println(*speed);
  }
  if (info[1]) {
    Serial.println("Prendo rpm");
    readShort(rpm);
    Serial.print("RPM: ");
    Serial.println(*rpm);
  }
  if (info[2]) {
    Serial.println("Prendo fuel");
    readInt(fuel_level);
    Serial.print("Fuel level: ");
    Serial.println(*fuel_level);
  }

  if (info[15]) {
    Serial.println("Reading message");
    readString(*message_size_p, message);
    Serial.print("Message: ");
    Serial.println(*message);
  }


}
