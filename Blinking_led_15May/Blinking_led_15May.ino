int ledPin = 10;


void setup()
{
  pinMode(ledPin, OUTPUT);
} 


void loop()
{
  digitalWrite(ledPin, HIGH);
  delay(1100);
  digitalWrite(ledPin, LOW);
  delay(1100);
} 
