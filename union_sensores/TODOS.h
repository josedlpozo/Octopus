/*=========================================================================
      Libreria para el proyecto OCTOPUS.
      Toma de medidas conjuntas de todos los sensores.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
#ifndef __TODOS_H__
#define __TODOS_H__
#include "Arduino.h"
#include "Sensor.h"
#include "PCF8591.h"
#include "HMC5883.h"
#include "ADXL345.h"
#include "DHT.h"
#include <Serial.h>
#include <SD.h>
#include <Wire.h>


/*=========================================================================

  Clase para establecer las medidas.

=========================================================================*/
class TODOS {
  public:

    TODOS(int32_t sensorID = -1);

        HMC5883 hmc;
        PCF8591 pcf;
        ADXL345 adx;
        DHT dht;
    
    void leerDatos(void);
    void iniciarSD(void);

    uint8_t         chipSelect;

  private:
    int32_t         _sensorID;

    
};

#endif