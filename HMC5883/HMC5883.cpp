/*=========================================================================
      Libreria para el uso del dispositivo HMC5883 - BRUJULA
      Conexion con ARDUINO mediante bus I2C.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
#include "Arduino.h"
#include <Serial.h>
#include <limits.h>
#include "HMC5883.h"
#include "Sensor.h"
#include <Wire.h>

/*=========================================================================

  Constantes para la obtencion de los valores de x,y,z.

=========================================================================*/
static float _hmc5883_Gauss_LSB_XY = 1100.0F;  
static float _hmc5883_Gauss_LSB_Z  = 980.0F;   

/*=========================================================================

  Escribe 8 bits en el registro especificado.

=========================================================================*/
void HMC5883::write8(byte address, byte reg, byte value)
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

/*=========================================================================

  Lee 8 bits del registro especificado.

=========================================================================*/
byte HMC5883::read8(byte address, byte reg)
{
  byte value;

  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(address, (byte)1);
  value = Wire.read();
  Wire.endTransmission();

  return value;
}

/*=========================================================================

  Lee los valores de x,y,z de la brujula.
  Lee 6 BYTES.

=========================================================================*/
void HMC5883::read()
{

  Wire.beginTransmission((byte)HMC5883_ADDRESS_MAG);
  Wire.write(HMC5883_REGISTER_MAG_OUT_X_H_M);

  Wire.endTransmission();
  Wire.requestFrom((byte)HMC5883_ADDRESS_MAG, (byte)6);
  

  while (Wire.available() < 6);


    uint8_t xh = Wire.read();
    uint8_t xl = Wire.read();
    uint8_t zh = Wire.read();
    uint8_t zl = Wire.read();
    uint8_t yh = Wire.read();
    uint8_t yl = Wire.read();

  

  _magData.x = (int16_t)(xh << 8 | xl);
  _magData.y = (int16_t)(yh << 8 | yl);
  _magData.z = (int16_t)(zh << 8 | zl);
  
}

/*=========================================================================

  Constructor de la clase. Recibe como parametro un identificador.

=========================================================================*/
HMC5883::HMC5883(int32_t sensorID) {
  _sensorID = sensorID;
}

/*=========================================================================

  Inicializa la brujula y habilita el modo MEASURE. Establece la ganancia.

=========================================================================*/
bool HMC5883::begin()
{

  write8(HMC5883_ADDRESS_MAG, HMC5883_REGISTER_MAG_MR_REG_M, 0x00);
  
  /* Establece la ganancia */
  setMagGain(HMC5883_MAGGAIN_1_3);
    


  return true;
}

/*=========================================================================

  Establece la ganancia de la brujula

=========================================================================*/
void HMC5883::setMagGain(hmc5883MagGain gain)
{
  write8(HMC5883_ADDRESS_MAG, HMC5883_REGISTER_MAG_CRB_REG_M, (byte)gain);
  
  _magGain = gain;
 
  switch(gain)
  {
    case HMC5883_MAGGAIN_1_3:
      _hmc5883_Gauss_LSB_XY = 1100;
      _hmc5883_Gauss_LSB_Z  = 980;
      break;
    case HMC5883_MAGGAIN_1_9:
      _hmc5883_Gauss_LSB_XY = 855;
      _hmc5883_Gauss_LSB_Z  = 760;
      break;
    case HMC5883_MAGGAIN_2_5:
      _hmc5883_Gauss_LSB_XY = 670;
      _hmc5883_Gauss_LSB_Z  = 600;
      break;
    case HMC5883_MAGGAIN_4_0:
      _hmc5883_Gauss_LSB_XY = 450;
      _hmc5883_Gauss_LSB_Z  = 400;
      break;
    case HMC5883_MAGGAIN_4_7:
      _hmc5883_Gauss_LSB_XY = 400;
      _hmc5883_Gauss_LSB_Z  = 255;
      break;
    case HMC5883_MAGGAIN_5_6:
      _hmc5883_Gauss_LSB_XY = 330;
      _hmc5883_Gauss_LSB_Z  = 295;
      break;
    case HMC5883_MAGGAIN_8_1:
      _hmc5883_Gauss_LSB_XY = 230;
      _hmc5883_Gauss_LSB_Z  = 205;
      break;
  } 
}

/*=========================================================================

  Devuelve el evento mas actual. Almacena los valores de x,y,z en sensors_t.

=========================================================================*/
void HMC5883::getEvent(sensors_t *bruj) {
  /* Borra datos anteriores */
  memset(bruj, 0, sizeof(sensors_t));
  Serial.println("HMC");
  /* Lee nuevos datos. */
  read();
  
  bruj->brujula.x = _magData.x; 
  bruj->brujula.y = _magData.y; 
  bruj->brujula.z = _magData.z; 
}


