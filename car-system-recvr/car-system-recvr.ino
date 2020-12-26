#define TR 11
#define SDA 12
#define SCL 13

#define speed 500
bool prevStat;
byte result[16];

void setup() {
  ////Serial.begin(250000);

  //Serial.println("ricevitore");
  pinMode(TR, OUTPUT);
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);



  delay(1000);

  digitalWrite(TR, 1);
  while (!digitalRead(SCL)) {}
  delay(100);
  digitalWrite(TR, 0);

  riceviByte();

String myString = String((char*)result);

Serial.println(myString);


}
void loop() {

  
  //Serial.print("TR: ");
  //Serial.print(4 + digitalRead(TR));

  //Serial.print("  SDA: ");


  //Serial.print(2 + digitalRead(SDA));

  //Serial.print("  SCL: ");

  //Serial.print(digitalRead(SCL));
  //Serial.println("");

}
