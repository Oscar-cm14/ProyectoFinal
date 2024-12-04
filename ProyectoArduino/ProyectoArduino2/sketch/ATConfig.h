/**
 * @file ATConfig.h
 * @brief Declaración de las tareas asincronas
 */
#ifndef ASYNC_TASKS_CONFIG_H
#define ASYNC_TASKS_CONFIG_H

#include "AsyncTaskLib.h"

extern AsyncTask taskMenu;
extern AsyncTask taskTemperatura;
extern AsyncTask taskHumedad;
extern AsyncTask taskLuz;
extern AsyncTask taskHall;
extern AsyncTask taskInfraRojo;
extern AsyncTask taskTimeoutInicioAFK;
extern AsyncTask taskTimeoutEventos;
extern AsyncTask taskTimeoutAmbiental;
extern AsyncTask taskTimeoutBloqueo;
extern AsyncTask taskTimeoutAlarma;

/** @brief Se actualizan todas las tareas asincronas */
void updateAllAsyncTasks();

/** @brief detiene todas las tareas asincronas activas */
void stopAllAsyncTasks();

#endif