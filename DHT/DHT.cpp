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
  #include <limits.h>
  #include "DHT.h"

/*=========================================================================

  Constructor de la clase. Recibe como parametro un identificador.

=========================================================================*/
DHT::DHT(uint8_t pin) {
  _pin = pin;
  _count = 6;
  firstreading = true;
}

/*=========================================================================

  Inicializa el sensor.

=========================================================================*/
void DHT::begin(void) {
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
  _lastreadtime = 0;
}

/*=========================================================================

  Lee temperatura en grados Centigrados del sensor.

=========================================================================*/
float DHT::readTemperature(void) {
  float f;

  if (read()) {
      f = data[2] & 0x7F;
      f *= 256;
      f += data[3];
      f /= 10;
      if (data[2] & 0x80)
	    f *= -1;

      return f;
  }
  return NAN;
}

/*=========================================================================

  Lee porcentaje de humedad relativa en el aire.

=========================================================================*/
float DHT::readHumidity(void) {
  float f;
  if (read()) {
      f = data[0];
      f *= 256;
      f += data[1];
      f /= 10;
      return f;
    }
  return NAN;
}

/*=========================================================================

  Calcula el computeHeatIndex -- Sensación térmica.

=========================================================================*/
float DHT::computeHeatIndex(float tempCelsius, float percentHumidity) {
  float tempFahrenheit = tempCelsius * 9 / 5 + 32;
  return (((-42.379 +
           2.04901523 * tempFahrenheit + 
          10.14333127 * percentHumidity +
          -0.22475541 * tempFahrenheit*percentHumidity +
          -0.00683783 * pow(tempFahrenheit, 2) +
          -0.05481717 * pow(percentHumidity, 2) + 
           0.00122874 * pow(tempFahrenheit, 2) * percentHumidity + 
           0.00085282 * tempFahrenheit*pow(percentHumidity, 2) +
          -0.00000199 * pow(tempFahrenheit, 2) * pow(percentHumidity, 2))-32)*5/9);
}



/*=========================================================================

  Lee datos del sensor.

=========================================================================*/
boolean DHT::read(void) {
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;
  unsigned long currenttime;

  // Comprueba si el sensor ha tomado una medida hace menos de dos segundos
  // y si es asi, devuelve la anterior.
  currenttime = millis();
  if (currenttime < _lastreadtime) {
    _lastreadtime = 0;
  }
  if (!firstreading && ((currenttime - _lastreadtime) < 2000)) {
    return true; 
  }
  firstreading = false;
  _lastreadtime = millis();

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  
  // Activa el pin a nivel ALTO ty espera 250 milisegundos.
  digitalWrite(_pin, HIGH);
  delay(250);

  // Activa el pin a nivel BAJO ty espera 250 milisegundos.
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(20);
  noInterrupts();
  digitalWrite(_pin, HIGH);
  delayMicroseconds(40);
  pinMode(_pin, INPUT);

  // Lee
  for ( i=0; i< MAXTIMINGS; i++) {
    counter = 0;
    while (digitalRead(_pin) == laststate) {
      counter++;
      delayMicroseconds(1);
      if (counter == 255) {
        break;
      }
    }
    laststate = digitalRead(_pin);

    if (counter == 255) break;

    // Ignora las 3 primeras transiciones
    if ((i >= 4) && (i%2 == 0)) {
      // Añade cada bit a almacenamiento de bytes
      data[j/8] <<= 1;
      if (counter > _count)
        data[j/8] |= 1;
      j++;
    }

  }

  interrupts();
  

  // Comprueba que ha leido 40 bits y que el cheksum concuerda.
  if ((j >= 40) && 
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
    return true;
  }
  

  return false;

}

/*=========================================================================

  Devuelve el evento mas actual. Almacena los valores de temperatura,
  humedad y sensación térmica.

=========================================================================*/
void DHT::getEvent(sensors_t *dht) {
  /* Borra datos anteriores */
  memset(dht, 0, sizeof(sensors_t));
  
  dht->dht22.tempC = readTemperature();
  dht->dht22.humidity = readHumidity();
  dht->dht22.heatIndex = computeHeatIndex(dht->dht22.tempC,dht->dht22.humidity);
}
