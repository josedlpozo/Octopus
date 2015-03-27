/*=========================================================================
      Libreria para el uso del dispositivo PCF8591 - Conversor ADC/DAC de 8 bits.
      Conexion con ARDUINO mediante bus I2C.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
    #ifndef __PCF8591_H__
    #define __PCF8591_H__
    #include "Arduino.h"
    #include <Sensor.h>
    #include <Wire.h>

/*=========================================================================

  Direccion I2C del dispositivo

=========================================================================*/
    #define PCF8591_ADDRESS            (0x90 >> 1)         

/*=========================================================================

  Enumerado de registros. 

=========================================================================*/
    
    #define  PCF8591_REGISTER_A0                   0x00
    #define  PCF8591_REGISTER_A1                   0x01
    #define  PCF8591_REGISTER_A2                   0x02
    #define  PCF8591_REGISTER_A3                   0x03
    

/*=========================================================================

  Estructura para almacenar los datos de los sensores durante las medidas.

=========================================================================*/
    typedef struct PCF8591_DATA
    {
        uint8_t sensor_t;
        uint8_t sensor_r;
        uint8_t sensor_h;
        uint8_t sensor_l;
    } Pcf8591_Data;



/*=========================================================================

  Clase para establecer y guardar las medidas.

=========================================================================*/
class PCF8591 : public Sensor
{
  public:
    PCF8591(int32_t sensorID = -1);
  
    void getEvent(sensors_t *sens);

  private:
    Pcf8591_Data    _Data;     
    int32_t         _sensorID;
    
    void write8(byte address, byte reg, byte value);
    byte read8(byte address, byte reg);
    void read(void);
};

#endif