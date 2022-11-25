#include <AsyncElegantOTA.h>
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "ADIS_Sensor_Unit";
const char* password = "miniproject@team1";

const int sensor_pin = 0;
// const float moisturelevel[];
AsyncWebServer server(80);

String readmoisture()
{
  return String(100.00 -((analogRead(sensor_pin)/1023.00) * 100.00));
}
void setup()
{

  Serial.begin(9600);
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

  server.on("/valvestatus", HTTP_GET,[](AsyncWebServerRequest *request)
    {
      if(readmoisture().toFloat()<40.0)
      {
        request->send_P(200, "text/plain", "ON");
      }
      else
      {
        request->send_P(200, "text/plain", "OFF");
      }
    });     
  // else if()
  // {
  //    server.on("/valvestatus", HTTP_GET,[](AsyncWebServerRequest *request)
  //     {
  //       request->send_P(200, "text/plain", "ON");
  //     });   
  // }
  AsyncElegantOTA.begin(&server);  
  server.begin();  
  
}   
void loop()
{
 Serial.println("Moisture Level: "+ readmoisture());
} 