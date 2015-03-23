#include <Wire.h>
#include <Sensor.h>
#include <HMC5883.h>

/* Constructor */
HMC5883 bruj = HMC5883(12345);


void setup(void) 
{
  /* Inicia conexion serie */
  Serial.begin(9600);
  Serial.println("Ejemplo brujula"); Serial.println("");
  
  /* Inicializar el sensor */
  if(!bruj.begin())
  {
     /* No detecta la brujula */
    Serial.println("No se ha detectado brujula!");
    while(1);
  }
  

}

void loop(void) 
{
  /* Recogemos el evento del sensor */ 
  sensors_t event; 
  bruj.getEvent(&event);
 
  /* Representacion de los resultados */
  Serial.print("X: "); Serial.print(event.brujula.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.brujula.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.brujula.z); Serial.print("  ");Serial.println("uT");

  /* Calculo del angulo con respecto al norte */
  float angulo = atan2(event.magnetic.y, event.magnetic.x);
  
  
  
  /* Angulo entre 0 y 2*PI */
  if(angulo < 0)
    angulo += 2*PI;
    

  if(angulo > 2*PI)
    angulo -= 2*PI;
   
  /* Conversion de radianes a grados */ 
  float anguloGrados = angulo * 180/PI; 
  
  Serial.print("Grados: "); Serial.println(anguloGrados);
  
  delay(500);
}
