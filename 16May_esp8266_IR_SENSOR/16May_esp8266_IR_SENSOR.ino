// IR sensor
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
const int ProxSensor= 2;  // Connect to IR sensor
 const int led=0;  
// Replace with your network credentials
const char* ssid = "dongle";
const char* password = "TEST0562";
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
String text = "";
//double data;
 String data="";
void setup(void){
 pinMode(A0, INPUT);
 delay(1000);
 Serial.begin(115200);
 WiFi.begin(ssid, password); //begin WiFi connection
 Serial.println("");
 pinMode(ProxSensor,INPUT);
 // Wait for connection
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
}
 
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 server.on("/data.txt", [](){
   text = (String)data;
   server.send(200, "text/html", text);
 });
 server.on("/", [](){
   page = "<h1>Sensor to ESP8266 Web Server</h1><h1>IR status:</h1><h1 id=\"data\"></h1>""\r\n";
   page += "<script>\r\n";
   page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
   page += "function loadData(url, callback){\r\n";
   page += "var xhttp = new XMLHttpRequest();\r\n";
   page += "xhttp.onreadystatechange = function(){\r\n";
   page += " if(this.readyState == 4 && this.status == 200){\r\n";
   page += " callback.apply(xhttp);\r\n";
   page += " }\r\n";
   page += "};\r\n";
   page += "xhttp.open(\"GET\", url, true);\r\n";
   page += "xhttp.send();\r\n";
   page += "}\r\n";
   page += "function updateData(){\r\n";
   page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
   page += "}\r\n";
   page += "</script>\r\n";
   server.send(200, "text/html", page);
});
 
 server.begin();
 Serial.println("Web server started!");
}
 
void loop(void){

 if(digitalRead(ProxSensor)==LOW)      //Check the sensor output
  {
    digitalWrite(led, HIGH);   // set the LED on
    Serial.println("Clear");
    data = "Clear";
    server.handleClient();
  }
  else
  {
    digitalWrite(led, LOW);     // set the LED off
    Serial.println("Obstacle detected");
    data = "Obstacle detected";
    server.handleClient();
  }
  
 delay(200);
}
