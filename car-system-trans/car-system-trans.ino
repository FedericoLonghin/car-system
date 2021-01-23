#include <CAN.h>
#include <OBD2.h>

#define TR 11
#define SDA 12
#define SCL 13

#define speed 500

bool prevStat;



int smartSearch = 1;
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



void setup()
{
	Serial.begin(9600);

	Serial.println("trasmettitore");
	pinMode(TR, INPUT);
	pinMode(SDA, OUTPUT);
	pinMode(SCL, OUTPUT);

	obdSetup();
}
void loop()
{

	if (digitalRead(TR))
	{
		initSequence();

		mandaByte(0x55);
		endSequence();
	}

	fetchData();
}
