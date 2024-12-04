#include "SMConfig.h"

#define N_STATES    5
#define N_VERTICES  8

#include "config.h"
#include "ATConfig.h"
#include "LMConfig.h"
#include "melody.h"

StateMachine stateMachine(N_STATES, N_VERTICES);
Input input;

/** @brief Compara el input de la maquina de estados y lo resetea */
int compareAndResetInput(Input input);

// FUNCIONES DE TRANSICIÓN
/** 
 * @brief Funcion que se encarga de pedir una contraseña
 * @returns int 1 en caso de que se pueda ir a Monitoreo Ambiental, 0 en caso de contraseña erronea
 */
int seguridad();
/**
 * @brief funcion que se encarga de chequear si sobran intentos de seguridad
 * @returns int 1 en caso de no más intentos, 0 en caso de que falten intentos
 */
int sin_intentos_seguridad();
/** 
  * @brief comprueba si se debe de ir a inicio desde bloqueado
  * @return 1 en caso de que se pase a inicio, 0 en caso de quedarse en el mismo estado
  */
int bloqueo_inicio();
/** 
  * @brief comprueba si se debe de ir a alarma desde monitoreo ambiental
  * @return 1 en caso de que se pase a alarma, 0 en caso de quedarse en el mismo estado
  */
int monitor_ambiental_alarma();
/**
  * @brief comprueba si se llego al timeout del monitor ambiental 
  * @return 1 en caso de tener timeout, 0 en caso de quedarse en el mismo estado
  */
int monitor_ambiental_timeout();
/** 
  * @brief comprueba si se debe de ir a alarma desde monitoreo de eventos 
  * @return 1 en caso de pasar a alarma, 0 en caso de quedarse en el mismo estado
  */
int monitor_eventos_alarma();
/** 
  * @brief comprueba si se llego al timeout del monitor de eventos 
  * @return 1 en caso de tener timeout, 0 en caso de quedarse en el mismo estado
  */
int monitor_eventos_timeout();
/** 
  * @brief comprueba si se debe de ir a inicio en alarma 
  * @return 1 en caso de pasar a inicio, 0 en caso de quedarse en el mismo estado
  */
int alarma_inicio(); 

// FUNCIONES DE ENTRADA A UN ESTADO
/** @brief funcion que se ejecuta al entrar al estado de inicio */
void onEnteringInicio();
/** @brief funcion que se ejecuta al entrar al estado de bloqueo */
void onEnteringBloqueado();
/** @brief funcion que se ejecuta al entrar al estado de monitoreo ambiental */
void onEnteringMAmbiental();
/** @brief funcion que se ejecuta al entrar al estado de monitoreo de eventos */
void onEnteringMEventos();
/** @brief funcion que se ejecuta al entrar al estado de alarma */
void onEnteringAlarma();

// FUNCIONES DE SALIDA DE UN ESTADO
/** @brief funcion que se ejecuta al salir del estado de inicio */
void onLeavingInicio();
/** @brief funcion que se ejecuta al salir del estado de bloqueo */
void onLeavingBloqueado();
/** @brief funcion que se ejecuta al salir del estado de monitoreo ambiental */
void onLeavingMAmbiental();
/** @brief funcion que se ejecuta al salir del estado de monitoreo de eventos */
void onLeavingMEventos();
/** @brief funcion que se ejecuta al salir del estado de alarma */
void onLeavingAlarma();

void setupStateMachine() {
  stateMachine.AddTransition(INICIO, MONITOREO_AMBIENTAL, seguridad);  
  stateMachine.AddTransition(INICIO, BLOQUEADO, sin_intentos_seguridad);  
  stateMachine.AddTransition(BLOQUEADO, INICIO, bloqueo_inicio);
  stateMachine.AddTransition(MONITOREO_AMBIENTAL, MONITOR_EVENTOS, monitor_ambiental_timeout);
  stateMachine.AddTransition(MONITOREO_AMBIENTAL, ALARMA, monitor_ambiental_alarma);
  stateMachine.AddTransition(MONITOR_EVENTOS, MONITOREO_AMBIENTAL, monitor_eventos_timeout);
  stateMachine.AddTransition(MONITOR_EVENTOS, ALARMA, monitor_eventos_alarma);
  stateMachine.AddTransition(ALARMA, INICIO, alarma_inicio);

  stateMachine.SetOnEntering(INICIO, onEnteringInicio);
  stateMachine.SetOnEntering(BLOQUEADO, onEnteringBloqueado);
  stateMachine.SetOnEntering(MONITOREO_AMBIENTAL, onEnteringMAmbiental);
  stateMachine.SetOnEntering(MONITOR_EVENTOS, onEnteringMEventos);
  stateMachine.SetOnEntering(ALARMA, onEnteringAlarma);

  stateMachine.SetOnLeaving(INICIO, onLeavingInicio);
  stateMachine.SetOnLeaving(BLOQUEADO, onLeavingBloqueado);
  stateMachine.SetOnLeaving(MONITOREO_AMBIENTAL, onLeavingMAmbiental);
  stateMachine.SetOnLeaving(MONITOR_EVENTOS, onLeavingMEventos);
  stateMachine.SetOnLeaving(ALARMA, onLeavingAlarma);
}

int compareAndResetInput(Input inputIn) {
  if (input == inputIn) {
    input = DESCONOCIDO;
    return 1;
  }
  return 0;  
}

// FUNCIONES DE TRANSICIÓN
int seguridad() {  
  const char key = customKeypad.getKey();
  if (!key) return 0;

  if (key != 'A') {
    keypadBuffer.push(key);
    lcd.print('*');
    if (!keypadBuffer.isFull()) return 0;
  }

  if (keypadBuffer.len == PASSWORD_LEN && strncmp(PASSWORD, keypadBuffer.str, PASSWORD_LEN) == 0) {
    setLED(0, 1, 0);
    lcd.clear();
    lcd.print("Correcto");
    return 1; /* Cambia de fase */
  } else {
    --password_attempts;
    setLED(1, 1, 0);
    lcd.clear();
    lcd.print("Incorrecto");    
  }
  delay(1000);
  setLED(0, 0, 0);  
  lcd.clear();
  lcd.print("Clave: ");
  keypadBuffer.clear();
}

int sin_intentos_seguridad() {  
  return password_attempts == 0;
}

int bloqueo_inicio() {
  setLED(1, 0, 0);
  lcd.setCursor(0, 0);
  lcd.print("Sistema ");
  lcd.setCursor(0, 1);
  lcd.print("Bloqueado");
  execute_melody(melodyBloqueo);
  lcd.clear();
  return 1;
}

int monitor_ambiental_alarma() {
  float lastT = T;
  
  taskTemperatura.Update();
  taskHumedad.Update();
  taskLuz.Update();  

  // suena si la temperatura aumenta
  if (T > lastT) {
    tone(buzzer, 500, 100);
  }
  if (T > TH_TMP_HIGH) {
    strcpy(messageAlarma, "'Esta Caliente");
    return 1;
  }
  
  if (L > TH_LUZ_HIGH) {
    strcpy(messageAlarma, "'Esta Oscuro");
    return 1;
  }

  if (L < TH_LUZ_LOW) {
    strcpy(messageAlarma, "'Mucha luz");
    return 1;
  }
  
  return 0;
}

int monitor_ambiental_timeout() {
  taskTimeoutAmbiental.Update();  
  return compareAndResetInput(TIMEOUT);
}

int monitor_eventos_alarma() {
  taskHall.Update();
  taskInfraRojo.Update();
  if (HALL > TH_HALL) {
    strcpy(messageAlarma, "Hay Iman");
    return 1;
  }
  if (INFRAROJO) {
    strcpy(messageAlarma, "Movimiento");
    return 1;
  }
  return 0;
}

int monitor_eventos_timeout() {
  taskTimeoutEventos.Update();
  return compareAndResetInput(TIMEOUT);
}

int alarma_inicio() {
  return customKeypad.getKey() == '#';
}

// ENTERING/LEAVING FUNCTIONS
void onEnteringInicio() {
  Serial.println("Entering Inicio");  

  keypadBuffer.clear();
  password_attempts = PASSWORD_ATTEMPTS;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Clave: ");
}
void onLeavingInicio() {
  Serial.println("Leaving Inicio");
  taskTimeoutInicioAFK.Stop();
}

void onEnteringMAmbiental() {
  Serial.println("Entering Monitoreo Ambiental");  
  taskTemperatura.Start();
  taskHumedad.Start();
  taskLuz.Start();
  taskHall.Start();
  taskTimeoutAmbiental.Start();
  taskMenu.Start();
  mainMenu.change_screen(&scrn_monitoreo_ambiental);
  mainMenu.update();
}
void onLeavingMAmbiental() {
  Serial.println("Leaving Monitoreo Ambiental");
  taskTemperatura.Stop();
  taskHumedad.Stop();
  taskLuz.Stop();
  taskHall.Stop();
  taskTimeoutAmbiental.Stop();
  taskMenu.Stop();
}

void onEnteringMEventos() {
  Serial.println("Entering Monitoreo Eventos");    
  taskTimeoutEventos.Start();
  taskHall.Start();
  taskInfraRojo.Start();
  taskMenu.Start();
  mainMenu.change_screen(&scrn_monitoreo_eventos);
  mainMenu.update();
}
void onLeavingMEventos() {
  Serial.println("Leaving Monitoreo Eventos");
  taskTimeoutEventos.Stop();
  taskInfraRojo.Stop();
  taskHall.Stop();  
  taskMenu.Stop();
}

void onEnteringBloqueado() {
  Serial.println("Entering Bloqueado");

}
void onLeavingBloqueado() {
  Serial.println("Leaving Bloqueado");
  setLED(0, 0, 0);
}

void onEnteringAlarma() {
  Serial.println("Entering Alarma");  
  setLED(0, 0, 1);
  tone(buzzer, 97, 4000);
  taskTemperatura.Start();
  taskHumedad.Start();
  taskLuz.Start();
  taskHall.Start();
  taskTimeoutAlarma.Start();
  mainMenu.change_screen(&scrn_alarma);
  mainMenu.update();
}
void onLeavingAlarma() {
  Serial.println("Leaving Alarma");
  taskTemperatura.Stop();
  taskHumedad.Stop();
  taskLuz.Stop();
  taskHall.Stop();

  
  temperatura.clear();
  humedad.clear();
  luz.clear();
  hall.clear();
  T = H = HALL = INFRAROJO = 0;
  L = TH_LUZ_LOW + 1;

  noTone(buzzer);
  taskTimeoutAlarma.Stop();
  setLED(0, 0, 0);
}