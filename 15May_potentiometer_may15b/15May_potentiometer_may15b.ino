#include <Servo.h>

Servo S1;

int value = 0;
int potenPIN = A2;
int Angle = 0;

void setup() {
 Serial.begin(9600);
 S1.attach(9);
}

void loop() {

  value = analogRead(potenPIN);

  Serial.println(value);
value=map(value,0,1023,0,179);
  Angle = (value);
  
    S1.write(Angle);
    delay(50);
}
