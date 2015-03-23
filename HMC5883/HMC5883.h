/*=========================================================================
      Libreria para el uso del dispositivo HMC5883 - BRUJULA
      Conexion con ARDUINO mediante bus I2C.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
  #ifndef __HMC5883_H__
  #define __HMC5883_H__
  #include "Arduino.h"
  #include "Sensor.h"
  #include <Wire.h>


/*=========================================================================

  Direccion I2C del dispositivo

=========================================================================*/
  #define HMC5883_ADDRESS_MAG            (0x1E)         // 0011110x

/*=========================================================================

  Definicion de registros

=========================================================================*/
    typedef enum
    {
      HMC5883_REGISTER_MAG_CRA_REG_M             = 0x00,
      HMC5883_REGISTER_MAG_CRB_REG_M             = 0x01,
      HMC5883_REGISTER_MAG_MR_REG_M              = 0x02,
      HMC5883_REGISTER_MAG_OUT_X_H_M             = 0x03,
      HMC5883_REGISTER_MAG_OUT_X_L_M             = 0x04,
      HMC5883_REGISTER_MAG_OUT_Z_H_M             = 0x05,
      HMC5883_REGISTER_MAG_OUT_Z_L_M             = 0x06,
      HMC5883_REGISTER_MAG_OUT_Y_H_M             = 0x07,
      HMC5883_REGISTER_MAG_OUT_Y_L_M             = 0x08,
      HMC5883_REGISTER_MAG_SR_REG_Mg             = 0x09,
      HMC5883_REGISTER_MAG_IRA_REG_M             = 0x0A,
      HMC5883_REGISTER_MAG_IRB_REG_M             = 0x0B,
      HMC5883_REGISTER_MAG_IRC_REG_M             = 0x0C,
      HMC5883_REGISTER_MAG_TEMP_OUT_H_M          = 0x31,
      HMC5883_REGISTER_MAG_TEMP_OUT_L_M          = 0x32
    } hmc5883MagRegisters_t;

/*=========================================================================

  Enumerado con los posibles valores de ganancia

=========================================================================*/
    typedef enum
    {
      HMC5883_MAGGAIN_1_3                        = 0x20,  
      HMC5883_MAGGAIN_1_9                        = 0x40,  
      HMC5883_MAGGAIN_2_5                        = 0x60,  
      HMC5883_MAGGAIN_4_0                        = 0x80,  
      HMC5883_MAGGAIN_4_7                        = 0xA0,  
      HMC5883_MAGGAIN_5_6                        = 0xC0,  
      HMC5883_MAGGAIN_8_1                        = 0xE0   
    } hmc5883MagGain;	

/*=========================================================================

  Estructura para almacenar los datos de x,y,z durante las medidas.

=========================================================================*/
    typedef struct hmc5883MagData_s
    {
        float x;
        float y;
        float z;
      float orientation;
    } hmc5883MagData;

/*=========================================================================

  Constantes 

=========================================================================*/
  #define SENSORS_GRAVITY_EARTH (9.80665F) 
  #define SENSORS_GRAVITY_STANDARD (SENSORS_GRAVITY_EARTH)
  #define SENSORS_GAUSS_TO_MICROTESLA (100) 

/*=========================================================================

  Clase para establecer y guardar las medidas.

=========================================================================*/
class HMC5883 : public Sensor {
  public:
    HMC5883(int32_t sensorID = -1);
  
    bool begin(void);
    void setMagGain(hmc5883MagGain gain);
    void getEvent(sensors_t *bruj);

  private:
    hmc5883MagGain   _magGain;
    hmc5883MagData   _magData;     
    int32_t         _sensorID;
    
    void write8(byte address, byte reg, byte value);
    byte read8(byte address, byte reg);
    void read(void);
};

#endif
