# Control versionamiento

## Creación

~~~
Fecha: 2018
Autor: Andrés Gomez
~~~

## Actualizaciones

~~~
Fecha: [Julio 2023]
Autor: JCaballero
Actualización:
- Cambio en diseño electríco del SKL-180 Master
- Redistribución de pines
- Cambios en lógica sistema de rotulación
- Cambio en lógica sistema de gripper
~~~

~~~
Fecha: [Junio 2023]
Autor: JCaballero
Actualización:
- Mejoras en algoritmo de control de de motores
- Refinación de comunicación con Software
- Creación de Rutina_prueba para implementar cambios en comunicación (y mantener el original)
~~~

~~~
Fecha: [Mayo 2023]
Autor: JCaballero
Actualización:
- Implementación de librería `skylabStepper` para mejoras significativas en rapidez de movimiento motores
- Mejoras en confiabilidad de agarre de tubos de sistema gripper
- Mejoras en confiabilidad de sistema rotulación de tubos
- Creación de rutina prueba de agarre de tubos
~~~

~~~
Fecha: 01/04/2023
Autor: AGomez
Actualización:
- Distribución de código en clases para mejoras en modularidad
~~~

~~~
Fecha: [2018-2019]
Autor: AGomez
Actualización:
- Creación de código de control SKL-180
- Implementación con librería `AccelStepper` y `stepper`
- Control de 2 motores paso a paso, sistema neumático gripper y rotulador de tubos
- Lectura de 6 finales de carrera (home X, home Y, 4 líneas) y 2 sensores ópticos (sistema rotulación tubo)
- Comunicación con Software vía _Serial_
~~~
