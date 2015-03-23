/*=========================================================================
      Libreria para el uso del dispositivo ADXL345 - ACELEROMETRO
      Conexion con ARDUINO mediante bus I2C.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
 #ifndef __ADXL345_H__
 #define __ADXL345_H__

 #include "Arduino.h"
 #include <Sensor.h>
 #include <Wire.h> 

/*=========================================================================

  Direccion I2C del dispositivo

=========================================================================*/
    #define ADXL345_ADDRESS                 (0x53)    


/*=========================================================================

  Definicion de registros

=========================================================================*/
    #define ADXL345_REG_DEVID               (0x00)    // Device ID
    #define ADXL345_REG_THRESH_TAP          (0x1D)    // Tap threshold
    #define ADXL345_REG_OFSX                (0x1E)    // X-axis offset
    #define ADXL345_REG_OFSY                (0x1F)    // Y-axis offset
    #define ADXL345_REG_OFSZ                (0x20)    // Z-axis offset
    #define ADXL345_REG_DUR                 (0x21)    // Tap duration
    #define ADXL345_REG_LATENT              (0x22)    // Tap latency
    #define ADXL345_REG_WINDOW              (0x23)    // Tap window
    #define ADXL345_REG_THRESH_ACT          (0x24)    // Activity threshold
    #define ADXL345_REG_THRESH_INACT        (0x25)    // Inactivity threshold
    #define ADXL345_REG_TIME_INACT          (0x26)    // Inactivity time
    #define ADXL345_REG_ACT_INACT_CTL       (0x27)    // Axis enable control for activity and inactivity detection
    #define ADXL345_REG_THRESH_FF           (0x28)    // Free-fall threshold
    #define ADXL345_REG_TIME_FF             (0x29)    // Free-fall time
    #define ADXL345_REG_TAP_AXES            (0x2A)    // Axis control for single/double tap
    #define ADXL345_REG_ACT_TAP_STATUS      (0x2B)    // Source for single/double tap
    #define ADXL345_REG_BW_RATE             (0x2C)    // Data rate and power mode control
    #define ADXL345_REG_POWER_CTL           (0x2D)    // Power-saving features control
    #define ADXL345_REG_INT_ENABLE          (0x2E)    // Interrupt enable control
    #define ADXL345_REG_INT_MAP             (0x2F)    // Interrupt mapping control
    #define ADXL345_REG_INT_SOURCE          (0x30)    // Source of interrupts
    #define ADXL345_REG_DATA_FORMAT         (0x31)    // Data format control
    #define ADXL345_REG_DATAX0              (0x32)    // X-axis data 0
    #define ADXL345_REG_DATAX1              (0x33)    // X-axis data 1
    #define ADXL345_REG_DATAY0              (0x34)    // Y-axis data 0
    #define ADXL345_REG_DATAY1              (0x35)    // Y-axis data 1
    #define ADXL345_REG_DATAZ0              (0x36)    // Z-axis data 0
    #define ADXL345_REG_DATAZ1              (0x37)    // Z-axis data 1
    #define ADXL345_REG_FIFO_CTL            (0x38)    // FIFO control
    #define ADXL345_REG_FIFO_STATUS         (0x39)    // FIFO status

/*=========================================================================

  Multiplicador para visualizar los valores en m/s^2

=========================================================================*/

    #define ADXL345_MG2G_MULTIPLIER (0.004)

/*=========================================================================

  Enumerado con los posibles rangos de medida

=========================================================================*/
typedef enum
{
  ADXL345_RANGE_16_G          = 0b11,   
  ADXL345_RANGE_8_G           = 0b10,   
  ADXL345_RANGE_4_G           = 0b01,   
  ADXL345_RANGE_2_G           = 0b00    
} range_t;

/*=========================================================================

  Clase para establecer y guardar las medidas.

=========================================================================*/
class ADXL345 : public Sensor {
 public:
  ADXL345(int32_t sensorID = -1);

  bool       begin(void);
  void       setRange(range_t range);
  range_t    getRange(void);
  void       getEvent(sensors_t *acel);

  void       writeRegister(uint8_t reg, uint8_t value);
  uint8_t    readRegister(uint8_t reg);
  int16_t    read16(uint8_t reg);

  int16_t    getX(void), getY(void), getZ(void);
    
 private:
  int32_t _sensorID;
  range_t _range;
};
#endif
