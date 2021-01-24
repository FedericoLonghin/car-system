//#define ESPb
#define AVRb

#ifdef ESPb
#define TR 12
#define SDA 13
#define SCL 14
#endif

#ifdef AVRb
#define TR 3
#define SDA 4
#define SCL 5
#endif



#include <CAN.h>
#include <OBD2.h>

#define trans_size 16 //16 byte for every transition
bool prevStat;
int timeout_delay = 1000;

byte flags[] = {255, 255, 5};
enum dictionary {
  speed,
  rpm,
  lat,
  longi,
  message,
  another
};

bool boolFlag[16] = { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
byte* Message = ((byte*)"ciao, questo è abbastanza cortino");


int smartSearch = 0;
int maxPidsCount = 1000;
int maxPidsResearchCount = 100;

float *dati = new float[maxPidsResearchCount];
float *enabledpids = new float[maxPidsCount];

typedef enum
{
  Raw = 1,
  Clear = 2,
  Error = 0,
} ReturnType;

ReturnType getPidsValue(int pid, float &value);
void obdSetup();
void fetchData();
long last_fetch = 0;
int fetch_delay = 1000;
void setup() {
  Serial.begin(230400);
  Serial.println("trasmettitore");
  
  pinMode(TR, INPUT);
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);
  
  obdSetup();
  delay(2000);
}


void loop() {
  if (millis() - last_fetch > fetch_delay) {
    Serial.print("Start fetching:");
    Serial.println(millis());
    fetchData();
    last_fetch = millis();
    Serial.print("Finish fetching:");
    Serial.println(millis());
  }
  if (digitalRead(TR)) {
    replyRequest();
  }
}
