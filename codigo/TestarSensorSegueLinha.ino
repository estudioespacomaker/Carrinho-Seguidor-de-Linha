// Pinos dos sensores
const int sensorDireito  = 6;
const int sensorEsquerdo = 7;

void setup() {

  Serial.begin(9600);

  Serial.println("==============================");
  Serial.println(" TESTE DOS SENSORES SEGUE LINHA ");
  Serial.println("==============================");
}

void loop() {

  int valorEsquerdo = analogRead(sensorEsquerdo);
  int valorDireito  = analogRead(sensorDireito);

  Serial.print("Esquerdo: ");
  Serial.print(valorEsquerdo);

  Serial.print("    ");

  Serial.print("Direito: ");
  Serial.println(valorDireito);

  delay(200);
}