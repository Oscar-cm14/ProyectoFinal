/**
 * @file LMConfig.h
 * @brief Configuración del menu LiquidMenu
 */

#pragma once
#ifndef LIQUID_MENU_CONFIG_H
#define LIQUID_MENU_CONFIG_H

#include <LiquidMenu.h>
#include "config.h"

#define MESSAGE_ALARMA_LEN 17

/** @brief Mensaje que se muestra en la alarma */
extern char messageAlarma[MESSAGE_ALARMA_LEN];

/** @brief pantalla de monitoreo ambiental */
extern LiquidScreen scrn_monitoreo_ambiental;
/** @brief pantalla de monitoreo de eventos */
extern LiquidScreen scrn_monitoreo_eventos;
/** @brief pantalla de alarma */
extern LiquidScreen scrn_alarma;

/** @brief Instancia del liquid menu a controlar */
extern LiquidMenu mainMenu;

/** @brief Inicializa el menu de LiquidMenu */
void setupLiquidMenu();

#endif