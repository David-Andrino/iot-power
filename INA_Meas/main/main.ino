#include <Wire.h>
#include <INA226_WE.h>
//Direcciones I2C
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
  while (!Serial);
  Wire.begin();
  Solar.init();
  Batbu.init();
  Bat1.init();
  Bat2.init();
  //T_medida=Promediado_Numero_medidas*T_Conversion*2

  /* Tiempo de conversión 
     CONV_TIME_140          140 µs
     CONV_TIME_204          204 µs
     CONV_TIME_332          332 µs
     CONV_TIME_588          588 µs
     CONV_TIME_1100         1.1 ms (Por defecto)
     CONV_TIME_2116       2.116 ms
     CONV_TIME_4156       4.156 ms
     CONV_TIME_8244       8.244 ms  
  */
  Solar.setConversionTime(CONV_TIME_1100);
  Batbu.setConversionTime(CONV_TIME_1100);
  Bat1.setConversionTime(CONV_TIME_1100);
  Bat2.setConversionTime(CONV_TIME_1100);
  /*Modos de medida:
    POWER_DOWN - Permite configurar el sistema en bajo consumo manteniendo la configuración
               - El consumo se reduce de 0.35mA (Activo) a 2.3 uA (Bajo consumo) 
    TRIGGERED  - Medidas a petición
    CONTINUOUS - Medidas continuas
  */

  Solar.setMeasureMode(POWER_DOWN);
  Batbu.setMeasureMode(POWER_DOWN);
  Bat1.setMeasureMode(POWER_DOWN);
  Bat2.setMeasureMode(POWER_DOWN);

  /* Indicación de la resistencia se SHUNT y el rango de corrientes usados
      .setResistorRange(R_SHUNT, I);
  */
  
  Solar.setResistorRange(0.1, 10);//Cambiar resistencia si usamos otra, esta es para conexión directa
  Batbu.setResistorRange(0.1, 10);
  Bat1.setResistorRange(0.1, 10);
  Bat2.setResistorRange(0.1, 10);
  
  
  /* Si las medidas tienen un error debido al equipo por un factor constante se puede indicar:
     Factor_Correccion = I_Equipo/I_INA
  */

  /*
  Solar.setCorrectionFactor(0.95);
  Batbu.setCorrectionFactor(0.95);
  Bat1.setCorrectionFactor(0.95);
  Bat2.setCorrectionFactor(0.95);
  */

  //Comentar si estamos utilizando el modo de TRIGGERED
  //Ya que se necesita esperar la conversión en los otros no hace falta.
  
  Solar.waitUntilConversionCompleted();
  Batbu.waitUntilConversionCompleted(); 
  Bat1.waitUntilConversionCompleted(); 
  Bat2.waitUntilConversionCompleted(); 
  
}

void loop(){

  //Tomamos las medidas

  Solar.readAndClearFlags();
  VSolar = Solar.getBusVoltage_V()+(Solar.getShuntVoltage_mV()/100); 
  ISolar = Solar.getCurrent_mA(); 

  Batbu.readAndClearFlags();
  VBatbu = Batbu.getBusVoltage_V()+(Batbu.getShuntVoltage_mV()/100); 
  IBatbu = Batbu.getCurrent_mA();
    
  Bat1.readAndClearFlags();
  VBat1  = Bat1.getBusVoltage_V()+(Bat1.getShuntVoltage_mV()/100);
  IBat1  = Bat1.getCurrent_mA(); 
  
  Bat2.readAndClearFlags();
  VBat2  = Bat2.getBusVoltage_V()+(Bat2.getShuntVoltage_mV()/100);
  IBat2  = Bat2.getCurrent_mA();

  //Ponemos los INA a bajo consumo

  Solar.powerDown();
  Batbu.powerDown(); 
  Bat1.powerDown(); 
  Bat2.powerDown();  

  Serial.print("VSolar [V]: "); Serial.println(VSolar);
  Serial.print("ISolar [mA]: "); Serial.println(ISolar);
  Serial.print("VBatbu [V]: "); Serial.println(VBatbu);
  Serial.print("IBatbu [mA]: "); Serial.println(IBatbu);
  Serial.print("VBat1  [V]: "); Serial.println(VBat1);
  Serial.print("IBat1  [mA]: "); Serial.println(IBat1);
  Serial.print("VBat2  [V]: "); Serial.println(VBat2);
  Serial.print("IBat2  [mA]: "); Serial.println(IBat2);

  //Hacemos una espera de 5s y volvemos a tomar meidas:
  Serial.println("Espera 5s");
  for(int i=0; i<5; i++){
    Serial.print(".");
    delay(1000);
  }
  //Comentar para que al terminar las medidas quede a la espera hasta que queramos.
  despertar_INAs();

}

void despertar_INAs(){
  //Despertamos los INA de nuevo 
  Solar.powerUp();
  Batbu.powerUp(); 
  Bat1.powerUp(); 
  Bat2.powerUp();   
}
