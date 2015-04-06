#include <Wire.h>
#include <ADXL345.h>
#include <DHT.h>
#include <Sensor.h>
#include <PCF8591.h>
#include <HMC5883.h>
#include <VirtualWire.h>

#define DHTPIN 7
DHT dht = DHT(DHTPIN);


ADXL345 acel = ADXL345(12345);
HMC5883 bruj = HMC5883(12345);
PCF8591 pcf = PCF8591(12345);

float acelx, acely, acelz;
float pcft, pcfh, pcfr, pcfl;
float brujx, brujy, brujz, grados;
float dht22h, dht22t, dht22f;


const int led_pin = 11;
const int transmit_pin = 8;
const int receive_pin = 2;
const int transmit_en_pin = 3;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  
  
  if(!acel.begin())
      {
        /* No detecta acelerometro */
        Serial.println("No hay acelerometro detectado!");
        while(1);
      }
   acel.setRange(ADXL345_RANGE_16_G);
   if(!bruj.begin())
      {
        /* No detecta acelerometro */
        Serial.println("No hay acelerometro detectado!");
        while(1);
      }
     // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  dht.begin();
  
}

void loop(){
    sensors_t event;
    acel.getEvent(&event);
    acelx = event.acceleration.x;
    acely = event.acceleration.y;
    acelz = event.acceleration.z;
    Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
    delay(500);
    pcf.getEvent(&event);
    pcft = event.pcf.t;
    pcfh = event.pcf.h;
    pcfr = event.pcf.r;
    pcfl = event.pcf.l;
    Serial.print(event.pcf.t);
    Serial.print(event.pcf.t); Serial.print(" Temperatura"); Serial.println();
    Serial.print(event.pcf.r); Serial.print(" Rocio"); Serial.println();
    Serial.print(event.pcf.h); Serial.print(" Humedad"); Serial.println();
    Serial.print(event.pcf.l); Serial.print(" Luminosidad"); Serial.println();
    delay(500);
    bruj.getEvent(&event);
    brujx = event.brujula.x;
    brujy = event.brujula.y;
    brujz = event.brujula.z;
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
    grados = headingDegrees;
    delay(500);
    dht.getEvent(&event);
    dht22h = event.dht22.humidity;
    dht22t = event.dht22.tempC;
    dht22f = event.dht22.heatIndex;
    Serial.print("Humidity: "); Serial.print(event.dht22.humidity);Serial.println();
    Serial.print("Temperatura: "); Serial.print(event.dht22.tempC);Serial.println();
    Serial.print("HeatIndex: "); Serial.print(event.dht22.heatIndex);Serial.println();
    char msg[10];
    char t[10];
    dtostrf(acelx, 6, 2, t);
    sprintf(msg, "ACX: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(acely, 6, 2, t);
    sprintf(msg, "ACX: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(acelz, 6, 2, t);
    sprintf(msg, "ACX: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(pcft, 6, 2, t);
    sprintf(msg, "TLM35: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(pcfh, 6, 2, t);
    sprintf(msg, "HTIERRA: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(pcfr, 6, 2, t);
    sprintf(msg, "ROCIO: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(pcfl, 6, 2, t);
    sprintf(msg, "LUMI: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(grados, 6, 2, t);
    sprintf(msg, "Grados: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(dht22h, 6, 2, t);
    sprintf(msg, "HAIRE: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(dht22t, 6, 2, t);
    sprintf(msg, "TDHT22: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    dtostrf(dht22f, 6, 2, t);
    sprintf(msg, "STERMICA: %s",t);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(5000);
    delay(10000);
    
}


