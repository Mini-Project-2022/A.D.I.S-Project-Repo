// Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
// Blynk IOT Smart Agriculture Monitoring System 

#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

char auth[] = "AMXAWQuF-uGVemwkc9BEH4dwXbw33cwh";               //Authentication code sent by Blynk
char ssid[] = "Joshi -5G";                        //WiFi SSID
char pass[] = "123456789";                        //WiFi Password
              

#define sensorPin D6 
int sensorState;
int lastState = 0;


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}


void loop()
{
  Blynk.run(); 
  sensorState = digitalRead(sensorPin);
  Serial.println(sensorState);

if (sensorState == 1 && lastState == 0) 
{
  Serial.println("needs water, send notification");
  Blynk.notify("Water your plants");
  lastState = 1;
  delay(1000);
//send notification
    
} 
  else if (sensorState == 1 && lastState == 1) {
    //do nothing, has not been watered yet
  Serial.println("has not been watered yet");
  delay(1000);
  }
  else {
    //st
    Serial.println("does not need water");
    lastState = 0;
    delay(1000);
  }




}
