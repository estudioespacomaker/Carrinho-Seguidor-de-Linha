/*
===========================================================
 PROJETO: Carrinho Seguidor de Linha com Sensor Ultrassônico
 AUTOR: Espaço Maker
 BLOG: https://www.espacomaker.online/
 GITHUB: https://github.com/estudioespacomaker
 YOUTUBE: https://www.youtube.com/@estudioespacomaker
 INSTAGRAM: https://www.instagram.com/estudioespacomaker

 DESCRIÇÃO:
 Este projeto demonstra como construir um carrinho seguidor
 de linha utilizando:

 - Arduino
 - 2 Servos MG996R (Rotação Contínua)
 - 2 Sensores Seguidores de Linha TCRT5000
 - 1 Sensor Ultrassônico HC-SR04

 FUNCIONAMENTO:

 ✔ Segue uma linha utilizando dois sensores TCRT5000.
 ✔ Detecta obstáculos utilizando o HC-SR04.
 ✔ Para automaticamente quando um obstáculo estiver
   a menos de 20 centímetros.

===========================================================
*/

#include <Servo.h>

//==========================================================
// Criação dos objetos Servo
//==========================================================
Servo MOTOR_DIREITA;
Servo MOTOR_ESQUERDA;

//==========================================================
// Definição dos pinos dos sensores seguidores de linha
//==========================================================
#define SENSOR_ESQUERDA 7
#define SENSOR_DIREITA 6

//==========================================================
// Definição dos pinos do Sensor Ultrassônico HC-SR04
//==========================================================
#define TRIG 12
#define ECHO 13

//==========================================================
// Distância mínima para parar o robô
//==========================================================
#define DISTANCIA_MINIMA 20

//==========================================================
// Variáveis globais
//==========================================================
bool sensorEsquerda;
bool sensorDireita;

long duracao;
float distancia;

//==========================================================
// SETUP
//==========================================================
void setup() {

  // Liga os servos às portas PWM
  MOTOR_DIREITA.attach(11);
  MOTOR_ESQUERDA.attach(10);

  // Configura os sensores seguidores de linha
  pinMode(SENSOR_ESQUERDA, INPUT);
  pinMode(SENSOR_DIREITA, INPUT);

  // Configura o sensor ultrassônico
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Inicializa o Monitor Serial
  Serial.begin(9600);

  Serial.println("========================================");
  Serial.println(" Carrinho Seguidor de Linha + HC-SR04");
  Serial.println("========================================");
}

//==========================================================
// LOOP PRINCIPAL
//==========================================================
void loop() {

  // Faz a leitura dos sensores
  lerSensoresLinha();

  // Mede a distância utilizando o HC-SR04
  medirDistancia();

  // Mostra informações no Monitor Serial
  mostrarInformacoes();

  // Se houver obstáculo...
  if (distancia <= DISTANCIA_MINIMA) {

    pararMotores();

    Serial.println(">>> OBSTÁCULO DETECTADO <<<");

  }

  // Caso contrário...
  else {

    seguirLinha();

  }

  delay(20);
}

//==========================================================
// Faz a leitura dos sensores seguidores de linha
//==========================================================
void lerSensoresLinha() {

  sensorEsquerda = digitalRead(SENSOR_ESQUERDA);
  sensorDireita = digitalRead(SENSOR_DIREITA);

}

//==========================================================
// Mede a distância utilizando o HC-SR04
//==========================================================
void medirDistancia() {

  // Garante que o Trigger comece desligado
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  // Envia um pulso de 10 microssegundos
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Mede o tempo de retorno
  duracao = pulseIn(ECHO, HIGH);

  // Calcula a distância em centímetros
  distancia = duracao * 0.0343 / 2;

}

//==========================================================
// Mostra informações no Monitor Serial
//==========================================================
void mostrarInformacoes() {

  Serial.print("Sensor Esquerdo: ");
  Serial.print(sensorEsquerda);

  Serial.print(" | Sensor Direito: ");
  Serial.print(sensorDireita);

  Serial.print(" | Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

}

//==========================================================
// Lógica do Seguidor de Linha
//==========================================================
void seguirLinha() {

  //--------------------------------------------------------
  // Branco + Branco
  // O robô segue em frente
  //--------------------------------------------------------
  if (sensorEsquerda == 0 && sensorDireita == 0) {

    frente();

  }

  //--------------------------------------------------------
  // Preto + Branco
  // Corrige para a esquerda
  //--------------------------------------------------------
  else if (sensorEsquerda == 1 && sensorDireita == 0) {

    esquerda();

  }

  //--------------------------------------------------------
  // Branco + Preto
  // Corrige para a direita
  //--------------------------------------------------------
  else if (sensorEsquerda == 0 && sensorDireita == 1) {

    direita();

  }

  //--------------------------------------------------------
  // Preto + Preto
  // Para o robô
  //--------------------------------------------------------
  else {

    pararMotores();

  }

}

//==========================================================
// Movimento para frente
//==========================================================
void frente() {

  MOTOR_ESQUERDA.write(180);
  MOTOR_DIREITA.write(0);

}

//==========================================================
// Curva para esquerda
//==========================================================
void esquerda() {

  MOTOR_ESQUERDA.write(90);
  MOTOR_DIREITA.write(0);

}

//==========================================================
// Curva para direita
//==========================================================
void direita() {

  MOTOR_ESQUERDA.write(180);
  MOTOR_DIREITA.write(90);

}

//==========================================================
// Para os motores
//==========================================================
void pararMotores() {

  MOTOR_ESQUERDA.write(90);
  MOTOR_DIREITA.write(90);

}