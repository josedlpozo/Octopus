/*=========================================================================
      Libreria para el uso del dispositivo ADXL345 - ACELEROMETRO
      Conexion con ARDUINO mediante bus I2C.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
#include "Arduino.h"
#include <limits.h>
#include "ADXL345.h"
#include <Wire.h>

/*=========================================================================

  Escribe 8 bits en el registro especificado.

=========================================================================*/
void ADXL345::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

/*=========================================================================

  Lee 8 bits del registro especificado.

=========================================================================*/
uint8_t ADXL345::readRegister(uint8_t reg) {

    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(ADXL345_ADDRESS, 1);
    return (Wire.read());
}

/*=========================================================================

  Lee 16 bits del registro especificado.

=========================================================================*/
int16_t ADXL345::read16(uint8_t reg) {

    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(ADXL345_ADDRESS, 2);

    uint8_t l = Wire.read();
    uint8_t h = Wire.read();

    return (uint16_t)( h << 8  | l );     
}

/*=========================================================================

  Lectura de la coordenada x. Lee los 16 bits a partir del registro X0.

=========================================================================*/
int16_t ADXL345::getX(void) {
  return read16(ADXL345_REG_DATAX0);
}

/*=========================================================================

  Lectura de la coordenada y. Lee los 16 bits a partir del registro Y0.

=========================================================================*/
int16_t ADXL345::getY(void) {
  return read16(ADXL345_REG_DATAY0);
}

/*=========================================================================

  Lectura de la coordenada z. Lee los 16 bits a partir del registro Z0.

=========================================================================*/
int16_t ADXL345::getZ(void) {
  return read16(ADXL345_REG_DATAZ0);
}

/*=========================================================================

  Constructor de la clase. Recibe como parametro un identificador, y
  especifica el rango de medida del acelerometro.

=========================================================================*/
ADXL345::ADXL345(int32_t sensorID) {
  _sensorID = sensorID;
  _range = ADXL345_RANGE_2_G;
}


/*=========================================================================

  Inicializa el acelerometro y habilita el modo MEASURE.

=========================================================================*/
bool ADXL345::begin() {
  
  
  /* Permite la recepción de medidas */
  writeRegister(ADXL345_REG_POWER_CTL, 0x08);  
    
  return true;
}

/*=========================================================================

  Establece el rango de medida.

=========================================================================*/
void ADXL345::setRange(range_t range)
{
  /* Lee el formato de los datos para mantener los bits */
  uint8_t format = readRegister(ADXL345_REG_DATA_FORMAT);

  /* Actualiza el ancho de banda */
  format &= ~0x0F;
  format |= range;
  
  /* Asegura que el bit de FULL-RES esta activado para el reescalado */
  format |= 0x08;
  
  /* Escribe el formato en el registro de nuevo */
  writeRegister(ADXL345_REG_DATA_FORMAT, format);
  
  /* Guarda el actual rango para evitar llamadas posteriores */
  _range = range;
}

/*=========================================================================

  Devuelve el rango de medida

=========================================================================*/
range_t ADXL345::getRange(void)
{
  /* Lee el formato de datos para mantenerlo. */
  return (range_t)(readRegister(ADXL345_REG_DATA_FORMAT) & 0x03);
}


/*=========================================================================

  Devuelve el evento mas actual. Almacena los valores de x,y,z en sensors_t.

=========================================================================*/
void ADXL345::getEvent(sensors_t *acel) {
  /* Borra datos anteriores */
  memset(acel, 0, sizeof(sensors_t));
  Serial.println(getX());
  acel->acceleration.x = getX() * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
  acel->acceleration.y = getY() * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
  acel->acceleration.z = getZ() * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
}
