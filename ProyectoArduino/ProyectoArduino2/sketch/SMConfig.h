#pragma once 
#ifndef STATE_MACHINE_CONFIG_H
#define STATE_MACHINE_CONFIG_H
#include "StateMachineLib.h"

/** @brief Estados de la maquina de estados */
enum State {
  INICIO = 0,
  BLOQUEADO = 1,
  MONITOREO_AMBIENTAL = 2,
  MONITOR_EVENTOS = 3,
  ALARMA = 4,  
};

/** @brief Senales de input de la maquina de estados */
enum Input {
  DESCONOCIDO = 0,
  OK = 1,
  BLOQUEO = 2,
  TIMEOUT = 3,
  UMBRAL = 4
};

/** @brief Maquina de estados usada */
extern StateMachine stateMachine;

/** @input senal que se le da a la maquina de estados */
extern Input input;

/** @brief Inicializa la maquina de estados */
void setupStateMachine();


#endif

