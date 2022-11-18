#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "Sanarth-01"
#define WIFI_PASSWORD "12345667"

#define API_KEY "EMZekUSqeVlBNsdr0ccJO1KhHWhpHCQMAN3KCuPP"
#define DATABASE_URL "mini-project-12-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData Reading;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
const int sensor_pin = A0;
void setup(){
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.begin(&config,&auth)){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop()
{ float moisture_percentage;
  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 9000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    Firebase.RTDB.setFloat(&Reading, "Soil Moisture(in Percentage) = ", moisture_percentage)
    Serial.println("Soil Moisture(in Percentage) = ");
    Serial.println(Firebase.RTDB.getFloat(&Reading, "Soil Moisture(in Percentage) = "));
    
  }
}