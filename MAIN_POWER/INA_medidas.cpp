//! Clase INA_medidas. Engargada de configurar y solicitar medidas al los INAs del circuito.

#include "INA_medidas.hpp"

// INA226 instances
INA226_WE Solar(I2C_D_PANEL);
INA226_WE Batbu(I2C_D_BAT_BU);
INA226_WE Bat1(I2C_D_BAT_1);
INA226_WE Bat2(I2C_D_BAT_2);

//! Booleano.
/*! Indica si se ha realizado la configuración inicial de los sensores*/
bool fist_config=false;

void setupINA226Sensors();
void reconfig_INAs();
void powerDownINA226();
void powerUpINA226();

/**************************************************************************//**
 * Configuración inicial de los sensores.
 *
 * Tras un reset se inician los sensores para ser modificados, estableciendose los parámetros:
 *  -Tiempo de conversión: Entre 140 us y 8.244 ms.
 *  -Modo de medida: POWER_DOWN (Sistema apagado), TRIGGERED (medidas a petición) o CONTINUOUS (medidas constantes).
 *  -Valor de la resistencia se SHUNT. 
 *  -Rango de corrientes.
 *  -Factor de correción.
 ******************************************************************************/
void setupINA226Sensors() {
    Wire.begin();
    //Inicialización de todos los INA antes de su configuración.
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
      POWER_DOWN - Permite configurar el sistema (es decir, mantiene apagado el sensor).
                 - Si se declara inicialmente en este modo no se permite su configuración.
                 - Además, el consumo se reduce de ~0.35mA (Activo) a ~2.3 uA (Bajo consumo) cuando está en este estado. 
      TRIGGERED  - Medidas a petición
      CONTINUOUS - Medidas continuas
    */
    Solar.setMeasureMode(CONTINUOUS);
    Batbu.setMeasureMode(CONTINUOUS);
    Bat1.setMeasureMode(CONTINUOUS);
    Bat2.setMeasureMode(CONTINUOUS);
    
    /* Indicación de la resistencia se SHUNT y el rango de corrientes usados
        .setResistorRange(R_SHUNT, I);
    */
    Solar.setResistorRange(0.1, 10);
    Batbu.setResistorRange(0.1, 10);
    Bat1.setResistorRange(0.1, 10);
    Bat2.setResistorRange(0.1, 10);
    
    /* Si las medidas tienen un error debido al equipo por un factor constante se puede indicar:
       Factor_Correccion = I_Equipo/I_INA
    */
   
    Solar.setCorrectionFactor(1.0469);
    Batbu.setCorrectionFactor(1.0419);
    Bat1.setCorrectionFactor(0.9650);
    Bat2.setCorrectionFactor(0.9624);
    
    Solar.waitUntilConversionCompleted();
    Batbu.waitUntilConversionCompleted();
    Bat1.waitUntilConversionCompleted();
    Bat2.waitUntilConversionCompleted();
}

/**************************************************************************//**
 * Reconfiguración de los sensores.
 *
 * Al desperta a los sensores, se reinician con la configuración por defecto.
 * Por ello es necesario reconfigurarlos al volver a tomar medidas.
 ******************************************************************************/

void reconfig_INAs(){
    Solar.setConversionTime(CONV_TIME_1100);Batbu.setConversionTime(CONV_TIME_1100);
    Bat1.setConversionTime(CONV_TIME_1100);Bat2.setConversionTime(CONV_TIME_1100);

    Solar.setMeasureMode(CONTINUOUS);Batbu.setMeasureMode(CONTINUOUS);
    Bat1.setMeasureMode(CONTINUOUS);Bat2.setMeasureMode(CONTINUOUS);

    Solar.setResistorRange(0.1, 10);Batbu.setResistorRange(0.1, 10);
    Bat1.setResistorRange(0.1, 10);Bat2.setResistorRange(0.1, 10);

    Solar.waitUntilConversionCompleted();Batbu.waitUntilConversionCompleted();
    Bat1.waitUntilConversionCompleted();Bat2.waitUntilConversionCompleted();  
}

/**************************************************************************//**
 * Realiza una medida de todos los sensores.
 *
 *Inicialmente se verifica si se ha realizado la configuración inicial de los INAs.
 *  -Si se ha realizado, se despiertan y reconfiguran
 *  -En caso contrario se realiza una configuración inicial antes de la captación de datos.
 *Se realiza 1 medida que es almacenada en la estrucutra de datos.
 *Y finalmente se ponen a bajo consumo los INA.
 * @param telemetry Puntero a la estructura de datos que contiene las medidas de tensión y corriente de las baterias y panel solar.
 ******************************************************************************/

void measureINA226(telemetry_t *telemetry) {
    // Panel Solar
    if(fist_config==false){
      setupINA226Sensors();
      fist_config=true;
    }else{
      powerUpINA226();  
    }
    
    Solar.readAndClearFlags();
    telemetry->VSolar = Solar.getBusVoltage_V() + (Solar.getShuntVoltage_mV() / 100);
    telemetry->ISolar = Solar.getCurrent_mA();

    // Batería Backup
    Batbu.readAndClearFlags();
    telemetry->VBatbu = Batbu.getBusVoltage_V() + (Batbu.getShuntVoltage_mV() / 100);
    telemetry->IBatbu = -Batbu.getCurrent_mA();

    // Batería 1
    Bat1.readAndClearFlags();
    telemetry->VBat1 = Bat1.getBusVoltage_V() + (Bat1.getShuntVoltage_mV() / 100);
    telemetry->IBat1 = -Bat1.getCurrent_mA();

    // Batería 2
    Bat2.readAndClearFlags();
    telemetry->VBat2 = Bat2.getBusVoltage_V() + (Bat2.getShuntVoltage_mV() / 100);
    telemetry->IBat2 = Bat2.getCurrent_mA();
    powerDownINA226();
}

/**************************************************************************//**
 * Pone en modo de bajo consumo a los INA.
 *
 * Tras una medida no es necesario que se mantengan activos los sensores por lo que es necesario ponerlos a bajo consumo.
 ******************************************************************************/

void powerDownINA226() {
    Solar.powerDown();
    Batbu.powerDown();
    Bat1.powerDown();
    Bat2.powerDown();
}

/**************************************************************************//**
 * Despierta a los INA del bajo consumo.
 *
 * Al desperta a los sensores, se reinician con la configuración por defecto.
 * Por ello es necesario reconfigurarlos al volver a tomar medidas.
 ******************************************************************************/

void powerUpINA226() {
    Solar.powerUp();
    Batbu.powerUp();
    Bat1.powerUp();
    Bat2.powerUp();
    reconfig_INAs();
}
