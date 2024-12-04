/**
 * @file config.h
 * @brief configuración global del programa
 */

#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <DHT.h>
#include "Average.h"

/* CONFIGURACION DEL PROGRAMA */
#define PASSWORD_ATTEMPTS 3
#define PASSWORD_LEN 4
#define PASSWORD "4444"

#define TH_TMP_HIGH 25
#define TH_TMP_LOW 10
#define TH_LUZ_HIGH 650
#define TH_LUZ_LOW 70
#define TH_HALL 10000
#define TH_INFRAROJO 1200

#define LCD_ROWS 2
#define LCD_COLS 16

/* CONFIGURACION DE PINES */
#define DHT_TYPE DHT11 // !Cambiar al dht que es cuando se deba de entregar
#define DHT_PIN 39
#define PHOTOCELL_PIN A0
#define BUZZER_PIN 7
#define HALL_PIN A1
#define INFRAROJO_PIN 41
#define INFRAROJO_EN_PIN 6
#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2
#define LED_R 8
#define LED_G 9
#define LED_B 10
#define BUTTON_PIN 53

/* INTENTOS DE INGRESO DE CONTRASEÑA */
extern int password_attempts;

/* BUFFER DE LA CONTRASEÑA */
typedef struct {
  static const int size = 16;
  char str[size + 1];
  byte len = 0;
  void push(char chr) {
    if (len == size) return;
    str[len++] = chr;
  }
  void clear() {
    for (size_t i = 0; i < this->len; i++) {
      str[i] = 0;
    }
    len = 0;
  }
  bool isFull() {
    return len == size;
  }
  char lastCharacter() {
    return len == 0 ? 0 : str[len - 1];
  }
} Buffer;
extern Buffer keypadBuffer;

/** @brief Instancia Global del objeto controlador del LCD */
extern LiquidCrystal lcd;

/** @brief Instancia global del objeto cotrolador del DHT */
extern DHT dht;

/** @brief Intancia del objeto controlador del Keypad */
extern Keypad customKeypad;


/* VALORES GLOBALES DE MONITOREO */
extern float T;         /* !< Temperatura */
extern int16_t H;       /* !< Humedad */
extern int16_t L;       /* !< Luz */
extern int16_t HALL;    /* !< Hall */
extern int16_t INFRAROJO; /* !< InfraRojo */
extern Average<float> temperatura;
extern Average<int16_t> humedad;
extern Average<int16_t> luz;
extern Average<int16_t> hall;

void setLED(uint16_t red, uint16_t green, uint16_t blue);

#endif