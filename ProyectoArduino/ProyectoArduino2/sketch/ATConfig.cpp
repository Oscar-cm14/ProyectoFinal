/**
   @file ATConfig.cpp
   @brief Implementación de las tareas asincronas
*/
#include "ATConfig.h"
#include "SMConfig.h"
#include "LMConfig.h"

/** @brief Actualiza el menu */
void updateMenu();
/** @brief Actualiza la temperatura */
void controlTemperatura();
/** @brief Actualiza la humedad */
void controlHumedad();
/** @brief Actualiza el sensor de luz */
void controlLuz();
/** @brief Actualiza el sensor de hall */
void controlHall();
/** @brief Actualiza el sensor de infrarojo */
void controlInfraRojo();
/** @brief Funcion que manda una señal de timeout */
void inputTimeout();
/** @brief Funcion que resetea la seguridad en caso de AFK */
void onSeguridadAFK();

AsyncTask taskMenu(1000, true, updateMenu);
AsyncTask taskTemperatura(1000, true, controlTemperatura);
AsyncTask taskHumedad(1000, true, controlHumedad);
AsyncTask taskLuz(1000, true, controlLuz);
AsyncTask taskHall(1000, true, controlHall);
AsyncTask taskInfraRojo(100, true, controlInfraRojo);
AsyncTask taskTimeoutAmbiental(5000, false, inputTimeout);
AsyncTask taskTimeoutEventos(3000, false, inputTimeout);
AsyncTask taskTimeoutBloqueo(7000, false, inputTimeout);
AsyncTask taskTimeoutAlarma(4000, false, inputTimeout);
AsyncTask taskTimeoutInicioAFK(7000, false, onSeguridadAFK);

void updateAllAsyncTasks() {
  taskMenu.Update();
  taskTemperatura.Update();
  taskHumedad.Update();
  taskLuz.Update();
  taskHall.Update();
  taskInfraRojo.Update();
}

void stopAllAsyncTasks() {
  taskMenu.Stop();
  taskTemperatura.Stop();
  taskHumedad.Stop();
  taskLuz.Stop();
  taskHall.Stop();
  taskInfraRojo.Stop();
}

void updateMenu() {
  mainMenu.update();
}

void controlTemperatura() {
  T = temperatura.rolling(dht.readTemperature());
}

void controlHumedad() {
  H = humedad.rolling(dht.readHumidity());
}

void controlLuz() {
  L = luz.rolling(analogRead(PHOTOCELL_PIN));
}

void controlHall() {
  HALL = hall.rolling(analogRead(HALL_PIN));
}

void controlInfraRojo() {
  
  digitalWrite(INFRAROJO_EN_PIN, HIGH);
  delayMicroseconds(210);
  if (digitalRead(INFRAROJO_PIN)) {
    INFRAROJO = 0;
  } else {
    delayMicroseconds(395);
    if (digitalRead(INFRAROJO_PIN)) {
      INFRAROJO = 0;
    } else {
      INFRAROJO = 1;
    }
  }
  digitalWrite(INFRAROJO_EN_PIN, LOW);
  
  INFRAROJO = 0;
}

void inputTimeout() {
  input = TIMEOUT;
}

void onSeguridadAFK() {
  --password_attempts;
  keypadBuffer.clear();
  setLED(1, 1, 0);
  lcd.clear();
  lcd.print("Incorrecto");
  delay(1000);
  setLED(0, 0, 0);
  lcd.clear();
  lcd.print("Clave: ");
}