#include <Arduino.h>

// Definir los pines TRIG y ECHO del sensor ultrasónico
const int trigPin = 13;
const int echoPin = 12;

//SALIDAS LOGICAS
const int pines[3] = {11,10,9}; // A, B, C

long duracion;
int distancia;
int distanciaReal;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

uint8_t aGray(uint8_t num) {
  return num ^ (num >> 1);
}

int validarDistancia(int distancia){
  if(distancia >= 0 && distancia < 10){
    return 0;
  }

  else if(distancia >= 10 && distancia < 20){
    return 1;
  }

  else if(distancia >= 20 && distancia < 30){
    return 2;
  }

  else if(distancia >= 30 && distancia < 40){
    return 3;
  }

  else if(distancia >= 40 && distancia < 50){
    return 4;
  }

  else if(distancia >= 50 && distancia < 60){
    return 5;
  }

  else if(distancia >= 60 && distancia < 70){
    return 6;
  }

  else{
    return 7;
  }
}

String validarLargo(String gray){
  if(gray.length() == 1){
    return "00" + gray;
  }

  else if(gray.length() == 2){
    return "0" + gray;
  }

  else{
    return gray;
  }
}

void generarSalidas(String gray){
  for (int i = 0; i < 3; i++) {
    char num = gray.charAt(i);

    if(num == '0'){
      digitalWrite(pines[i], LOW);
    }
    else{
      digitalWrite(pines[i], HIGH);
    }
  }
}
 
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracion = pulseIn(echoPin, HIGH);
  distanciaReal = duracion * 0.034 / 2;
  distancia = validarDistancia(distanciaReal);

  if(distanciaReal <= 70){
    Serial.print("Distancia: ");
    Serial.print(distanciaReal);
    Serial.println(" cm");
    
    String codigoGray = validarLargo(String(aGray(distancia), BIN));

    Serial.print("GRAY: ");
    Serial.println(codigoGray);

    generarSalidas(codigoGray);
  }
  else{
    Serial.print("---");
  }
  
  delay(500);
}
