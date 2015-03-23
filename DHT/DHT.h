/*=========================================================================
      Libreria para el uso del dispositivo DHT22 - Sensor temperatura 
      y humedad relativa.

      Conexion con ARDUINO mediante pin DIGITAL.

      Diseño basado en libreria diseñada por ADAFRUIT.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
  #ifndef DHT_H
  #define DHT_H
  #include "Arduino.h"
  #include <Sensor.h>

  #define MAXTIMINGS 85

/*=========================================================================

  Clase para establecer y guardar las medidas.

=========================================================================*/
class DHT : public Sensor {
 private:
  uint8_t data[6];
  uint8_t _pin, _count;
  unsigned long _lastreadtime;
  boolean firstreading;

 public:
  DHT(uint8_t pin = 4);
  void begin(void);
  float readTemperature(void);
  float convertCtoF(float);
  float computeHeatIndex(float tempCelsius, float percentHumidity);
  float readHumidity(void);
  boolean read(void);
  void getEvent(sensors_t *dht);
};
#endif
