#include <Arduino.h>

const int NUM_ANEIS = 3; // Número de anéis metálicos
int pinos_analogicos[NUM_ANEIS] = {0, 1, 2}; // Pinos analógicos correspondentes aos anéis
int valores_umidade[NUM_ANEIS]; // Array para armazenar os valores de umidade

void setup() {
  for (int i = 0; i < NUM_ANEIS; i++) {
    pinMode(pinos_analogicos[i], INPUT); // Configura os pinos analógicos como entrada
  }
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  for (int i = 0; i < NUM_ANEIS; i++) {
    int leitura_analogica = analogRead(pinos_analogicos[i]); // Lê o valor analógico para o anel atual
    // Realize os cálculos e conversões necessárias para estimar a umidade com base na leitura
    // Armazene o valor de umidade estimado no array valores_umidade[i]

    // Exemplo de impressão dos valores de umidade na porta serial
    Serial.print("Anel ");
    Serial.print(i + 1);
    Serial.print(" - Umidade: ");
    Serial.print(valores_umidade[i]);
    Serial.println("%");
  }

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}