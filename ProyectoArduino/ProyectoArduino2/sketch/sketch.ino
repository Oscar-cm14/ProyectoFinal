#include "config.h"
#include "SMConfig.h"
#include "LMConfig.h"
#include "ATConfig.h"

void setup() {  
  lcd.begin(LCD_COLS, LCD_ROWS);
  dht.begin();
  Serial.begin(9600);

  // Inicializa el LED  
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  setLED(0, 0, 0);
  // Inicializa el menu del lcd
  Serial.println("Starting LiquidMenu...");
  setupLiquidMenu();
  Serial.println("LiquidMenu Started");

  // Inicializa la maquina de estados
  Serial.println("Starting State Machine...");
  setupStateMachine();
  Serial.println("State Machine Started");

  stateMachine.SetState(INICIO, false, true);
}

void loop() {    
  stateMachine.Update();
  taskMenu.Update();  
}


