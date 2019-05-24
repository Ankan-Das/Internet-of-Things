int sensorPIN = 10;
int ledPIN = 13;
int val = 0;

void setup() {
  pinMode(sensorPIN, INPUT);
  pinMode(ledPIN, OUTPUT);
}

void loop() {

  val = digitalRead(sensorPIN); 
    
  if(val==HIGH)
    {
      digitalWrite(ledPIN, HIGH);
      delay(100);
    }
  else if(val==LOW)
    {
      digitalWrite(ledPIN, LOW);
      delay(100);}
    }
