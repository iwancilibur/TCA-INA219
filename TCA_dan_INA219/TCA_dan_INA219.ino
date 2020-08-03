#include <Arduino.h>
#include "TCA9548A.h"
#include <DS3231.h>
#include <Wire.h>
#include <Adafruit_INA219.h> // You will need to download this library
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

//KALIBRASI SUSHU
float kalibrasisuhu=8;

//Inisialisasi OneWire untuk koneksi sensor SUHU dan Pembuatan Variable yang akan dipanggil oleh library dalasTemperature
OneWire oneWire1(2);DallasTemperature sensorSuhu1(&oneWire1);
OneWire oneWire2(3);DallasTemperature sensorSuhu2(&oneWire2);
OneWire oneWire3(4);DallasTemperature sensorSuhu3(&oneWire3);
OneWire oneWire4(5);DallasTemperature sensorSuhu4(&oneWire4);
OneWire oneWire5(6);DallasTemperature sensorSuhu5(&oneWire5);

//Inisialisasi INA219 untuk koneksi sensor ARUS dan Pembuatan Variable yang akan dipanggil oleh library Adafruit_INA219
Adafruit_INA219 sensor1; // Declare and instance of INA219
Adafruit_INA219 sensor2; // Declare and instance of INA219
Adafruit_INA219 sensor3; // Declare and instance of INA219
Adafruit_INA219 sensor4; // Declare and instance of INA219
Adafruit_INA219 sensor5; // Declare and instance of INA219

//Inisialisasi SERVO untuk koneksi Motor SERVO dan Pembuatan Variable yang akan dipanggil oleh library Servo
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

//Inisialisasi RTC untuk koneksi Module WAKTU dan Pembuatan Variable yang akan dipanggil oleh library DS3231
DS3231  rtc(SDA, SCL);
Time waktu;

TCA9548A I2CMux;     // Address can be passed into the constructor

void setup() {
  Serial.begin(115200);             // Define baud rate
  sensorSuhu1.begin();
  sensorSuhu2.begin();
  sensorSuhu3.begin();
  sensorSuhu4.begin();
  sensorSuhu5.begin();
  
  sensor1.begin(); 
  sensor2.begin(); 
  sensor3.begin(); 
  sensor4.begin(); 
  sensor5.begin();
   
  servo1.attach(7);
  servo2.attach(8);
  servo3.attach(9);
  servo4.attach(10);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);

  rtc.begin();
  //rtc.setDOW(MINGGU);           // Set Hari
  //rtc.setTime(21, 02, 00);      // Set waktu JJ:MM:DD (24hr format)
  //rtc.setDate(2, 8, 2020);     // Set tanggal 20 September 2016

  I2CMux.begin(Wire);             // TwoWire isntance can be passed here as 3rd argument
  I2CMux.closeAll();              // Set a base state which we know (also the default state on power on)
}

void loop() 
{
  //AMBIL DATA SUHU
  sensorSuhu1.setWaitForConversion(false);sensorSuhu1.requestTemperatures();float datasuhu1= sensorSuhu1.getTempCByIndex(0)-kalibrasisuhu;
  sensorSuhu2.setWaitForConversion(false);sensorSuhu2.requestTemperatures();float datasuhu2= sensorSuhu2.getTempCByIndex(0)-kalibrasisuhu;
  sensorSuhu3.setWaitForConversion(false);sensorSuhu3.requestTemperatures();float datasuhu3= sensorSuhu3.getTempCByIndex(0)-kalibrasisuhu;
  sensorSuhu4.setWaitForConversion(false);sensorSuhu4.requestTemperatures();float datasuhu4= sensorSuhu4.getTempCByIndex(0)-kalibrasisuhu;
  sensorSuhu5.setWaitForConversion(false);sensorSuhu5.requestTemperatures();float datasuhu5= sensorSuhu5.getTempCByIndex(0)-kalibrasisuhu;
   
  //AMBIL DATA WAKTU 
  waktu = rtc.getTime();
  int dataJam = waktu.hour;     
  int dataMenit = waktu.min;
  int dataDetik = waktu.sec;
  
  //***************************************************//
  I2CMux.openChannel(0);
  float busVoltage1 = 0;
  float current1 = 0; // Measure in milli amps
  float power1 = 0;
  busVoltage1 = sensor1.getBusVoltage_V()*10;
  current1 = sensor1.getCurrent_mA();
  power1 = busVoltage1 * (current1/1000); // Calculate the Power
  I2CMux.closeChannel(0);
  //___________________________________________________//
   
  //***************************************************//
  I2CMux.openChannel(1);
  float busVoltage2 = 0;
  float current2 = 0; // Measure in milli amps
  float power2 = 0;
  busVoltage2 = sensor2.getBusVoltage_V()*10;
  current2 = sensor2.getCurrent_mA();
  power2 = busVoltage2 * (current2/1000); // Calculate the Power
  //___________________________________________________//
   
  //***************************************************//
  I2CMux.openChannel(2);
  float busVoltage3 = 0;
  float current3 = 0; // Measure in milli amps
  float power3 = 0;
  busVoltage3 = sensor3.getBusVoltage_V()*10;
  current3 = sensor3.getCurrent_mA();
  power3 = busVoltage3 * (current3/1000); // Calculate the Power
  I2CMux.closeChannel(2);
  I2CMux.closeChannel(1);
  //___________________________________________________//
   
  //***************************************************//
  I2CMux.openChannel(3);
  float busVoltage4 = 0;
  float current4 = 0; // Measure in milli amps
  float power4 = 0;
  busVoltage4 = sensor4.getBusVoltage_V()*10;
  current4 = sensor4.getCurrent_mA();
  power4 = busVoltage4 * (current4/1000); // Calculate the Power
  I2CMux.closeChannel(3);
  //___________________________________________________//
  
  //***************************************************//
  I2CMux.openChannel(4);
  float busVoltage5 = 0;
  float current5 = 0; // Measure in milli amps
  float power5 = 0;
  busVoltage5 = sensor5.getBusVoltage_V()*10;
  current5 = sensor5.getCurrent_mA();
  power5 = busVoltage5 * (current5/1000); // Calculate the Power
  //I2CMux.closeChannel(4);
  //___________________________________________________//

  //PRINT DATA KE SERIAL
  Serial.print(dataJam);Serial.print(':'); Serial.print(dataMenit); Serial.print(':');Serial.println(dataDetik);
  Serial.print("SENSOR 1 :"); Serial.print("Bus Voltage="); Serial.print(busVoltage1); Serial.print(" V  | "); Serial.print("Current="); Serial.print(current1); Serial.print(" mA  | "); Serial.print("Power="); Serial.print(power1); Serial.print(" W  |  ");Serial.print("Suhu="); Serial.print(datasuhu1); Serial.println(" C"); 
  Serial.print("SENSOR 2 :"); Serial.print("Bus Voltage="); Serial.print(busVoltage2); Serial.print(" V  | "); Serial.print("Current="); Serial.print(current2); Serial.print(" mA  | "); Serial.print("Power="); Serial.print(power2); Serial.print(" W  |  ");Serial.print("Suhu="); Serial.print(datasuhu2); Serial.println(" C"); 
  Serial.print("SENSOR 3 :"); Serial.print("Bus Voltage="); Serial.print(busVoltage3); Serial.print(" V  | "); Serial.print("Current="); Serial.print(current3); Serial.print(" mA  | "); Serial.print("Power="); Serial.print(power3); Serial.print(" W  |  ");Serial.print("Suhu="); Serial.print(datasuhu3); Serial.println(" C"); 
  Serial.print("SENSOR 4 :"); Serial.print("Bus Voltage="); Serial.print(busVoltage4); Serial.print(" V  | "); Serial.print("Current="); Serial.print(current4); Serial.print(" mA  | "); Serial.print("Power="); Serial.print(power4); Serial.print(" W  |  ");Serial.print("Suhu="); Serial.print(datasuhu4); Serial.println(" C"); 
  Serial.print("SENSOR 5 :"); Serial.print("Bus Voltage="); Serial.print(busVoltage5); Serial.print(" V  | "); Serial.print("Current="); Serial.print(current5); Serial.print(" mA  | "); Serial.print("Power="); Serial.print(power5); Serial.print(" W  |  ");Serial.print("Suhu="); Serial.print(datasuhu5); Serial.println(" C"); 
  Serial.println();
  delay(1000);
  /* Code  to interactive with revealed addresses on bus */
  I2CMux.closeAll();

  //MEMBUAT LOGIKA UNTUK PERGERAKAN SERVO BERDASARKAN WAKTU
  if(dataJam==9 && dataMenit==1 ){servo1.write(45);servo2.write(45);servo3.write(45);servo4.write(45);}
  if(dataJam==9 && dataMenit==4 ){servo1.write(46);servo2.write(46);servo3.write(46);servo4.write(46);}
  if(dataJam==9 && dataMenit==8 ){servo1.write(47);servo2.write(47);servo3.write(47);servo4.write(47);}
  if(dataJam==9 && dataMenit==12 ){servo1.write(48);servo2.write(48);servo3.write(48);servo4.write(48);}
  if(dataJam==9 && dataMenit==16 ){servo1.write(49);servo2.write(49);servo3.write(49);servo4.write(49);}
  if(dataJam==9 && dataMenit==20){servo1.write(50);servo2.write(50);servo3.write(50);servo4.write(50);}
  if(dataJam==9 && dataMenit==24 ){servo1.write(51);servo2.write(51);servo3.write(51);servo4.write(51);}
  
}
