#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
const char* ssid = "ON_Home";
const char* password = "044349220";
 
const char* html = "<h1>Nap GPIO2 Control</h1><button onClick=\"window.location='/status/1';\">>>>>ON<<<<</button>&nbsp;&nbsp;<button onClick=\"window.location='/status/0';\">>>>>OFF<<<<</button>&nbsp;&nbsp;<button onClick=\"window.location='/status/2';\">>>>>Blink<<<<</button>";
 
ESP8266WebServer server(80);
 
const int led = 2;
 
void setup(void) {
 Serial.begin(115200);
 pinMode(led, OUTPUT);
 
 // Connect to WiFi network
 WiFi.begin(ssid, password);
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
 
 server.on("/", [](){
 server.send(200, "text/html", html);
 });
 
 server.on("/status/0", [](){
 digitalWrite(led, LOW);
 server.send(200, "text/html", html);
 });
 
 server.on("/status/1", [](){
 digitalWrite(led, HIGH);
 server.send(200, "text/html", html);
 });

  server.on("/status/2", [](){
 digitalWrite(led, HIGH);
 delay(1000);
 digitalWrite(led, LOW);
 delay(1000);
  digitalWrite(led, HIGH);
 delay(1000);
 digitalWrite(led, LOW);
 delay(1000);
  digitalWrite(led, HIGH);
 delay(1000);
 digitalWrite(led, LOW);
 delay(1000);
 server.send(200, "text/html", html);
 });
 
 server.on("/api/getstatus", [](){
 if (digitalRead(led))
 server.send(200, "text/plain", "Status:1");
 else
 server.send(200, "text/plain", "Status:0");
 });
 
 server.on("/api/status/0", [](){
 digitalWrite(led, LOW);
 server.send(200, "text/plain", "OK");
 });
 
 server.on("/api/status/1", [](){
 digitalWrite(led, HIGH);
 server.send(200, "text/plain", "OK");
 });
 
 server.begin();
 Serial.println("HTTP server started");
}
 
void loop(void) {
 server.handleClient();
}
