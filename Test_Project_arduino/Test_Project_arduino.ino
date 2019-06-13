// code for LDR
#include <SoftwareSerial.h>
#define LDRpin A0 // pin where we connected the LDR and the resistor
#define LM35pin A1

int LDRValue = 0;     // result of reading the analog pin
int LM35Value = 0;

void setup() {
  Serial.begin(115200); // sets serial port for communication
  
}

void loop() {
  LDRValue = analogRead(LDRpin); // read the value from the LDR
  LM35Value = analogRead(LM35pin); 
  
  Serial.println(LDRValue);      // print the value to the serial port
  Serial.println(LM35Value);
  
  delay(1000);                    // wait a little
}
