#define TR 12 //1 D1 5
#define SDA 13 // 12 D2 4
#define SCL 14 // 13 D3 0

short speed, rpm;
int fuel_level;
String message; 
void setup() {
  ESP.wdtDisable();
  Serial.begin(250000);

  Serial.println("ricevitore");
  pinMode(TR, OUTPUT);
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);

}
void loop() {
    fetchData(); 

 delay(5000);
}
