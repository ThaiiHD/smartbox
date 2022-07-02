
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password = "";


#define BOTtoken "" 

#define CHAT_ID ""

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int licht = 0;

void setup() {
  Serial.begin(9600);
  configTime(0, 0, "pool.ntp.org");     
  client.setTrustAnchors(&cert); 
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
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
