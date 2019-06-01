#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "dongle";
const char* password = "TEST0562";
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
String text = "";
int data;
 
void setup(){
 pinMode(A0, INPUT);
 delay(1000);
 Serial.begin(115200);
 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  
  Serial.println("");
  Serial.println("Client-------------------------------");
  Serial.print("Connecting to Network");
  WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password); //begin WiFi connection
 Serial.println("");
 
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
   page = "<h1>ESP8266 Web Server</h1><h1>Sensor Reading:</h1><h1 id=\"data\"></h1>""\r\n";
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
 String rx_byte = "";
String inString = ""; 
 
void loop(){

   while (Serial.available() > 0) {
    int inChar = Serial.read();
    
    
    if (isDigit(inChar)) {
      
      inString += (char)inChar;
    }
   
    if (inChar == '\n') {

      data=inString.toInt();
     
      server.handleClient();
    Serial.println(data);
      delay(200);

      inString = "";
    }
  }

 
}
