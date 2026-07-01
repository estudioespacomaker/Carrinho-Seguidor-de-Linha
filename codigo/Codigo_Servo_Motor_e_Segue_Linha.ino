#include <Servo.h>

Servo MOTOR_DIREITA;
Servo MOTOR_ESQUERDA;

#define SENSOR_ESQUERDA 7
#define SENSOR_DIREITA 6

void setup() {

  MOTOR_DIREITA.attach(11);
  MOTOR_ESQUERDA.attach(10);

  pinMode(SENSOR_ESQUERDA, INPUT);
  pinMode(SENSOR_DIREITA, INPUT);

  Serial.begin(9600);
}

void loop() {

  bool sensorEsquerda = digitalRead(SENSOR_ESQUERDA);
  bool sensorDireita = digitalRead(SENSOR_DIREITA);

  Serial.print("E:");
  Serial.print(sensorEsquerda);
  Serial.print(" D:");
  Serial.println(sensorDireita);

  // Branco Branco -> frente
  if (sensorEsquerda == 0 && sensorDireita == 0) {

    MOTOR_ESQUERDA.write(180);
    MOTOR_DIREITA.write(0);

  }

  // Preto Branco -> virar para esquerda
  else if (sensorEsquerda == 1 && sensorDireita == 0) {

    MOTOR_ESQUERDA.write(90);
    MOTOR_DIREITA.write(0);

  }

  // Branco Preto -> virar para direita
  else if (sensorEsquerda == 0 && sensorDireita == 1) {

    MOTOR_ESQUERDA.write(180);
    MOTOR_DIREITA.write(90);

  }

  // Preto Preto
  else {

    MOTOR_ESQUERDA.write(90);
    MOTOR_DIREITA.write(90);

  }
}