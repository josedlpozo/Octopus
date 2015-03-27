/*=========================================================================
      Libreria para el uso del dispositivo PCF8591 - Conversor ADC/DAC de 8 bits.
      Conexion con ARDUINO mediante bus I2C.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
#include "Arduino.h"
#include <limits.h>
#include <PCF8591.h>
#include <Sensor.h>
#include <Serial.h>
#include <Wire.h>

/*=========================================================================

  Escribe 8 bits en el registro especificado.

=========================================================================*/
void PCF8591::write8(byte address, byte reg, byte value)
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

/*=========================================================================

  Lee 8 bits del registro especificado.

=========================================================================*/
byte PCF8591::read8(byte address, byte reg)
{
  byte value;

  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(address, (byte)2);
  value = Wire.read();
  value = Wire.read();
  

  return value;
}

/*=========================================================================

  Lee los valores de los sensores conectados a las entradas analogicas.
  Lee 8 BYTES.
  Almacena la segunda medida de cada sensor, pues la primera medida
  corresponde al valor anteriormente medido(medida antigua).


=========================================================================*/
void PCF8591::read()
{
  Wire.beginTransmission(PCF8591_ADDRESS);
  Wire.write(PCF8591_REGISTER_A0);
  Serial.println(Wire.endTransmission());

  Wire.requestFrom(PCF8591_ADDRESS ,8);
  
  /* Espera mientras que los datos esten disponibles */
  while (Wire.available() < 8);
    
    
    uint8_t tf = Wire.read();
    uint8_t ts = Wire.read();
    
    uint8_t rf = Wire.read();
    uint8_t rs = Wire.read();
    
    uint8_t hf = Wire.read();
    uint8_t hs = Wire.read();
    
    uint8_t lf = Wire.read();
    uint8_t ls = Wire.read();

  
  _Data.sensor_t = (ts);
  _Data.sensor_r = (rs);
  _Data.sensor_h = (hs);
  _Data.sensor_l = (ls);
  
}

/*=========================================================================

  Constructor de la clase. Recibe como parametro un identificador.

=========================================================================*/
PCF8591::PCF8591(int32_t sensorID) {
  _sensorID = sensorID;
}

/*=========================================================================

  Devuelve el evento mas actual. Almacena los valores devueltos por
   los sensores en sensors_t.

=========================================================================*/
void PCF8591::getEvent(sensors_t *sens) {
  /* Borra datos anteriores */
  memset(sens, 0, sizeof(sensors_t));
  /* Lee nuevos datos. */
    
    sens->pcf.t = read8(PCF8591_ADDRESS,PCF8591_REGISTER_A0);
    
    sens->pcf.r = read8(PCF8591_ADDRESS,PCF8591_REGISTER_A1);
    
    sens->pcf.h = read8(PCF8591_ADDRESS,PCF8591_REGISTER_A2);
    
    sens->pcf.l = read8(PCF8591_ADDRESS,PCF8591_REGISTER_A3);

    return;
}


