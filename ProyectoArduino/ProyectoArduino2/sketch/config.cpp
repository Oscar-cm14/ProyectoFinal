/**
 * @file config.cpp
 * @brief Implementación de los objetos de configuración globales
 */

#include "config.h"
#include "Average.h"

/* INTENTOS DE INGRESO DE CONTRASEÑA */
int password_attempts = PASSWORD_ATTEMPTS;

// Variables para la contraseña
Buffer keypadBuffer;

/* CONFIGURACION LCD */
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/* CONFIGURACION DHT */
DHT dht(DHT_PIN, DHT_TYPE);

/* CONFIGURACION KEYPAD */
const char KEYPAD_ROWS = 4;
const char KEYPAD_COLS = 4;
char padKeys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
char keypadRowPins[KEYPAD_ROWS] = {22, 24, 26, 28}; // Conectar los pines de las filas del keypad
char keypadColPins[KEYPAD_COLS] = {30, 32, 34, 36}; // Conectar los pines de las columnas del keypad
Keypad customKeypad = Keypad( makeKeymap(padKeys), keypadRowPins, keypadColPins, KEYPAD_ROWS, KEYPAD_COLS);


float T = 0; /* !< Temperatura */
int16_t H = 0; /* !< Humedad */
int16_t L = TH_LUZ_LOW + 1; /* !< Luz */
int16_t HALL = 0; /* !< Hall */
int16_t INFRAROJO = 0; /* !< InfraRojo */

Average<float> temperatura(5);
Average<int16_t> humedad(5);
Average<int16_t> luz(5);
Average<int16_t> hall(5);

void setLED(uint16_t red, uint16_t green, uint16_t blue) {
  digitalWrite(LED_R, red);
  digitalWrite(LED_G, green);
  digitalWrite(LED_B, blue);
}