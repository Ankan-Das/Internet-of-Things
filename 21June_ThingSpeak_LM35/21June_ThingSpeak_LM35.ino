#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

#define TEMPPIN A0

WiFiClient client;

char ssid[] = "ankan";
char pass[] = "gunsnroses";
int status = WL_IDLE_STATUS;

unsigned long myChannelNumber = 806659;
const char *myWriteAPIKey = "NA5ZMPSVL76MY5CG";

void setup(){
  Serial.begin(115200);
  pinMode(TEMPPIN,INPUT);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
  
  }

void loop(){
  
  delay(3000);

  float h = analogRead(TEMPPIN);

  ThingSpeak.setField(1,h);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  Serial.print("Sensor Value: ");
  Serial.println(h);
  }
