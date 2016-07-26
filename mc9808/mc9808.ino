#include <Wire.h>
#include "Adafruit_MCP9808.h"

Adafruit_MCP9808 sensor = Adafruit_MCP9808();

void mostra_temperatura();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  Serial.println("Ligando Arduino...");
  Serial.println();

  if(!sensor.begin()){
    Serial.println("Sensor não encontrado!");
    while (1);
  }

  sensor.shutdown_wake(0);
  
}

void mostra_temperatura(){
  float temperatura = sensor.readTempC();
  delay(250);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");
}

void loop() {
  // put your main code here, to run repeatedly:
  mostra_temperatura();
  delay(1000);
}
