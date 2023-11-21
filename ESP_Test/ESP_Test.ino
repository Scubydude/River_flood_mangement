#include "HardwareSerial.h"

String load1 = "Hello";
String load2 = "World";
HardwareSerial nano1(1);
HardwareSerial nano2(2);
void setup() {
  Serial.begin(9600);
  nano1.begin(9600, SERIAL_8N1, 2, 4);
  nano2.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  nano1.write('1');
  nano2.write('1');
  while (nano1.available() && nano2.available())
  {
    load1 = nano1.readString();
    load2 = nano2.readString();
  }
  Serial.println(load1);
  Serial.println(load2);
  delay(10);
}