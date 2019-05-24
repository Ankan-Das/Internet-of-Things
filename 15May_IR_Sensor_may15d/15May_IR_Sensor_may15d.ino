int sensorPIN = 10;
int ledPIN = 13;
int val = 0;

void setup() {
  pinMode(sensor_PIN, INPUT);
  pinMode(led_PIN, OUTPUT);
}

void loop() {

  val = digitalRead(sensor_PIN); 
    
  if(val==HIGH)
    {
      digitalWrite(led_PIN, HIGH);
      delay(100);
    }
  else if(val==LOW)
    {
      digitalWrite(led_PIN, LOW);
      delay(100);}
    }
