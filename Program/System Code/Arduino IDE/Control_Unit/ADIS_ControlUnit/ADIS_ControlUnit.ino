#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

const char* ssid = "ADIS_Sensor_Unit";
const char* password = "miniproject@team1";

const char* moistureserver = "http://192.168.4.1/moisturelevel";
const char* statusserver = "http://192.168.4.1/valvestatus";

unsigned long previousMillis = 0;
const long interval = 5000; 

String soilmoisture;
String valvestate;

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
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

String httpGETRequest(const char* serverName) 
{
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);
  
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) 
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else 
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}