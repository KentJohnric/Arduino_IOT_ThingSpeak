#include <SoftwareSerial.h>
#include <DHT.h>

//Selecting the Type of the DHT from the DHT Library
#define DHTTYPE DHT11

//Define RX and TX pin of the ESP8266
#define RX 2
#define TX 3
#define DHT_pin 5

//DHT fin
DHT dht(DHT_pin, DHTTYPE);

//Esp8266 Wifi Setup and ThinkSpeak API setup
String AP = "MortyMcFly2020"; //Wifi Name
String PASS = "Valorant2020!"; //Wifi Password
String API = "TEYZT9TII939X3CQ"; //The user ThingSpeak Channel API
String HOST = "api.thingspeak.com"; //ThingSpeak API 
String PORT = "80";
int countTrueCommand;
int countTimeCommand;
boolean found = false;
int valSensor = 1;
String field = "field1";
String fieldd = "field2";

//Setting up SoftwareSerial to the esp8266
SoftwareSerial esp8266(RX,TX);

void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

void loop() {
 String getData = "GET /update?api_key="+ API +"&"+ field +"="+ getTemperatureValue() + "&" + fieldd + "=" + getHumidityValue();
 /*String getData = "GET /update?api_key="+ API +"&field1="+getTemperatureValue()+"&field2="+getHumidityValue(); */
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}

String getTemperatureValue(){
  float t = dht.readTemperature();
  if(isnan(t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  return String(t);
}

String getHumidityValue(){
  float h = dht.readHumidity();
  if(isnan(h)){
    Serial.println(F("Failed to read from the DHT sensor!"));
    return;
  }
  return String(h);
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
