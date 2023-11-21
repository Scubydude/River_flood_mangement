#include "HX711.h"
#include "SoftwareSerial.h"
#define LOADCELL_DOUT_PIN 4
#define LOADCELL_SCK_PIN 5

HX711 scale;

const byte rxPin = 2;
const byte txPin = 3;

SoftwareSerial esp32(rxPin, txPin);

float calibration_factor = 89.097160;  //93.377456 for lc1 & 89.097160 for lc2 //Change this by using known weight
float weight;
char weight_f[5];

void setup() {

  Serial.begin(9600);
  esp32.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();  //Reset the scale to 0
  scale.set_scale(calibration_factor);
}

void loop() {
  while (esp32.available()) {
    while (esp32.available()) {
      Serial.print(esp32.read());
      esp32.flush();
      Serial.flush();
    }
    // esp32.write("1: ");  //For Load cell 1
    esp32.write("2: ");  //For Load cell 2
    weight = scale.get_units();
    dtostrf(weight, 3, 1, weight_f);
    esp32.write(weight_f);
    esp32.println();
    esp32.flush();
    Serial.flush();
  }
  esp32.flush();
  Serial.flush();
}
