
#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>


#define FIREBASE_HOST "distance-finder-4933c.firebaseio.com"
#define WIFI_SSID "@nk@n"                            // Change the name of your WIFI
#define WIFI_PASSWORD "gunsnroses"                   // Change the password of your WIFI

const int trigP = D4;  //D4 of nodemcu
const int echoP = D3;  //D3 of nodemcu

long duration;
int distance;

void setup() 
{
   Serial.begin(115200);        // Open serial channel at 115200 baud rate  
   pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output
   pinMode(echoP, INPUT);   // Sets the echoPin as an Input
   WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
   Serial.print("connecting");
   while (WiFi.status()!=WL_CONNECTED)
   {
      Serial.print(".");
      delay(500);
   }
   Serial.println();
   Serial.print("connected:");
   Serial.println(WiFi.localIP());

   Firebase.begin(FIREBASE_HOST); 
}

void loop() 
{ 
  digitalWrite(trigP, LOW); // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay 

  digitalWrite(trigP, HIGH);// tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trigP, LOW); // trigPin low

  duration = pulseIn(echoP, HIGH); //Read echo pin, time in microseconds
  distance= duration*0.034/2;        //Calculating actual/real distance
  String Value = String(distance)+ String(" cm");
    
  Serial.print("Distance = ");        //Output distance on arduino serial monitor 
  Serial.println(Value);

  Firebase.setString("SensorValue",Value);
  delay(200);
}
