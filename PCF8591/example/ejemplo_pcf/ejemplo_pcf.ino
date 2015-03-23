#include <Wire.h>
#include <Sensor.h>
#include <PCF8591.h>

/* Constructor */
PCF8591 pcf = PCF8591(12345);


void setup(void) 
{
  /* Inicializar conexion serie */
  Serial.begin(9600);
  Serial.println("Ejemplo pcf8591"); Serial.println("");
  
  /* Inicializar sensor */
  if(!pcf.begin())
  {
    /* No se detecta sensor */
    Serial.println("No se detecta el sensor!");
    while(1);
  }
  
}

void loop(void) 
{
  /* Recogemos el evento del sensor */ 
  sensors_t event; 
  pcf.getEvent(&event);
 
  /* Representacion de los resultados */
  Serial.print("Value0: "); Serial.print(event.pcf.t); Serial.print("  ");
  Serial.print("Value1: "); Serial.print(event.pcf.r); Serial.print("  ");
  Serial.print("Value2: "); Serial.print(event.pcf.h); Serial.print("  ");
  Serial.print("Value3: "); Serial.print(event.pcf.l); Serial.print("  ");
  Serial.println();
  
  delay(500);
}
