#include <ArduinoJson.h>

void cria_json();

void setup() {
  pinMode(0, OUTPUT);
  Serial.begin(115200);
  delay(2000);
  Serial.println("Ligando Arduino...");
  Serial.println();
  cria_json();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void cria_json(){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& buffer = jsonBuffer.createObject();
  buffer["lampada"] = true;
  buffer["temperatura"] = 25.4;
  buffer.printTo(Serial);
  Serial.println();
  buffer.prettyPrintTo(Serial);
}

