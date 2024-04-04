# CLTech_SkyLab_SKL180_Control_V3
## SKYLAB CLTech - Área Automatización - Subárea Control
En este repositorio se encuentra el código de control correspondiente a el producto SKL180 de Skylab utilizando la librería `skylabStepper` en el cual se realizan rutinas para el funcionamiento del producto.

## Versión 3:
  En esta version de codigo se presenta el funcionamiento basico de el producto SKL180 perteneciente a Skylab de CLTech, esta version de codigo es la que se encuentra en los productos SKL180 ubicados en LCC.
  
  Esta versión se encuentra diseñada para el accionamiento de los siguiente actuadores:
   - Motor NEMA 17/23.
   - Servomotor.
   - Motores de aire VDC.
   - Electrovalvulas.
   - Motor DC.

  El accionamiento de dichos actuadores se realiza mediante diversos drivers como drivers de motores paso a paso, puente H y modulos relays.
  
  Esta versión se encuentra diseñada para la lectura de los siguiente tipos de sensores:
   - TCRT5000.
   - TCST2103.

  Los componentes mencionados anteriormente son los que conforman el producto o equipo SKL180.
  La documentación de dichos componentes se encuentra en la carpeta "docs".

### Diferencia entre versiones:

En esta version se realizo la eliminación de 2 funciones que se habian creado para realizar pruebas de funcionamiento entre el software SkyLab.exe y el codigo del area de control, dichas funciones correspondian a los siguientes nombres `procesoIOTpruebaSensores()` y `procesoIOTprueba()`.

## Clases

- Eprom:
Librería encargada de realizar el cargue y guardado de parámetros críticos funcionamiento máquina como:
  - `HMG`: Posición servo de _Home_
  - `SR`: Posición servo de _Servo rotulado_ (Posición de apriete de servo al momento de rotular tubo)
  - `SL`: Posición servo de _Servo liberar_ (Posición de servo para soltar el tubo)
  - `RTD`: Bandera activación proceso rotulado
  - `V_PT`: Velocidad 1 rotación de rodillo rotulador tubo
  - `V_RT`: Velocidad 2 rotación de rodillo rotulador tubo

- GV:
Archivo encargado de declarar las variables globales para todas las librerías. Nota: Si se desea utilizar alguna variable declarada en librerías una librería en particular se debe agregar `#include "GV.h"`

- Home:
Librería encargada de llevar a Home la máquina. Esta se llama en el `loop()` y se llama siempre que no se realice una rutina de recogida de tubos

- Main:
Librería encargada de lectura periodica de sensores y monitoreo de banderas de funcionamiento, y se llama por medio del _Timer 1_ del _MCU_ con un periodo de `2000ms`.

- MainSerial:
Librería encargada de la comunicación serial del _MCU_ con el _Software SIGA_ y _Software pruebas_. Se encarga de leer y procesar los comandos que recibe. La lista de comandos válidos son:

  - `?est`: Reporte de estado de máquina
  - `hmgrp`: Realizar rutina de prueba de gripper (Abrir, cerrar y abrir gripper)
  - `rt`: Realizar rutina de prueba _Sistema de rotulación_ de proceso de _rotulado_
  - `hm`: Realizar rutina de prueba _Servomotor_ de proceso _Servo home_
  - `sr`: Realizar rutina de prueba _Servomotor_ de proceso _Servo rotulado_
  - `svlb`: Realizar rutina de prueba _Servomotor_ de proceso _Servo liberado_
  - `looplX`: Realizar rutina de prueba _SKL-180_ de agarre y devolución de tubos a la linea `X` (1,2,3,4)
  - `lX`: Realizar rutina de máquina de agarre y rotulado de tubos de la linea `X` (1,2,3,4)
  - `LX`: Realizar rutina (de prueba) de máquina de agarre y rotulado de tubos de la linea `X` (1,2,3,4)
  - `init`: Analiza el estado de los sensores de cada subsistema
  - `habilitados`: Presenta el vector de cuales son los sensores que se encuentran habilitados y deshabilitados del producto
  - `RLX`: Reinicia el contador de tubos de la linea `X` (1,2,3,4)
  

- PinMode:
Librería encargada de configurar el modo de funcionamiento de todos los pines del MCU utilizados (_INPUT_ y _OUTPUT_)

- Pins:
Archivo encargado de declarar las IDs de los pines del MCU utilizados

- Rutina:
Librería encargada de recopilar todas las rutinas de prueba y funcionamiento de la máquina. Entre las cuales se destacan:

  - `griperOpen`: Acción de abrir gripper
  - `griperClose`: Acción de cerrar gripper
  - `posicionarTubo` en _Rutinas_pruebas_ / `RotularTubo` en _Rutinas_: Rutina para posicionar tubo con etiqueta orientada a cierto ángulo
  - `RotularTubo` en _Rutinas_pruebas_ / `Rotulado` en _Rutinas_: Rutina para accionar motor rotulado por 3 seg (rotación simultánea con la impresión de la etiqueta de la impresora interna)
  - `LiberarTubo`: Rutina de liberación tubo (accionar motor rotulado, abrir el servo para dejar caer tubo y volver a home)
  - `RecogerYDevolverTubo`: Rutina de prueba de _SKL-180_ de agarre y devolución de tubos a la linea `X` (1,2,3,4)
  - `RecogerTubo`: Rutina de máquina de agarre y rotulado de tubos de la linea `X` (1,2,3,4). Hay dos versiones: _Rutina_ y _Rutina_pruebas_
  - `poscionar2Sensores` en _Rutinas_: Rutina para posicionar el tubo en el instante en que esté llegue a el sistema de rotulacion.
  - `poscionar2SensoresX2` en _Rutinas_: Rutina para posicionar el tubo, el posicionamiento se realiza despues de que a esté se le de una vuelta a su llegada a el sistema de rotulacion.

## Software pruebas
El programa `SkyLab Control.exe` fue desarrollado para ejecutar los comandos predefinidos, para probar cada subsistema por separado (gripper, servomotor rotulado, motor rotulado, impresora interna) y rutinas de funcionamiento (buscar tubo en linea 1,2,3,4).
