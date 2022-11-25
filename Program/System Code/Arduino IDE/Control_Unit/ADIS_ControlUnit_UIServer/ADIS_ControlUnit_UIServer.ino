#include <HttpClient.h>
#include <b64.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "ESPAsyncWebServer.h"
#include <AsyncElegantOTA.h>

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

const char* server_ssid = "ADIS_Control_Unit";
const char* server_password = "miniproject@team1";

const char* ssid = "ADIS_Sensor_Unit";
const char* password = "miniproject@team1";

const char* moistureserver = "http://192.168.4.1/moisturelevel";
const char* statusserver = "http://192.168.4.1/valvestatus";

unsigned long previousMillis = 0;
const long interval = 5000; 

String soilmoisture;
String valvestate;

char* soilmoisture_UI;
char* valvestate_UI;

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(server_ssid, server_password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP); 
  server.on("/", HTTP_GET,[](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/plain",updateuipage().c_str());
  });
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.println();
  // soilmoisture_UI=soilmoisture;
  // valvestate_UI=valvestate;      
  
  AsyncElegantOTA.begin(&server);  
  server.begin(); 

}

void loop()
{
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) 
  {
     // Check WiFi connection status
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      soilmoisture = httpGETRequest(moistureserver);
      valvestate = httpGETRequest(statusserver);
      Serial.println("Soil Moisture Level: " + soilmoisture + " %");
      Serial.println("Valve State: " + valvestate);
      
         
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
   
}
String updateuipage()
{
  return String("Moisture Level: "+String(soilmoisture)+" %"+" Valve Status: "+String(valvestate));
}
String httpGETRequest(const char* serverName) 
{
  WiFiClient client;
  HTTPClient http;
  http.begin(client,serverName);
  
  int httpResponseCode = http.GET(); 
  // int httpResponseCode =1; 
  String payload= "--";
  if (httpResponseCode>0) 
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
  }
  else 
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}