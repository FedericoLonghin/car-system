#define TR 11
#define SDA 12
#define SCL 13

short speed, rpm;
int fuel_level;
String message; 
void setup() {
  Serial.begin(250000);

  Serial.println("ricevitore");
  pinMode(TR, OUTPUT);
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  pinMode(2, INPUT_PULLUP);
  fetchData(); 

}
void loop() {
 // delay(5000);
}
