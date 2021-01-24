#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#define TR 12 //1 D1 5
#define SDA 13 // 12 D2 4
#define SCL 14 // 13 D3 0

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "passnode"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);


short speed, rpm;
int fuel_level;
char* message;
int timeout_delay = 500;
bool flags[16];
void setup() {
  ESP.wdtDisable();
  Serial.begin(250000);

  Serial.println("ricevitore");
  pinMode(TR, OUTPUT);
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  digitalWrite(TR, 0);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password, 1, 0);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");


  delay(2000);
  fetchData();
}
void loop() {
  ESP.wdtFeed();
  if (Serial.read() == 'r') {
    fetchData();
  }
  //server.handleClient();
  // fetchData();

}
