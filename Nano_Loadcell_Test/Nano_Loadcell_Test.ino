#include "HX711.h"
#define LOADCELL_DOUT_PIN 4
#define LOADCELL_SCK_PIN 5

HX711 scale;

float calibration_factor = 89.097160;  //Change this by using known weight
float weight;
long int mili = 0;
char weight_f[5];

void setup() {

  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();  //Reset the scale to 0
  scale.set_scale(calibration_factor);
  mili = millis();
}

void loop() {
  weight = scale.get_units();
  mili = millis() - mili;
  Serial.print(mili);
  Serial.print(" ");
  Serial.println(weight);
  mili = millis();
}
