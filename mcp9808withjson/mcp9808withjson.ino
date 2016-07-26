#include <ArduinoJson.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"

Adafruit_MCP9808 sensor = Adafruit_MCP9808();

void analisaJsonSerial(String json);
void enviaJsonSerial();
void ligaLed(int porta);
void desligaLed(int porta);
void inverteLed(int porta);
void atualizaLed();

int ledState = 0;
int intervaloPisca = 1000;
int ultimoPisca = 0;

void setup() {
  pinMode(0, OUTPUT);
  ligaLed(0);
  Serial.begin(115200);
  delay(2000);
  if(!sensor.begin()){
    Serial.println("Sensor de temperatura não encontrado!");
    while(1);
  }

  sensor.shutdown_wake(0);
  Serial.println("Ligando Arduino...");
  Serial.println();
}

void loop() {
  if(Serial.available()){
    String texto = Serial.readStringUntil('\n');
    analisaJsonSerial(texto);
  }
  atualizaLed();
}

void analisaJsonSerial(String json){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& buffer = jsonBuffer.parseObject(json);
  
  if(!buffer.success()){
    Serial.println("JSON apresenta erros!");
    return ;
  }
  if(buffer.containsKey("status")){
    enviaJsonSerial();
  }
  if(buffer.containsKey("seta_led")){
    String lamp = buffer["seta_led"];
    if(lamp == "desligado"){
      ledState = 0; 
    } else if(lamp == "ligado"){
      ledState = 1;
    } else if(lamp == "piscando"){
      ledState = 2;
    }
  }
  if(buffer.containsKey("pisca_led")){
    intervaloPisca = buffer["pisca_led"];
    ledState = 2;
  }
}

void enviaJsonSerial(){
  String lampada = "";
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& buffer = jsonBuffer.createObject();

  switch(ledState){
    case 0: lampada = "desligado";
            break;
    case 1: lampada = "ligado";
            break;
    case 2: lampada = "piscando";
            break;                
  }

  float temp = sensor.readTempC();
  delay(200);
  buffer["led"] = lampada;
  buffer["temperatura"] = temp;
  buffer.prettyPrintTo(Serial);
  Serial.println();  
}

void ligaLed(int porta){
  digitalWrite(porta, LOW);
}

void desligaLed(int porta){
  digitalWrite(porta, HIGH);
}

void inverteLed(int porta){
  digitalWrite(porta, !digitalRead(porta));
}

void atualizaLed(){
  switch(ledState){
    case 0: desligaLed(0);
            break;
    case 1: ligaLed(0);
            break;
    case 2: if(millis() - ultimoPisca > intervaloPisca){
              ultimoPisca = millis();
              inverteLed(0);              
            }
            break;
  }
}
