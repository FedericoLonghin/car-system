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
#define RST_EXT A0
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
bool obdStatus = 0;
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
long last_obd_check = 0;
int obd_check_delay = 5000;

void setup() {
  Serial.begin(230400);
  Serial.println("trasmettitore");

  pinMode(TR, INPUT);
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);
  pinMode(RST_EXT, OUTPUT);

  digitalWrite(SDA, 0);
  digitalWrite(SCL, 0);
  
  digitalWrite(RST_EXT, 1);
  obdSetup();
  digitalWrite(RST_EXT, 0);
  delay(100);
  digitalWrite(RST_EXT, 1);
  //delay(2000);
}


void loop() {

  if (millis() - last_fetch > fetch_delay && 0) {
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
  if (!obdStatus && millis() - last_obd_check > obd_check_delay && 0) {
    obdSetup();
    last_obd_check = millis();
  }
}
