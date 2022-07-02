
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "KDH-Oben";
const char* password = "37069675001749482983543253248675239560236747302934";


#define BOTtoken "5579709306:AAE8lXyiQSURHyJf_u1rIXGxlBmQQwJowpEBBUEMDOSBBD" 

#define CHAT_ID "813019446"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int licht = 0;
int LED = 2;

void setup() {
  Serial.begin(9600);
  configTime(0, 0, "pool.ntp.org");     
  client.setTrustAnchors(&cert); 
  pinMode(LED,OUTPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  bot.sendMessage(CHAT_ID, "Briefsensor aktiv", "");
}

void loop() {
 licht = analogRead(A0);
 Serial.print ("Lichtwert: ");  
  Serial.println(licht);  
  delay(1000);     
     
  if(licht > 100){
   bot.sendMessage(CHAT_ID, "Es wurde ein Brief eingeworfen", "");
   delay(60000);
  }
}
