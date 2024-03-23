/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#define BT_PRESSIONADO 0;
#define BT_SOLTO 1;
#define LED_DESLIGADO 0;
#define LED_LIGADO 1;
enum ESTADO { ESTADO_ON1, ESTADO_OFF1, ESTADO_ON2, ESTADO_OFF2, ESTADO_ON3 };
int piscar(DigitalOut &led, int segundos, int intervalo, DigitalIn &bt) {
  int totalPiscadas = segundos * 1000 / intervalo;
  for (int i = 0; i < totalPiscadas; i++) {
    led = !led;
    int bt_pressionado = BT_PRESSIONADO;
    if (bt == bt_pressionado) {
      return 1;
    }
    ThisThread::sleep_for(intervalo * 1ms);
  }
  return 0;
}

int main() {
  DigitalOut led(LED1);
  DigitalIn button(BUTTON1);
  ESTADO estadoAtual = ESTADO_ON1;
  int btAntigo = button;
  while (true) {
    switch (estadoAtual) {
    case ESTADO_ON1:
      led = LED_LIGADO;
      ThisThread::sleep_for(2000ms);
      estadoAtual = ESTADO_OFF1;
      break;
    case ESTADO_OFF1:
      led = LED_DESLIGADO;
      ThisThread::sleep_for(500ms);
      estadoAtual = ESTADO_ON2;
      break;
    case ESTADO_ON2:
      led = LED_LIGADO;
      if (piscar(led, 5, 100, button)) {
        estadoAtual = ESTADO_ON3;
        break;
      }
      estadoAtual = ESTADO_OFF2;
      break;
    case ESTADO_ON3:
      led = LED_LIGADO;
      ThisThread::sleep_for(10000ms);
      estadoAtual = ESTADO_OFF1;
      break;
    case ESTADO_OFF2:
      led = LED_DESLIGADO;
      int btAtual = button;
      int bt_solto = BT_SOLTO;
      int bt_pressionado = BT_PRESSIONADO;
      if (btAtual == bt_solto && btAntigo == bt_pressionado) {
        // piscar(led, 2, 100, button);
        estadoAtual = ESTADO_ON1;
      }
      btAntigo = btAtual;
      break;
    }
  }
}