#include <FirebaseESP8266.h> // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "mini-project-12-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "EMZekUSqeVlBNsdr0ccJO1KhHWhpHCQMAN3KCuPP"
#define WIFI_SSID "Sanarth-01" // wifi name
#define WIFI_PASSWORD "12345667" // Wifi Password

const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */

void setup()
 {
   Serial.begin(9600);
   delay(1000);
   pinMode (sensor_pin, OUTPUT);
   WiFi. begin (WIFI_SSID, WIFI_PASSWORD);
   Serial. print("connecting to ");
   Serial. print (WIFI_SSID);
   while (WiFi. status() != WL_CONNECTED)
   {
    Serial.print(".");
    delay (500);
   }
   Serial.println();
   Serial. print("Connected to ");
   Serial. println (WIFI_SSID);
   Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  }

void loop()
{
  float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  Firebase.setString("Soil Moisture(in Percentage) = " , (moisture_percentage));
    
  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(Firebase.getString("Soil Moisture(in Percentage) = ");
  Serial.print();
  Serial.println("%");
  delay(1000);
}