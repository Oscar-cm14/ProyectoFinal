#include "LMConfig.h"

LiquidMenu mainMenu(lcd);
char messageAlarma[MESSAGE_ALARMA_LEN];

/** @brief Funcion que no hace nada */
void blankFunction() { }

// PANTALLA DE MONITOREO AMBIENTAL
LiquidLine status_tmp_m(0, 0, "Luz:", L);
LiquidLine status_hum_m(8, 0, "Hum:", H, "%");
LiquidLine status_luz_m(0, 1, "Temp:", T, "C");
LiquidScreen scrn_monitoreo_ambiental(status_tmp_m, status_hum_m, status_luz_m);

// PANTALLA DE MONITOREO DE EVENTOS
LiquidLine status_hall_m(0, 0, "Hall:", HALL);
LiquidLine status_infra_m(0, 1, "InfraR:", HALL);
LiquidScreen scrn_monitoreo_eventos(status_hall_m);

LiquidLine line_alarma(0, 0, "Precaucion");
LiquidLine status_alarma(0, 1, messageAlarma);
LiquidScreen scrn_alarma(line_alarma, status_alarma);

void setupLiquidMenu() {
  mainMenu.add_screen(scrn_monitoreo_eventos);
  mainMenu.add_screen(scrn_monitoreo_ambiental);
  mainMenu.add_screen(scrn_alarma);
}
