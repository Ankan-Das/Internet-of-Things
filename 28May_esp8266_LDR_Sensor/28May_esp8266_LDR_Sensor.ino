// code for LDR
#include <SoftwareSerial.h>
#define LDRpin A0 // pin where we connected the LDR and the resistor

int LDRValue = 0;     // result of reading the analog pin

void setup() {
  Serial.begin(115200); // sets serial port for communication
  
}

void loop() {
  LDRValue = analogRead(LDRpin); // read the value from the LDR
  Serial.println(LDRValue);      // print the value to the serial port
  delay(1000);                    // wait a little
}
