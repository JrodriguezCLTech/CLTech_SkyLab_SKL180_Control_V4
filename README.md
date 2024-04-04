# CLTech_SkyLab_SKL180_Control_V4
## SKYLAB CLTech - Área Automatización - Subárea Control
En este repositorio se encuentra el código de control correspondiente a el producto SKL180 de Skylab utilizando la librería `skylabStepper` en el cual se realizan rutinas para el funcionamiento del producto.

## Versión 4:
  En esta version de codigo se implemento un monitoreo de las variables con la finalidad de generar una configuración de los motores basado en comandos lo que permite monitorear y configurar los parametros y/o variables iniciales de movimiento del equipo con base a el monitoreo y modificación de comandos que afectan directamente el vector y adicionalmente se implementaron dos clases con la finalidad de realizar solicitudes Http (Get Http y Post Http).
  
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

En esta version se realizo la implementación de 3 clases mas las cuales son `mainSerialVector()`, `getHttp()` y `postHttp()`.

## Software pruebas
El programa `SkyLab Control.exe` fue desarrollado para ejecutar los comandos predefinidos, para probar cada subsistema por separado (gripper, servomotor rotulado, motor rotulado, impresora interna) y rutinas de funcionamiento (buscar tubo en linea 1,2,3,4).
