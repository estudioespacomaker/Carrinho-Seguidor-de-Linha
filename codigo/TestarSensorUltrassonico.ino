#define TRIG 12
#define ECHO 13

void setup() {

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.begin(9600);
}

void loop() {

  long duracao;
  float distancia;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duracao = pulseIn(ECHO, HIGH);

  distancia = duracao * 0.0343 / 2;

  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.print(" cm");

  if (distancia <= 20) {
    Serial.println("  --> Obstáculo Detectado!");
  } else {
    Serial.println("  --> Caminho Livre");
  }

  delay(500);
}