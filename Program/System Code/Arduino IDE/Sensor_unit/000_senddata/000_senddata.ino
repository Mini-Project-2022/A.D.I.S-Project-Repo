#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;

#define ON_Board_LED 2

const char* ssid = "G";             // --> wifi name
const char* password = "12345678";  //--> wifi password
int status;

const char *host = "https://domestic-irrigation.000webhostapp.com:80/";
String inString = "";
void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(ON_Board_LED, OUTPUT);
  digitalWrite(ON_Board_LED, HIGH);

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
  pinMode(A0, INPUT);
}

void loop() {
  HTTPClient http;
  String GetAddress, LinkGet, getData, LEDStatResultSend;
  int moisture = int(100.00-((analogRead(A0)/1023.00) * 100.00)) ;               
  if(moisture<40)
  {
    status = 1;
  }
  else
  {
    status = 0;
  }               
  //moisture=45;
  //status=1;
  GetAddress = "SendData.php";
  LinkGet = host + GetAddress;
  getData = "status="+String(status)+"&&moisture="+String(moisture);
  http.begin(wifiClient, LinkGet); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCodeGet = http.POST(getData);
  String payloadGet = http.getString();
  Serial.print(status);
  Serial.print(",");
  Serial.println(moisture);
  Serial.println(payloadGet);
  
  Serial.println("----------------Closing Connection----------------");
  http.end();
  Serial.println();
  Serial.println("Please wait 5 seconds for the next connection.");
  Serial.println();
  delay(5000);
}