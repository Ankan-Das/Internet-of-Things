#include <SoftwareSerial.h>
const int trigP = 4;  //D4 
const int echoP = 3;  //D3 
long duration;
int distance;
  
void setup() {
pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output
pinMode(echoP, INPUT);   // Sets the echoPin as an Input
Serial.begin(115200);        // Open serial channel at 115200 baud rate
}


void loop() {

digitalWrite(trigP, LOW); // Makes trigPin low
delayMicroseconds(2);       // 2 micro second delay 

digitalWrite(trigP, HIGH);// tigPin high
delayMicroseconds(10);      // trigPin high for 10 micro seconds
digitalWrite(trigP, LOW); // trigPin low

duration = pulseIn(echoP, HIGH); //Read echo pin, time in microseconds
distance= duration*0.034/2;        //Calculating actual/real distance


Serial.println(distance);
delay(1000);                        //Pause for 1 seconds and start measuring distance again
}
