# ProyectoFinal
Proyecto final de la materia "Aquitectura Computacional".
## Problema principal 
Se requiere un sistema seguro, eficiente y fácil de usar capaz de monitorear en tiempo real las condiciones ambientales, incluyendo temperatura, humedad, luz y movimiento. El sistema alerta a los usuarios cuando estas condiciones superen los umbrales preestablecidos.
## Objetivos
### Desarrollo del software:
- Desarrollar una interfaz de seguridad, menú principal y menú secundario para el usuario en la pantalla LCD.
- Programar la lógica de lectura y monitoreo de los sensores.
- Programar funciones para cada una de las implementaciones dentro del proyecto.
- Implementar un sistema de alarma cada vez que se superan los umbrales establecidos para temperatura, luz, movimiento y bloqueo del sistema.
- Añadir medidas de seguridad, como bloqueo del sistema cuando se supere la cantidad de intentos al ingresar una contraseña o un limite de tiempo para ingresar la contraseña.
### Desarrollo del Hardware:
- Utilizar un Arduino Mega como microcontrolador principal. 
- Integrar sensores de temperatura y humedad (DHT11), luz (fotoresistor) y gas. 
- Incorporar una pantalla LCD para la visualización de datos. 
- Añadir un potenciómetro y un teclado (keypad) para la configuración del sistema.
- Implementar un LED RGB y un buzzer para las alertas sonoras y visuales.
- Utilizar una protoboard y cables para implementar los circuitos necesarios.
# Dependencias necesarias a instalar
Para correr el proyecto se deben de instalar las siguientes librerias de arduino:
- DHT sensor library: https://www.arduino.cc/reference/en/libraries/dht-sensor-library/
- LiquidCrystal: https://www.arduino.cc/reference/en/libraries/liquidcrystal/
- Keypad: https://www.arduino.cc/reference/en/libraries/keypad/
- AsyncTaskLib: https://www.arduino.cc/reference/en/libraries/asynctasklib/
- StateMachineLib: https://www.arduino.cc/reference/en/libraries/statemachinelib/
- LiquidMenu: https://www.arduino.cc/reference/en/libraries/liquidmenu/
