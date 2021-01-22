#include <CAN.h> 
#include <OBD2.h>

#define TR 11
#define SDA 12
#define SCL 13

#define speed 500


bool prevStat;

void setup() {
  Serial.begin(9600);

  Serial.println("trasmettitore");
  pinMode(TR, INPUT);
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);

  obdSetup();

}
void loop() {



  if (digitalRead(TR)) {
    initSequence();
    mandaByte(0x55);
    endSequence();
  }



}
