#include <ESP8266WiFi.h>
#include "ESPGithubUpdater.h"

ESPGithubUpdater updater("vlastahajek","RLTest");
// Github has anonymous rate limit 60/hours
// In order to access private repos or use higher limit, 1500/hour, user authenticated request 
//ESPGithubUpdater updater("vlastahajek","RLTest"),"<username>","<token>");

void setup() {
  Serial.begin(74880);
  Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin("SSID", "password");
  int i = 30;
  while (WiFi.status() != WL_CONNECTED && i>0) {
    Serial.print(".");
    delay(500);
    --i;
  }
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi failed");
    Serial.println("Restarting");
    delay(3000);  
    ESP.restart();
  }
  Serial.println();
  Serial.print("version 0.1: ");
  Serial.println(updater.checkVersion("0.1"));
  Serial.print("Latest version: ");
  Serial.println(updater.getLatestVersion());
  Serial.print("Latest beta: ");
  String ver = updater.getLatestVersion(true);
  Serial.println(ver);
  updater.runUpdate(ver);
}

void loop() {
   delay(5000);
}