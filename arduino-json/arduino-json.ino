#include <ArduinoJson.h>

void cria_json();
void extrai_json(String texto);

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
  if(Serial.available()){
    String texto = Serial.readStringUntil('\n');
    extrai_json(texto);
  }
}

void extrai_json(String json){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& buffer = jsonBuffer.parseObject(json);
  if(!buffer.success()){
    Serial.println("JSON apresenta erros!");
    return ;
  }
  if(buffer.containsKey("lampada")){
    boolean lampada = buffer["lampada"]; 
    Serial.print("Lâmpada: ");
    Serial.println(lampada == true ? "Ligada" : "Desligada");
  }

  if(buffer.containsKey("temperatura")){
    double temperatura = buffer["temperatura"];
    Serial.print("Temperatura : ");
    Serial.println(temperatura);
  }
  
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

