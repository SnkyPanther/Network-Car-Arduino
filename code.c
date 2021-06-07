#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#ifndef STASSID
#define STASSID "RouterName"  //put in the router name
#define STAPSK  "password"  //put in the password
#endif
Ticker runStepper;

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

//int state = 0, rstate = 0;
int mSpeed=50;

  void spinFront() {
    digitalWrite(D0, HIGH);
    tone(D1, mSpeed);
    tone(D3, mSpeed);
    digitalWrite(D2, LOW);
    digitalWrite(D4, HIGH);
    server.send(200, "text/html", " ");
  }

  void spinLeft() {
    digitalWrite(D0, HIGH);
    tone(D1, mSpeed);
    tone(D3, mSpeed);
    digitalWrite(D2, LOW);
    digitalWrite(D4, LOW);
    server.send(200, "text/html", " ");
  }
  
  void spinRight() {
    digitalWrite(D0, HIGH);
    tone(D1, mSpeed);
    tone(D3, mSpeed);
    digitalWrite(D2, HIGH);
    digitalWrite(D4,HIGH);
    server.send(200, "text/html", " ");
  }
  
  void spinBack(){
    digitalWrite(D0, HIGH);
    tone(D1, mSpeed);
    tone(D3, mSpeed);
    digitalWrite(D2, HIGH);
    digitalWrite(D4, LOW);
    server.send(200, "text/html", " ");
  }
  
  void handleRoot(){
    server.send(200, "text/html", "<!DOCTYPE html><html><body><div id=\"demo\"><h1>The Ultimate Object</h1><button style=\"margin-left: 35px; margin-bottom: 10px\" type=\"button\" onclick=\"loadDoc('/front')\">&uarr;</button></br><button type=\"button\" onclick=\"loadDoc('/left')\">&larr;</button><button type=\"button\" onclick=\"loadDoc('/stop')\">&#128721</button><button type=\"button\" onclick=\"loadDoc('/right')\">&rarr;</button></br><button style=\"margin-left: 35px; margin-top: 10px\" type=\"button\" onclick=\"loadDoc('/back')\">&darr;</button></div><script>function loadDoc(url) {var xhttp = new XMLHttpRequest();xhttp.onreadystatechange = function() {};xhttp.open(\"GET\", url, true);xhttp.send();}</script></body></html>");
  }
  
  void spinStop(){
    digitalWrite(D0, LOW);
    server.send(200, "text/html", " ");
  }
  

 
 
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
    pinMode(LED_BUILTIN, OUTPUT);
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

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);
  pinMode(D6, OUTPUT);
  digitalWrite(D6, LOW);
  pinMode(D7, OUTPUT);
  digitalWrite(D7, LOW);
  pinMode(D8, OUTPUT);
  digitalWrite(D8, LOW);
  server.on("/", handleRoot);
  server.on("/front", spinFront);
  server.on("/back", spinBack);
  server.on("/stop", spinStop);
  server.on("/right", spinRight);
  server.on("/left", spinLeft);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
//  runStepper.attach_ms(3, takeAStep);
}
int count=0;
void loop(void) {
  server.handleClient();
  MDNS.update();
}
