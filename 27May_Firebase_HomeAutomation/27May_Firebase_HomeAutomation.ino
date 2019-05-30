#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST "home-automation-523a2.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define WIFI_SSID "@nk@n"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "gunsnroses"                                      //Password of your wifi network 

#define Relay1 D2 
int val1;

#define Relay2 D6 
int val2;

#define Relay3 D7  
int val3;

#define Relay4 D8 
int val4;

void setup() 
{
  Serial.begin(115200);                                                   // Select the same baud rate if you want to see the datas on Serial Monitor
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);

  digitalWrite(Relay1,HIGH);
  digitalWrite(Relay2,HIGH);
  digitalWrite(Relay3,HIGH);
  digitalWrite(Relay4,HIGH);

  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST); //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("S1",0);                     //Here the varialbe"S1","S2","S3" and "S4" needs to be the one which is used in our Firebase and MIT App Inventor
  Firebase.setInt("S2",0); 
  Firebase.setInt("S3",0); 
  Firebase.setInt("S4",0); 
  
}

void loop() 
{
 val1=Firebase.getString("S1").toInt();                                        //Reading the value of the varialble Status from the firebase  
  if(val1==1)                                                             // If, the Status is 1, turn on the Relay1
  {
      digitalWrite(Relay1,LOW);
      Serial.println("light 1 OFF");
  }
  if(val1==0)                                                      // If, the Status is 0, turn Off the Relay1
  {                                      
     digitalWrite(Relay1,HIGH);
     Serial.println("light 1 ON");
   }

  val2=Firebase.getString("S2").toInt();                                        //Reading the value of the varialble Status from the firebase
  
  if(val2==1)                                                             // If, the Status is 1, turn on the Relay2
     {
      digitalWrite(Relay2,LOW);
      Serial.println("light 2 OFF");
    }
    if(val2==0)                                                      // If, the Status is 0, turn Off the Relay2
    {                                      
      digitalWrite(Relay2,HIGH);
      Serial.println("light 2 ON");
    }

   val3=Firebase.getString("S3").toInt();                                        //Reading the value of the varialble Status from the firebase
  
  if(val3==1)                                                             // If, the Status is 1, turn on the Relay3
     {
      digitalWrite(Relay3,LOW);
      Serial.println("light 3 OFF");
    }
    if(val3==0)                                                      // If, the Status is 0, turn Off the Relay3
    {                                      
      digitalWrite(Relay3,HIGH);
      Serial.println("light 3 ON");
    }

   val4=Firebase.getString("S4").toInt();                                        //Reading the value of the varialble Status from the firebase
  if(val4==1)                                                             // If, the Status is 1, turn on the Relay4
     {
      digitalWrite(Relay4,LOW);
      Serial.println("light 4 OFF");
    }
    if(val4==0)                                                      // If, the Status is 0, turn Off the Relay4
    {                                      
      digitalWrite(Relay4,HIGH);
      Serial.println("light 4 ON");
    }    
}
