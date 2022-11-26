#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;

#define ON_Board_LED 2
// #define Valve_pin D7
const int Valve_pin = 13;

const char* ssid = "G";             // --> wifi name
const char* password = "12345678";  //--> wifi password

const char *host = "https://domestic-irrigation.000webhostapp.com:80/";

// uint8_t Valve_pin = D2;

String inString = "";
void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(ON_Board_LED, OUTPUT);
  digitalWrite(ON_Board_LED, HIGH);
  pinMode(Valve_pin, OUTPUT);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH);
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
  HTTPClient http;
  String GetAddress, LinkGet, getData, LEDStatResultSend;
  int wid = 0;          
  GetAddress = "GetData.php";
  LinkGet = host + GetAddress;
  getData = "ID=" + String(wid);
  Serial.println("----------------Connect to Server-----------------");
  Serial.println("Get LED Status from Server or Database");
  Serial.print("Request Link : ");
  Serial.println(LinkGet);
  http.begin(wifiClient, LinkGet); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCodeGet = http.POST(getData);
  String payloadGet = http.getString();
    Serial.print("Response Code : ");
  Serial.println(httpCodeGet);
  Serial.print("Returned data from Server : ");
  Serial.println(payloadGet);
  String Status = payloadGet.substring(0, payloadGet.indexOf(","));
  Serial.println(Status);
  // char valveactuate= payloadGet[1];
  // Serial.print(payloadGet[0]);
  // Serial.print("-");
  // Serial.print(payloadGet[1]);
  // Serial.print("-");
  // Serial.print(payloadGet[2]);
  // Serial.print("-");
  // Serial.print(payloadGet[3]);
  // Serial.print("-");
  // Serial.println(payloadGet[4]);
  // Serial.print("ValveStatus");
  // Serial.println(valveactuate);
  // if(payloadGet.indexOf('0')==0)
  // {   
  //   digitalWrite(Valve_pin, LOW); 
  //   Serial.println("Valve OFF");
  // }
  // else if(payloadGet.indexOf('1')==0)
  // {
  //   digitalWrite(Valve_pin, HIGH);
  //   Serial.println("Valve ON");     
  // }
  // char t0='0';
  // char t1='1';
  // int payload_status=payloadGet[1] -'0';
  // char payload_status[]=(payloadGet);
  // Serial.println(payload_status[0]);
  // Serial.println(payload_status[1]);
  if(Status.indexOf('0')!=-1)
  {   
    digitalWrite(Valve_pin, HIGH); 
    Serial.println("Valve OFF");
  }
  else if(Status.indexOf('1')!=-1)
  {
    digitalWrite(Valve_pin, LOW);
    Serial.println("Valve ON");     
  }
  Serial.println("----------------Closing Connection----------------");
  http.end();
  Serial.println();
  Serial.println("Please wait 5 seconds for the next connection.");
  Serial.println();
  delay(5000);
}
