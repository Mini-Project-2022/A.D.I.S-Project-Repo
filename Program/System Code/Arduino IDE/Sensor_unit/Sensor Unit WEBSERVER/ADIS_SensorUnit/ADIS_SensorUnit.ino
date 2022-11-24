#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "ADIS_Sensor_Unit";
const char* password = "miniproject@team1";

const int sensor_pin = A0;
// const float moisturelevel[];
AsyncWebServer server(80);

String readmoisture()
{
  return String(100.00 -((analogRead(sensor_pin)/1023.00) * 100.00));
}
void setup()
{

  Serial.begin(115200);
  Serial.println();
  

  Serial.print("Setting AP (Access Point)…");

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

    
  server.on("/moisturelevel", HTTP_GET,[](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/plain", readmoisture().c_str());
  });
  if(readmoisture().toFloat()>=50.0)
  {
    server.on("/valvestatus", HTTP_GET,[](AsyncWebServerRequest *request)
      {
        request->send_P(200, "text/plain", "ON");
      });    
  }  
  else
  {
     server.on("/valvestatus", HTTP_GET,[](AsyncWebServerRequest *request)
      {
        request->send_P(200, "text/plain", "OFF");
      });   
  }  
  server.begin();  
  
}   
void loop()
{
 
} 