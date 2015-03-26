/*=========================================================================
      Libreria para el uso conjunto de los dispositivos HMC5883, ADXL345 
      , PCF8591, MCP9800 y DHT22.
	  Define estructuras y constantes para almacenar valores.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
	#ifndef _SENSOR_H
	#define _SENSOR_H
	#include "Arduino.h"
	#include "Print.h"

/*=========================================================================

  Constantes 

=========================================================================*/
	#define SENSORS_GRAVITY_EARTH (9.80665F) /* Gravedad de la Tierra en m/s^2 */
	#define SENSORS_GRAVITY_STANDARD (SENSORS_GRAVITY_EARTH)
	#define SENSORS_MAGFIELD_EARTH_MAX (60.0F) /*Valor maximo campo magnetico en la superficie de la Tierra */
	#define SENSORS_MAGFIELD_EARTH_MIN (30.0F) /*Valor minimo campo magnetico en la superficie de la Tierra */
	#define SENSORS_DPS_TO_RADS (0.017453293F) /* Conversor de grados a radianes */
	#define SENSORS_GAUSS_TO_MICROTESLA (100) /* Conversor de Gauss a microTesla */

/*=========================================================================

   Vector para almacenar valores de los dispositivos anteriores.

=========================================================================*/
typedef struct {
float x;
float y;
float z;
float t;
float r;
float h;
float l;
float tempC;
float humidity;
float heatIndex;
float tempMCP;
} sensors_vec_t;


/*=========================================================================

   Evento de un sensor 

=========================================================================*/
typedef struct
{
sensors_vec_t acceleration; /* Almacena datos del acelerometro */
sensors_vec_t brujula; /* Almacena datos de la brujula */
sensors_vec_t pcf; /* Almacena datos del conversor ADC/DAC */
sensors_vec_t dht22; /* Almacena datos del DHT */
sensors_vec_t mcp98;	
} sensors_t;

/*=========================================================================

  Clase para establecer los metodos necesarios para hallar las medidas.

=========================================================================*/
class Sensor {
public:
void constructor();
virtual void getEvent(sensors_t*);
private:
};
#endif