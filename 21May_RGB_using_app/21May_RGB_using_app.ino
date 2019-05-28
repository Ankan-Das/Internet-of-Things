#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "dongle";      
const char* password = "TEST0562"; 
WiFiServer server(80);

int RED = D6;
int GREEN = D7;
int BLUE = D8;

void setup() 
{
  Serial.begin(115200);
  delay(10);    
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
void loop() 
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

   if (request.indexOf("/R")!=-1) 
   {
      digitalWrite(RED,HIGH);
      digitalWrite(GREEN,LOW);
      digitalWrite(BLUE,LOW);
   }
   if (request.indexOf("/G")!=-1) 
   {
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,HIGH);
      digitalWrite(BLUE,LOW); 
   }
   if (request.indexOf("/B")!=-1) 
   {
       digitalWrite(RED,LOW);
       digitalWrite(GREEN,LOW);
       digitalWrite(BLUE,HIGH);
   }
   if (request.indexOf("/W")!=-1) 
   {  
      digitalWrite(RED,HIGH);
      digitalWrite(GREEN,HIGH);
      digitalWrite(BLUE,HIGH);
   }
   if (request.indexOf("/O")!=-1) 
   {  
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,LOW);
      digitalWrite(BLUE,LOW);
   }
   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println(""); 
   client.println("<!DOCTYPE HTML>");
   client.println("<html>");
   client.println("<br><br>");
   client.println("<center>");
   client.print("<a href=\"/R\"><button> RED </button></a><br><br>");
   client.print("<a href=\"/G\"><button> GREEN</button></a><br><br>");
   client.print("<a href=\"/B\"><button> BLUE</button></a><br><br>");
   client.print("<a href=\"/W\"><button> WHITE </button></a><br><br>");
   client.print("<a href=\"/O\"><button> NO LIGHT</button></a><br><br>");
   client.println("</center>");
   client.println("</html>"); 
   delay(1);
   Serial.println("Client disonnected");
   Serial.println("");
}
