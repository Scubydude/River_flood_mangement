#include "HardwareSerial.h"

float load1;
float load2;

HardwareSerial nano1(1);
HardwareSerial nano2(2);

void setup() {
  Serial.begin(9600);
  nano1.begin(9600, SERIAL_8N1, 2, 4);
  nano2.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  while (!Serial.available());
  nano1.write(Serial.read());
  while(!nano1.available());
  // load1 = nano1.parseFloat();
  Serial.print(nano1.read());
  Serial.println("--------");
  // // nano2.write('1');
  // while (nano1.available())// && nano2.available())
  // {
  //   load1 = nano1.readString();
  //   // load2 = nano2.readString();
  //   nano1.flush();
  // }
  // Serial.println(load1);
  // // Serial.println(load2);
  // delay(10);
}