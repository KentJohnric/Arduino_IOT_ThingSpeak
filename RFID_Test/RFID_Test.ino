#include <RFID.h>
#include <SPI.h>
#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rf
}

void loop() {
  // put your main code here, to run repeatedly:

}
