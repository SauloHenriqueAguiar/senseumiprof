#include <Arduino.h>
 
 
const int ANEL_PINO_ANALOGICO = A0; // Pino analógico ao qual o fio está conectado
const int TAMANHO_MEDIA_MOVEL = 20; // Tamanho da janela da média móvel
int valores_amostra[TAMANHO_MEDIA_MOVEL]; // Array para armazenar os valores de amostra
int indice_amostra = 0; // Índice atual da amostra

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  int leitura_analogica = analogRead(ANEL_PINO_ANALOGICO); // Lê o valor analógico do pino
  
  // Adiciona o valor atual à janela da média móvel
  valores_amostra[indice_amostra] = leitura_analogica;
  indice_amostra = (indice_amostra + 1) % TAMANHO_MEDIA_MOVEL; // Incrementa o índice e mantém dentro do intervalo da janela
  
  // Calcula a média móvel
  int soma = 0;
  for (int i = 0; i < TAMANHO_MEDIA_MOVEL; i++) {
    soma += valores_amostra[i];
  }
  int media_movel = soma / TAMANHO_MEDIA_MOVEL;
  
  // Imprime o valor da média móvel na porta serial
  Serial.print("Média móvel: ");
  Serial.println(media_movel);
  
  delay(1000); // Aguarda 1 segundo antes de fazer a próxima leitura
}