#include "HardwareSerial.h"
#include <Wire.h>
#include "RTClib.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

long timer = 0;

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// const int MPU_addr=0x69;  // I2C address of the MPU-6050

// int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
String load2,load1;
HardwareSerial nano1 (1);
HardwareSerial nano2 (2);
String msg;
String weight;
void setup() {
  Serial.begin(115200);
  #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");
  nano1.begin(9600, SERIAL_8N1, 2, 4);
  nano2.begin(9600, SERIAL_8N1, 16,17);
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
    time_read();
    mpu_read();
   delay(10);
}

void time_read(){
  
  DateTime now = rtc.now();
   Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(200);
}
void mpu_read(){
  mpu.update();

  if(millis() - timer > 1000){ // print data every second
    // Serial.print(F("TEMPERATURE: "));Serial.println(mpu.getTemp());
    Serial.print(F("ACCELERO  X: "));Serial.print(mpu.getAccX());
    Serial.print("\tY: ");Serial.print(mpu.getAccY());
    Serial.print("\tZ: ");Serial.println(mpu.getAccZ());
  
    Serial.print(F("GYRO      X: "));Serial.print(mpu.getGyroX());
    Serial.print("\tY: ");Serial.print(mpu.getGyroY());
    Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
  
    Serial.print(F("ACC ANGLE X: "));Serial.print(mpu.getAccAngleX());
    Serial.print("\tY: ");Serial.println(mpu.getAccAngleY());
    
    Serial.print(F("ANGLE     X: "));Serial.print(mpu.getAngleX());
    Serial.print("\tY: ");Serial.print(mpu.getAngleY());
    Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
    Serial.println(F("=====================================================\n"));
    timer = millis();
  }
  // Wire.begin();
  // byte status = mpu.begin();
// Wire.begin();
//  Wire.beginTransmission(MPU_addr);
//  Wire.write(0x6B);  // PWR_MGMT_1 register
//  Wire.write(0);     // set to zero (wakes up the MPU-6050)
//  Wire.endTransmission(true);
//  Wire.beginTransmission(MPU_addr);
//  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//  Wire.endTransmission(false);
//  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
//  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
//  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//  //Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//  Serial.print("Accelerometer Values: \n");
//  Serial.print("AcX: "); Serial.print(AcX); Serial.print("\nAcY: "); Serial.print(AcY); Serial.print("\nAcZ: "); Serial.print(AcZ);   
//  //Serial.print("\nTemperature: " );  Serial.print(Tmp);
//  Serial.print("\nGyroscope Values: \n");
//  Serial.print("GyX: "); Serial.print(GyX); Serial.print("\nGyY: "); Serial.print(GyY); Serial.print("\nGyZ: "); Serial.print(GyZ);
//  Serial.print("\n");
//  delay(200);
 }