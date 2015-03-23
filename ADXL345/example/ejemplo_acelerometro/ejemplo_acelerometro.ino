#include <Wire.h>
#include <ADXL345.h>

/* Constructor */
ADXL345 accel = ADXL345(12345);

void setup(void) 
{
  /* Inicia conexion serie */
  Serial.begin(9600);
  Serial.println("Eejmplo acelerometro"); Serial.println("");
  
  /* Inicializar el sensor */
  if(!accel.begin())
  {
    /* No detecta acelerometro */
    Serial.println("No hay acelerometro detectado!");
    while(1);
  }

  /* Establece el rango apropiado */
  accel.setRange(ADXL345_RANGE_16_G);
  
  
}

void loop(void) 
{
  /* Recogemos el evento del sensor */ 
  sensors_t event; 
  accel.getEvent(&event);
 
  /* Representacion de los resultados */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(500);
}
