/*=========================================================================
      Libreria para el proyecto OCTOPUS.
      Toma de medidas conjuntas de todos los sensores.
      
      Diseño por José María del Pozo Alonso, Fernando Pérez Fernández
      y Santiago Pérez Peña.

=========================================================================*/

/*=========================================================================

  Inclusion de libraries necesarias.

=========================================================================*/
#include "Arduino.h"
#include <Serial.h>
#include <SD.h>
#include <Wire.h>
#include "TODOS.h"
#include "Sensor.h"
#include "PCF8591.h"
#include "HMC5883.h"
#include "ADXL345.h"
#include "DHT.h"

/*=========================================================================

  Constructor de la clase.

=========================================================================*/
TODOS::TODOS(int32_t sensorID) {
  Serial.begin(9600);
  _sensorID = sensorID;
  
  iniciarSD();
  iniciarSensores();
  leerDatos();
}

/*=========================================================================

  Lee datos de los sensores.

=========================================================================*/
void TODOS::leerDatos(void){
  DHT dht = DHT((uint8_t)4);
  HMC5883 hmc = HMC5883(12345);
  PCF8591 pcf = PCF8591(12345);
  ADXL345 adx = ADXL345(12345);
  sensors_t event;
  while(1){
    adx.getEvent(&event);
    Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
    delay(500);
    pcf.getEvent(&event);
    Serial.print(event.pcf.t);
    Serial.print(" Temperatura");Serial.print(event.pcf.t); Serial.print(" Temperatura"); Serial.println();
    Serial.print(event.pcf.r); Serial.print(" Rocio"); Serial.println();
    Serial.print(event.pcf.h); Serial.print(" Humedad"); Serial.println();
    Serial.print(event.pcf.l); Serial.print(" Luminosidad"); Serial.println();
    delay(500);
    hmc.getEvent(&event);
    Serial.print("X: "); Serial.print(event.brujula.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.brujula.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.brujula.z); Serial.print("  ");Serial.println();
    float heading = atan2(event.brujula.y, event.brujula.x);
    if(heading < 0)
      heading += 2*PI;
    if(heading > 2*PI)
      heading -= 2*PI;
    float headingDegrees = heading * 180/PI; 
    Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
    delay(500);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Fallo leyendo del sensor.");
      return;
    }
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.print(" *C ");
    delay(500);
    dht.getEvent(&event);
    Serial.print("Humidity: "); Serial.print(event.dht22.humidity);Serial.println();
    Serial.print("Temperatura: "); Serial.print(event.dht22.tempC);Serial.println();
    Serial.print("HeatIndex: "); Serial.print(event.dht22.heatIndex);Serial.println();
    File dataFile = SD.open("sensores.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.print(event.pcf.t);
      dataFile.print(";");
      dataFile.print(event.pcf.r);
      dataFile.print(";");
      dataFile.print(event.pcf.h);
      dataFile.print(";");
      dataFile.print(event.pcf.l);
      dataFile.print(";");
      dataFile.print(event.brujula.x);
      dataFile.print(";");
      dataFile.print(event.brujula.y);
      dataFile.print(";");
      dataFile.print(event.brujula.z);
      dataFile.print(";");
      dataFile.print(headingDegrees);
      dataFile.print(";");
      dataFile.print(event.acceleration.x);
      dataFile.print(";");
      dataFile.print(event.acceleration.y);
      dataFile.print(";");
      dataFile.print(event.acceleration.z);
      dataFile.print(";");
      dataFile.print(event.dht22.humidity);
      dataFile.print(";");
      dataFile.print(event.dht22.tempC);
      dataFile.print(";");
      dataFile.print(event.dht22.heatIndex);
      dataFile.println();
      dataFile.close();
       
      // Avisamos de que se ha podido escribir correctamente.
      Serial.println("Impresion correcta");
       
    // Si no pudimos escribir en el fichero avisamos por el puerto serie.
    }else{
      Serial.println("Error al escribir");
    }
    }
   }
}

/*=========================================================================

  Inicializa sensores para tomar medidas.

=========================================================================*/
void TODOS::iniciarSensores(void){
  if(!adx.begin())
  {
    /* No detecta acelerometro */
    Serial.println("No hay acelerometro detectado!");
    while(1);
  }
  if(!hmc.begin())
  {
    /* No detecta acelerometro */
    Serial.println("No hay acelerometro detectado!");
    while(1);
  }
  dht.begin();
}

/*=========================================================================

  Inicializa el SD Shield.

=========================================================================*/
void TODOS::iniciarSD(void){
  if(!SD.begin(4)){
    Serial.println("Error al leer la tarjeta.");
    return;
  }
  Serial.println("Inicio SD correcto.");
}
