#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "ankan";
const char* password = "gunsnroses";
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
String text = "";
String text2 = "";
int data;
int data2;
String output = "";
 
void setup(){
 pinMode(A0, INPUT);
 delay(1000);
 Serial.begin(115200);
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
 
// server.on("/data.txt", [](){
//   text = (String)data;
//   server.send(200, "text/html", text);
// });

  server.on("/output.txt", [](){
   text2 = (String)output;
   server.send(200, "text2/html", text2);
 });
 
// server.on("/", [](){
//   page = "<h1>ESP8266 Web Server</h1><h1>1st Sensor Reading:</h1><h1 id=\"data\"></h1>""\r\n";
//   page += "<h1>2nd Sensor Reading:</h1><h1 id=\"data\"></h1>""\r\n";
//   page += "<script>\r\n";
//   page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
//   page += "function loadData(url, callback){\r\n";
//   page += "var xhttp = new XMLHttpRequest();\r\n";
//   page += "xhttp.onreadystatechange = function(){\r\n";
//   page += " if(this.readyState == 4 && this.status == 200){\r\n";
//   page += " callback.apply(xhttp);\r\n";
//   page += " }\r\n";
//   page += "};\r\n";
//   page += "xhttp.open(\"GET\", url, true);\r\n";
//   page += "xhttp.send();\r\n";
//   page += "}\r\n";
//   page += "function updateData(){\r\n";
//   page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
//   page += "}\r\n";
//   
//   page += "</script>\r\n";
//   server.send(200, "text/html", page);
//});
 
 server.on("/", [](){
   page = "<h1>ESP8266 Web Server</h1>""\r\n";  //<h1>1st Sensor Reading:</h1><h1 id=\"data\"></h1>""\r\n";
   page += "<h1 id=\"output\"></h1>""\r\n";
   page += "<script>\r\n";
   page += "var y = setInterval(function() {loadData(\"output.txt\",updateData)}, 400);\r\n";
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
   page += " document.getElementById(\"output\").innerHTML = this.responseText;\r\n";
   page += "}\r\n";
   page += "</script>\r\n";
   server.send(200, "text/html", page);
});
 
 server.begin();
 Serial.println("Web server started!");
}
 String rx_byte = "";
String inString = ""; 
String inString2 = "";

 
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

  while (Serial.available() > 0) {
    int inChar2 = Serial.read();
    if (isDigit(inChar2)) {
      
      inString2 += (char)inChar2;
    }
   
    if (inChar2 == '\n') {

      data2=inString2.toInt();
     
      server.handleClient();
      Serial.println(data2);
      delay(200);

      inString2 = "";
    }
  }

  output = "1st Sensor Reading:" + (String)data2 + "\n   2nd Sensor Reading:" + (String)data+" " ;
  Serial.println(output);
}


/* IDEAS: 1. Try putting everything indication and values inside data itself and then use the ajax code
          2. If time permits enough, use JQuery. Or do it after midsems   */

          
