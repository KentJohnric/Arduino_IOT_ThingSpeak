#include <DHT.h>
#include <SoftwareSerial.h> //for the esp8266
//Define RX and TX for the Esp8266
#define TX 2
#define RX 3
//Define DHT11 signal pin
#define DHT_pin 11
//name DHT for calling
DHT dht;

//Varaibles for the esp8266 to connect to the Wifi and Thingspeak
String AP = "MortyMcFly2020";
String PASS = "Valorant2020!";
String API = "TEYZT9TII939X3CQ";
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand;
boolean found = false;
int valSensor = 1;

SoftwareSerial esp8266(RX,TX);

void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  dht.setup(11);
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\""+AP+"\",\""+PASS+"\"",20,"OK");
}

void loop() {
  String getData = "GET /update?api_key="+API+"&field1="+getTemperatureValue()+"&field2="+getHumidityValue();
  sendCommand("AT+CIPMUX=1",5,"OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
  sendCommand("AT+CIPSEND=0," +String(getData.length()+4), 4, ">");
  esp8266.println(getData);
  delay(1500);
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");
}

void sendCommand(String command, int maxTime, char readReplay[]){
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1)){
    esp8266.println(command);
    if(esp8266.find(readReplay)){
      found = true;
      break;
    }
    countTimeCommand++;
  }
  if(found == true){
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  if(found == false){
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  found = false;
}

String getTemperatureValue(){
  float temperature = dht.getTemperature();
  Serial.print("Temperature(C) = ");
  Serial.println(temperature);
  return String(temperature);
}

String getHumidityValue(){
  float humidity = dht.getHumidity();
  Serial.print("Humidity in % = ");
  Serial.println(humidity);
  return String(humidity);
}
