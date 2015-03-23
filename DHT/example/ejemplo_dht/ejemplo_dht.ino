#include <DHT.h>

#define DHTPIN 2     // what pin we're connected to

DHT dht(DHTPIN);


void setup() {
  /* Inicializar la conexion serie */
  Serial.begin(9600); 
  Serial.println("Ejemplo DHT!");
  
  /* Inicializar sensor */
  dht.begin();
}

void loop() {
  /* Espera entre dos medidas */ 
  delay(2000);

  /* Lectura humedad */
  float h = dht.readHumidity();
  /* Lectura temperatura */
  float t = dht.readTemperature();

  
  /* Comprobacion de medidas erroneas */
  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo en la lectura!");
    return;
  }

  /* Calculo de sensacion termica */
  float hi = dht.computeHeatIndex(f, h);
  
  /* Representacion de los resultados */
  Serial.print("Humidity: ");Serial.print(h);Serial.print(" %\t");Serial.print("Temperature: "); Serial.print(t);Serial.print(" *C ");Serial.print("Heat index: ");Serial.print(hi);Serial.println(" *F");
}
