#include <Arduino.h>
#include <NewPing.h>

#define TRIGGER_PIN 2 // Pin de trigger del sensor ultrasónico
#define ECHO_PIN 3    // Pin de echo del sensor ultrasónico
#define MOTOR_PIN_1 9 // Pin 1 del motor (control de velocidad)
#define MOTOR_PIN_2 10 // Pin 2 del motor (control de dirección)

NewPing sonar(TRIGGER_PIN, ECHO_PIN);
int motorSpeed = 0;

void setup() {
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  delay(50);
  int distance = sonar.ping_cm(); // Medir la distancia en centímetros

  if (distance > 100) {
    motorSpeed = 0; // Si la distancia es mayor a 100 cm, apagar el motor
  } else if (distance >= 70 && distance <= 99) {
    motorSpeed = 100; // Si la distancia está entre 70 y 99 cm, velocidad lenta
  } else if (distance >= 40 && distance <= 69) {
    motorSpeed = 150; // Si la distancia está entre 40 y 69 cm, velocidad media
  } else if (distance < 40) {
    motorSpeed = 255; // Si la distancia es menor a 40 cm, velocidad máxima
  }

  analogWrite(MOTOR_PIN_1, motorSpeed); // Controlar la velocidad del motor
  digitalWrite(MOTOR_PIN_2, LOW); // Establecer la dirección del motor (en este ejemplo, hacia adelante)

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.print(" cm, Velocidad del motor: ");
  Serial.println(motorSpeed);

  delay(500); // Esperar un poco antes de la próxima lectura
}
