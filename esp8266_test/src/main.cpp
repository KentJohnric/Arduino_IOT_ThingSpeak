#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "MortyMcFly2020";
const char* password = "Valorant2020!";

unsigned long channel = 1278697;

unsigned int led1 = 1;
int d13led = 13;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(d13led, OUTPUT);
  pinMode(d13led, 0);

  Serial.println();
  Serial.print("Connecting to: ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.print("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);
}

void loop() {
  int led_1 = ThingSpeak.readFloatField(channel, led1);

  if(led_1 == 1){
    digitalWrite(d13led, HIGH);
    Serial.println("LED is ON!");
  }
  else{
    digitalWrite(d13led, LOW);
    Serial.println("LED is OFF");
  }
}