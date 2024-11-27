#include <Wire.h>
#include <INA226_WE.h>
#define I2C_D_PANEL  0x40
#define I2C_D_BAT_BU 0x40
#define I2C_D_BAT_1  0x40
#define I2C_D_BAT_2  0x40

INA226_WE Solar = INA226_WE(I2C_D_PANEL);
INA226_WE Batbu = INA226_WE(I2C_D_BAT_BU);
INA226_WE Bat1  = INA226_WE(I2C_D_BAT_1);
INA226_WE Bat2  = INA226_WE(I2C_D_BAT_2);
float VSolar = 0, ISolar = 0, VBatbu = 0, IBatbu = 0, VBat1 = 0, IBat1 = 0, VBat2 = 0, IBat2 = 0;

void setup(){
  Serial.begin(9600);
  while (!Serial); // wait until serial comes up on Arduino Leonardo or MKR WiFi 1010
  Wire.begin();
  Solar.init();
  Batbu.init();
  Bat1.init();
  Bat2.init();

  /* Set conversion time in microseconds
     One set of shunt and bus voltage conversion will take:
     number of samples to be averaged x conversion time x 2

       Mode *         * conversion time
     CONV_TIME_140          140 µs
     CONV_TIME_204          204 µs
     CONV_TIME_332          332 µs
     CONV_TIME_588          588 µs
     CONV_TIME_1100         1.1 ms (default)
     CONV_TIME_2116       2.116 ms
     CONV_TIME_4156       4.156 ms
     CONV_TIME_8244       8.244 ms  */

  Solar.setConversionTime(CONV_TIME_1100); //choose conversion time and uncomment for change of default
  Batbu.setConversionTime(CONV_TIME_1100);
  Bat1.setConversionTime(CONV_TIME_1100);
  Bat2.setConversionTime(CONV_TIME_1100);
  /* Set measure mode
    POWER_DOWN - INA226 switched off
    TRIGGERED  - measurement on demand
    CONTINUOUS  - continuous measurements (default)*/

  //ina226.setMeasureMode(CONTINUOUS); // choose mode and uncomment for change of default

  /* Set Resistor and Current Range
     if resistor is 5.0 mOhm, current range is up to 10.0 A
     default is 100 mOhm and about 1.3 A*/
  
  Solar.setResistorRange(0.1, 10); //Esto es para medir la corriente
  Batbu.setResistorRange(0.1, 10);
  Bat1.setResistorRange(0.1, 10);
  Bat2.setResistorRange(0.1, 10);
  
  
  /* If the current values delivered by the INA226 differ by a constant factor
     from values obtained with calibrated equipment you can define a correction factor.
     Correction factor = current delivered from calibrated equipment / current delivered by INA226*/
  /*
  Solar.setCorrectionFactor(0.95);
  Batbu.setCorrectionFactor(0.95);
  Bat1.setCorrectionFactor(0.95);
  Bat2.setCorrectionFactor(0.95);
  */
  Solar.waitUntilConversionCompleted(); //if you comment this line the first data might be zero
  Batbu.waitUntilConversionCompleted(); 
  Bat1.waitUntilConversionCompleted(); 
  Bat2.waitUntilConversionCompleted(); 
}

void loop()
{
  Solar.readAndClearFlags();
  Batbu.readAndClearFlags();
  Bat1.readAndClearFlags();
  Bat2.readAndClearFlags();
  //Nota el INA SOLO da valores V>0 Voltios
  VSolar = Solar.getBusVoltage_V()+(Solar.getShuntVoltage_mV()/100); 
  ISolar = Solar.getCurrent_mA(); 
  VBatbu = Batbu.getBusVoltage_V()+(Batbu.getShuntVoltage_mV()/100); 
  IBatbu = Batbu.getCurrent_mA();
  VBat1  = Bat1.getBusVoltage_V()+(Bat1.getShuntVoltage_mV()/100);
  IBat1  = Bat1.getCurrent_mA(); 
  VBat2  = Bat2.getBusVoltage_V()+(Bat2.getShuntVoltage_mV()/100);
  IBat2  = Bat2.getCurrent_mA();
  
  Serial.print("VSolar [V]: "); Serial.println(VSolar);
  Serial.print("ISolar [mA]: "); Serial.println(ISolar);
  Serial.print("VBatbu [V]: "); Serial.println(VBatbu);
  Serial.print("IBatbu [mA]: "); Serial.println(IBatbu);
  Serial.print("VBat1  [V]: "); Serial.println(VBat1);
  Serial.print("IBat1  [mA]: "); Serial.println(IBat1);
  Serial.print("VBat2  [V]: "); Serial.println(VBat2);
  Serial.print("IBat2  [mA]: "); Serial.println(IBat2);
  
  Serial.println();

  delay(3000);
}
