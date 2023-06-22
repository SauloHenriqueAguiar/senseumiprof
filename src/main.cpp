#include <Arduino.h>
#include <user_interface.h>
#include <task.h>


// Definições de tarefas
void taskLeituraSensor(os_event_t *events);
void taskCalculoMedia(os_event_t *events);
void taskSerialOutput(os_event_t *events);

// Constantes e variáveis
const int ANEL_PINO_ANALOGICO = A0;
const int TAMANHO_MEDIA_MOVEL = 20;
int valores_amostra[TAMANHO_MEDIA_MOVEL];
int indice_amostra = 0;

// Prioridades das tarefas
#define LEITURA_PRIORITY 1
#define CALCULO_PRIORITY 2
#define SERIAL_PRIORITY 3

// Variáveis das tarefas
os_timer_t leitura_timer;
os_timer_t calculo_timer;
os_timer_t serial_timer;

void setup() {
  Serial.begin(9600);

  // Inicializa os timers para as tarefas
  os_timer_setfn(&leitura_timer, (os_timer_func_t *)taskLeituraSensor, NULL);
  os_timer_setfn(&calculo_timer, (os_timer_func_t *)taskCalculoMedia, NULL);
  os_timer_setfn(&serial_timer, (os_timer_func_t *)taskSerialOutput, NULL);

  // Inicia os timers com os intervalos desejados
  os_timer_arm(&leitura_timer, 500, true);
  os_timer_arm(&calculo_timer, 1000, true);
  os_timer_arm(&serial_timer, 1000, true);
}

void loop() {
  // Vazio, não é usado com o Non-OS SDK
}

void taskLeituraSensor(os_event_t *events) {
  int leitura_analogica = analogRead(ANEL_PINO_ANALOGICO);
  valores_amostra[indice_amostra] = leitura_analogica;
  indice_amostra = (indice_amostra + 1) % TAMANHO_MEDIA_MOVEL;
}

void taskCalculoMedia(os_event_t *events) {
  int soma = 0;
  for (int i = 0; i < TAMANHO_MEDIA_MOVEL; i++) {
    soma += valores_amostra[i];
  }
  int media_movel = soma / TAMANHO_MEDIA_MOVEL;

  // Passar a média móvel para a tarefa de saída serial
  system_os_post(SERIAL_PRIORITY, 0, (os_param_t)media_movel);
}

void taskSerialOutput(os_event_t *events) {
  int media_movel = (int)events->par;
  Serial.print("Média móvel: ");
  Serial.println(media_movel);
}