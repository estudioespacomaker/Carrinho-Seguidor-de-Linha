#include <Servo.h>

Servo servoEsquerdo;
Servo servoDireito;

void setup() {

  servoDireito.attach(11);   
  servoEsquerdo.attach(10);

}

void loop() {

  // Frente
  Serial.println("Frente");

  servoEsquerdo.write(180);
  servoDireito.write(0);

  delay(3000);

  // Parado
  Serial.println("Parado");

  servoEsquerdo.write(90);
  servoDireito.write(90);

  delay(2000);

  // Ré
  Serial.println("Re");

  servoEsquerdo.write(0);
  servoDireito.write(180);

  delay(3000);

  // Parado
  servoEsquerdo.write(90);
  servoDireito.write(90);

  delay(2000);
}