#include <skylabStepper.h>
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>
#include "EEPROM.h"
#include "millisDelay.h"
#include "Pins.h"

extern skylabStepper stepperAX;             // OBJETO GLOBAL MOTOR EJE X
extern skylabStepper stepperAY;             // OBJETO GLOBAL MOTOR EJE Y
extern millisDelay Delay;                   // VARIABLE GLOBAL TIPO MILLISDELAY
extern Servo Servos[1];                     // OBJETO GLOBAL SERVOMOTOR ROTULADO

//  variables
extern bool encendidoMaquina;               // BANDERA QUE DETERMINA SI NO SE HA REPRODUCIDO NINGUNA RUTINA DESDE QUE SE REINIO ARDUINO

extern double 
    ZRO,                                    // ANGULO 0° SERVOMOTOR
    HMG,                                    // ANGULO HOME SERVOMOTOR (POSICIÓN POR DEFECTO SERVO, PERMITE INGRESO TUBO SIN APRETAR)
    SR,                                     // ANGULO SERVOROTULADO SERVOMOTOR (POSICIÓN APRIETE SERVO PARA ROTULAR)
    SL,                                     // ANGULO SERVOLIBERADO SERVOMOTOR (POSICION SOLTAR SERVO PARA LIBERAR)
    RTD,                                    // BANDERA ACTIVACIÓN PROCESO ROTULADO (CUANDO RECIBE COMANDO rt)
    V_PT,                                   // VALOR ANALOGICO 1 MOTOR DC ROTULADO (VELOCIDAD BAJA, CUANDO POSICIONA TUBO)
    V_RT,                                   // VALOR ANALOGICO 2 MOTOR DC ROTULADO (VELOCIDAD ALTA, CUANDO LIBERA Y ROTULA)
    value;                                  //

extern int 
    cnt_in,                                 // VARIABLE AUXILIAR LECTURA SERIAL (CUENTA DE CARACTERES RECIBIDOS)
    cnt_time,                               // VARIABLE AUXILIAR PROCESO ROTULADO (CUENTA DURACION TIEMPO, SE USA EN MAIN)
    cnt_time2,
    cnt_timeSR,
    addr,                                   // VARIABLE AUXILIAR INICIALIZACION EEPROM
    t_reset;                                // VARIABLE AUXILIAR DE RESETEO (EN CASO DE NECESITAR RESETEAR MILLIS)


extern double
    vlr_sensor_rotulado1,                   // LECTURA DIGITAL DE SENSOR ROTULADO 1 (SENSOR ROTULADO INFERIOR 1)
    vlr_sensor_tubo,                        // LECTURA DIGITAL DE SENSOR TUBO (SENSOR ROTULADO SUPERIOR)
    vlr_sensor_ln1,                         // LECTURA DIGITAL DE SENSOR FINAL CARRERA LINEA 1
    vlr_sensor_ln2,                         // LECTURA DIGITAL DE SENSOR FINAL CARRERA LINEA 2
    vlr_sensor_ln3,                         // LECTURA DIGITAL DE SENSOR FINAL CARRERA LINEA 3
    vlr_sensor_ln4,                         // LECTURA DIGITAL DE SENSOR FINAL CARRERA LINEA 4
    e_endX,                                 // LECTURA DIGITAL DE SENSOR FINAL CARRERA EJE X
    e_endY,                                 // LECTURA DIGITAL DE SENSOR FINAL CARRERA EJE Y
    stepsYHomeToPickTube,                   // NUMERO DE PASOS AVANCE Y PARA RECOGER TUBO (EN LINEAS)
    stepsYHomeToReleaseTube,                // NUMERO DE PASOS AVANCE Y PARA DEJAR TUBO (EN SISTEMA ROTULACION)
    stepsXCalibrateLineX,                   // NUMERO DE PASOS AVANCE X PARA CENTRAR X AL CENTRO LAS LINEAS
    stepsXLine1,                            // NUMERO DE PASOS ENTRE HOME X Y LINEA 1 (SOLO SE NECESITA UN VALOR ESTIMADO CERCA Y MENOR AL REAL)
    stepsXLine2,                            // NUMERO DE PASOS ENTRE HOME X Y LINEA 2 (SOLO SE NECESITA UN VALOR ESTIMADO CERCA Y MENOR AL REAL)
    stepsXLine3,                            // NUMERO DE PASOS ENTRE HOME X Y LINEA 3 (SOLO SE NECESITA UN VALOR ESTIMADO CERCA Y MENOR AL REAL)
    stepsXLine4,                            // NUMERO DE PASOS ENTRE HOME X Y LINEA 4 (SOLO SE NECESITA UN VALOR ESTIMADO CERCA Y MENOR AL REAL)
    stepsXCalibrateReleaseTube,             // NUMERO DE PASOS ENTRE HOME X Y SISTEMA ROTULACION (IDEALMENTE DEBE SER 0, PERO AJUSTAR VALOR A REALIDAD)
    pprX,
    pprY;

extern double
    rpmMediaX,
    rpmMediaY,
    rpmMaxX,                                // VALOR RPM MOVIMIENTO MOTOR EJE X
    rpmMaxY,                                // VALOR RPM MOVIMIENTO MOTOR EJE Y
    acelerationX,
    acelerationY;

extern char 
    buffer[16],                             // VARIABLE AUXILIAR LECTURA SERIAL (GUARDADO TEMPORAL CARACTERES LEIDOS)
    readC;                                  // VARIABLE AUXILIAR LECTURA SERIAL (GUARDADO TEMPORAR CARACTER ACTUAL LEIDO)

extern String 
    cmd,                                    // VARIABLE AUXILIAR LECTURA SERIAL (GUARDAR STRING FINAL LEIDO)
    rta;                                    // VARIABLE AUXILIAR RESPUESTA SOFTWARE (DEFINE MENSAJE A ENVIAR POR SERIAL)                               

extern bool
    flag_first,                             // BANDERA INICIALIZACION EEPROM (DETERMINA SI SE DEBE LEER EEPROOM)
    flag_rx,                                // BANDERA PROCESAMIENTO COMANDO (DETERMINA SI AÚN SE ESTA PROCESANDO COMANDO INGRESADO)                              
    flag_time,                              // BANDERA DE EJECUCION CUENTA DURACION TIEMPO (LIGADO A CLASE MAIN Y VARIABLE cnt_time)
    flag_time2,
    tube_true,                              // BANDERA SI EXISTE TUBO !
    banderaSRFallo;

extern int varSensoresOk;

extern int contaTubOk;
extern int contaTubNotOk;
extern int contaFallos;
extern int banderaIOT;
extern int contaTubosL1;
extern int contaTubosL2;
extern int contaTubosL3;
extern int contaTubosL4;
extern int contaHistorialFallos;

extern String espacio;
extern String cliente;
extern String version;
extern String falloStop;
extern String falloActual;
extern String falloAnterior;

extern bool varSO1;
extern bool varSO2;
extern bool varSO3;
extern bool varSO4;
extern bool varSO5;
extern bool varSO6;
extern bool varSO7;
extern bool varSO8;
extern bool varSH1;
extern bool varSH2;
extern bool varSH3;
extern bool varSH4;
extern bool varSH5;
extern bool varSH6;
extern bool varSH7;

extern bool varSSR;
extern bool varSGPR;
extern bool variableSolicitar;

extern double vectVarIniciales[17];

extern byte mac[];
extern IPAddress serverIP;
extern int port;

extern EthernetClient client;

extern bool varAuxCiclico;