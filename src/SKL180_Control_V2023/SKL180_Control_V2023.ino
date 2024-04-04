
/*****************************************CLTECH*****************************************************
                                        CLTECH LTD.
  
                                    http://WWW.CLTECH.NET

Ultima modificación: 05/11/2023
Modelo:
SKL180
    sistemas CNC(aceroplata)
    sistema de rotulacion
    codifo VSC
Version SKL180_VSC

Modificaciones
[2019]
    -
[2020]
    -
[2023]
    - Cambio de librería (skylabStepper) para control de los motores paso a paso, stepper.h V1.2, 
    aumentando al máximo la velocidad de movimiento
    - Se modificó algoritmo llegada a Home
    - Se modificó algoritmo de recogida y dejada de tubo
    - Cambios menores en ajuste de parámetros
    - Cambios menores posicionamiento gripper
    - Cambios menores en algoritmo de abertura/cierre de gripper
    - Cambios menores en algoritmo de accionamiento servorotulado
*/

//Prueba clonar repositorio desde mi PC personal (Camilo)

extern volatile unsigned long timer0_millis;
unsigned long new_value = 0;

//  import
//#include <loopTimer.h>
#include <TimerOne.h>
#include <EEPROM.h>
#include <skylabStepper.h>
#include <Servo.h>
#include "millisDelay.h"
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

//  include
#include "PinMode.h"
#include "MainSerial.h"
#include "Home.h"
#include "Main.h"
#include "Eprom.h"  
#include "lecturaSensores.h"


MainSerial mainSerial;
Home homeXY;
PinMode pinmode;
millisDelay Delay;
Main main_IRS;
Eprom EProm;
lecturaSensores lecturaSensoresAux;

#define STEPS 2000

int servoPins[] = {ServoMotorPin};
int servoPosSafeStart[NUM_SERVOS];
Servo Servos[NUM_SERVOS];

//  variables
bool doHomeXY = true,
     encendidoMaquina = true;
     
double ZRO = 0,
    HMG,
    SR,
    SL = 0,// no importa
    RTD = 1, //Comando
    V_PT,
    V_RT,
    value,
    sec = 1;

int cnt_in,
    cnt_time = 0,
    cnt_time2 = 0,
    addr,
    t_reset = 0;

    
double
    vlr_sensor_rotulado1,
    vlr_sensor_tubo,
    vlr_sensor_ln1,
    vlr_sensor_ln2,
    vlr_sensor_ln3,
    vlr_sensor_ln4,
    e_endX,
    e_endY,
    millisXFromHomeToLine1 = 750,
    millisXBetweenLines = 130,
    millisYToPickupTube = 250,
    millisYFromHomeToPickupTube = 900,
    millisYFromHomeToReleaseTube = 500,
    speedAcelerate = 30,
    stepsYHomeToPickTube,
    stepsYHomeToReleaseTube,
    stepsXCalibrateLineX,
    stepsXLine1, 
    stepsXLine2,
    stepsXLine3,
    stepsXLine4,
    stepsXCalibrateReleaseTube,
    pprX = 400,
    pprY = 400;

double
    rpmMaxX,
    rpmMaxY,
    rpmMediaX,
    rpmMediaY,
    acelerationX,
    acelerationY;

int contaTubOk;
int contaTubNotOk;
int contaFallos;
int contaTubosL1;
int contaTubosL2;
int contaTubosL3;
int contaTubosL4;
int contaHistorialFallos;
int banderaIOT;
String espacio = " ";
int varSensoresOk;
String falloStop;
String falloActual;
String falloAnterior;
String cliente = "CLIENTE";
String version = "V_4";

// Variables Aceleracion motores paso
skylabStepper stepperAX(skylabStepper::skylabSKL180EjeX,0,X_DIR_PIN,X_STEP_PIN,X_ENABLE_PIN);
skylabStepper stepperAY(skylabStepper::skylabSKL180EjeY,1,Y_DIR_PIN,Y_STEP_PIN,Y_ENABLE_PIN);

String readString;
String trama = "";
String cmd;
String rta;
String V_linea;

bool flag_first = false;
bool flag_rx = false;
bool flag_hm = false;
bool flag_time = false;
bool flag_time2 = false;
bool tube_true = false;
bool flag_disp = false;
bool banderaSRFallo = false;

bool varSO1 = 0;
bool varSO2 = 0;
bool varSO3 = 0;
bool varSO4 = 0;
bool varSO5 = 0;
bool varSO6 = 0;
bool varSO7 = 0;
bool varSO8 = 0;
bool varSH1 = 0;
bool varSH2 = 0;
bool varSH3 = 0;
bool varSH4 = 0;
bool varSH5 = 0;
bool varSH6 = 0;
bool varSH7 = 0;
bool varSSR = 0;
bool varSGPR = 0;

char buffer[16];
char readC;

double vectVarIniciales[17];

bool variableSolicitar = 0;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress serverIP(181, 48, 43, 69); // Dirección IP del servidor al que deseas hacer la solicitud HTTP
int port = 36810; // Puerto del servidor
bool varAuxCiclico = false;
EthernetClient client;

void setup()
{
    Timer1.initialize(2000000); // 2mS
    Timer1.attachInterrupt(ISR_Mode);
    Serial.begin(9600);
    pinmode.initPin();
    // EeProm();
    addr = EEPROM.length();    // read a byte from the current address of the EEPROM
    value = EEPROM.read(addr); // Serial.print(value);
    EProm.initEprom();
    EProm.leerEEPROMPredet();
    // Servo
    servoPosSafeStart[0] = {int(HMG)}; //  Ir a HMG
    initServos();
    
    stepperAX.configurarCNCSimp(X_MIN_PIN,1,true);
    stepperAY.configurarCNCSimp(Y_MIN_PIN,1,true);
    stepperAX.configurarMaxMovAxis(19000);
    stepperAY.configurarMaxMovAxis(8990);

    mainSerial.rutinas.varIOT[2] = "0";
    
    pinMode(gripClose, LOW); // ABRO GRIPPER
    delay(200);
    pinMode(motorOn, HIGH); // PRENDO MOTOR
    delay(800);
    pinMode(motorOn, LOW); // APAGO MOTOR

    t_reset = millis();

    for (int i=0; i<=11; i++)
    {
        mainSerial.rutinas.varIOT[i] = "-";
    }

    pinMode(servoMotorOn, OUTPUT); 
    delay(250);
    Servos[0].write(ZRO);
    delay(250);
    pinMode(servoMotorOn, INPUT);
    
    varSensoresOk = 0;
}

/*void setMillis(unsigned long new_millis){
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}*/

unsigned long temp1 = 0;
void loop()
{
    //mainSerial.rutinas.griperClose();
    // lecturaSensoresAux.valorSH7 = analogRead(sensor_gripper);
    // lecturaSensoresAux.voltajeSH7 = lecturaSensoresAux.valorSH7*5/1023;
    // Serial.println(lecturaSensoresAux.voltajeSH7);
    // delay(2000);
    // mainSerial.rutinas.griperOpen();
    // delay(5000);

    lecturaSensoresAux.deteccionSensores();
    
    if(mainSerial.rutinas.sinTubo == 1)
    {
        mainSerial.rutinas.sinTubo = 0;
        varSensoresOk = 2;
    }

    //loopTimer.check(Serial);
    interrupts();
    mainSerial.conect();
    
    if(varSensoresOk == 1)
    {
        varSensoresOk = 0;
        flag_hm = false;
        if (flag_hm == false){
            homeXY.initHome();
            //Home IOT
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[8] == 1 && lecturaSensoresAux.varIOTSensores[9] == 1){
                mainSerial.rutinas.varIOT[2] = "1";
            }
            else if(lecturaSensoresAux.varIOTSensores[8] == 0 && lecturaSensoresAux.varIOTSensores[9] == 0){
                mainSerial.rutinas.varIOT[2] = "0";
                mainSerial.rutinas.procesoIOT();
                mainSerial.rutinas.stopIOT();
            }
            flag_time = false;
            cnt_time = 0;
            flag_time2 = false;
            cnt_time2 = 0;
        } else {
            flag_hm = true;
        }

        /*if (millis() - t_reset < 0 ) {
        t_reset = millis();
        }*/
        
        
        /*switch(sec) {
        case 1:
            mainSerial.Run("l1");
            break;
        case 2:
            mainSerial.Run("l2");
            break;
        case 3:
            mainSerial.Run("l3");
            break;
        case 4:
            mainSerial.Run("l4");
            sec = 0;
            break;
        }
        sec ++;*/
        //mainSerial.Run("l2");

        if (millis()-temp1 >= 1000) {
            temp1 = millis();
            /*Serial.print(digitalRead(sensor_rotulado1));
            Serial.print(" ");
            Serial.print(digitalRead(sensor_rotulado2));
            Serial.print(" ");
            Serial.println(digitalRead(sensor_tubo));*/
        }
    }
    else{ }   
}
// ISR INTERRPCIONES
void ISR_Mode()
{
    main_IRS.ISRMode();
    if (millis() - t_reset >= 500) {
      t_reset = millis();
      //Serial.print(digitalRead(sensor_tubo));
      //Serial.print(" ");
      //Serial.println(digitalRead(sensor_rotulado1));
      //reset();
      //setMillis(new_value);
      //Serial.println("Reinicio millis()");
    }
}
//! Init servos
void initServos()
{
    for (int i = 0; i < NUM_SERVOS; i++)
    {
        Servos[i].attach(servoPins[i]); // servo setup
        Servos[i].write(servoPosSafeStart[i]);
    }
}

void resetArduino()
{
    asm volatile(" jmp 0");
}

void variablesPredet()
{   
    HMG = 34;                               //Posicion Home delServomotor
    SR = 45;                                //Posicion rotular del Servomotor
    V_PT = 90;                              //Velocidad Media del motor del S.R
    V_RT = 180;                             //Velocidad Alta del motor del S.R
    stepsYHomeToPickTube = 9000;           //Numero de pasos de eje Z para bajar a recoger tubo en lineas
    stepsYHomeToReleaseTube = 7000;         //Numero de pasos de eje Z para bajar a dejar tubo en S.R
    stepsXCalibrateLineX = -500;            //Numero de pasos para centrar el CNC en las lineas de la gradilla
    stepsXLine1 = 12000;                    //Numero de pasos que se debe mover el eje X para llegar a L1
    stepsXLine2 = 14100;                    //Numero de pasos que se debe mover el eje X para llegar a L2
    stepsXLine3 = 16200;                    //Numero de pasos que se debe mover el eje X para llegar a L3
    stepsXLine4 = 18300;                    //Numero de pasos que se debe mover el eje X para llegar a L4
    stepsXCalibrateReleaseTube = -185;      //Numero de pasos para centrar el CNC con el sistema de rotulación cuando el sensor de el eje X esta mal ubicado.
    rpmMaxX = 3500;                         //Valor de RPM maxima para el movimiento del eje X
    rpmMaxY = 3500;                         //Valor de RPM maxima para el movimiento del eje Y
    rpmMediaX = 1000;                       //Valor de RPM media para el movimiento del eje X
    rpmMediaY = 1000;                       //Valor de RPM media para el movimiento del eje Y
    acelerationX = 6000;                    //Valor de aceleración para el motor del eje X
    acelerationY = 6000;                    //Valor de aceleración para el motor del eje Y
}

void vectEnviar()
{
    vectVarIniciales[0] = HMG;                                //Posicion Home delServomotor
    vectVarIniciales[1] = SR;                                 //Posicion rotular del Servomotor
    vectVarIniciales[2] = V_PT;                               //Velocidad Media del motor del S.R
    vectVarIniciales[3] = V_RT;                               //Velocidad Alta del motor del S.R

    vectVarIniciales[4] = stepsYHomeToPickTube;               //Numero de pasos de eje Z para bajar a recoger tubo en lineas
    vectVarIniciales[5] = stepsYHomeToReleaseTube;            //Numero de pasos de eje Z para bajar a dejar tubo en S.R
    vectVarIniciales[6] = stepsXCalibrateLineX;               //Numero de pasos para centrar el CNC en las lineas de la gradilla
    vectVarIniciales[7] = stepsXLine1;                        //Numero de pasos que se debe mover el eje X para llegar a L1
    vectVarIniciales[8] = stepsXLine2;                        //Numero de pasos que se debe mover el eje X para llegar a L2
    vectVarIniciales[9] = stepsXLine3;                        //Numero de pasos que se debe mover el eje X para llegar a L3
    vectVarIniciales[10] = stepsXLine4;                       //Numero de pasos que se debe mover el eje X para llegar a L4
    vectVarIniciales[11] = stepsXCalibrateReleaseTube;        //Numero de pasos para centrar el CNC con el sistema de rotulación cuando el sensor de el eje X esta mal ubicado.
    
    vectVarIniciales[12] = rpmMaxX;                           //Valor de RPM maxima para el movimiento del eje X
    vectVarIniciales[13] = rpmMaxY;                           //Valor de RPM maxima para el movimiento del eje Y
    vectVarIniciales[14] = rpmMediaX;                         //Valor de RPM media para el movimiento del eje X
    vectVarIniciales[15] = rpmMediaY;                         //Valor de RPM media para el movimiento del eje Y
    vectVarIniciales[16] = acelerationX;                      //Valor de aceleración para el motor del eje X
    vectVarIniciales[17] = acelerationY;                      //Valor de aceleración para el motor del eje Y
}

void vectRecebir()
{
    HMG = vectVarIniciales[0];                                //Posicion Home delServomotor
    SR = vectVarIniciales[1];                                 //Posicion rotular del Servomotor
    V_PT = vectVarIniciales[2];                               //Velocidad Media del motor del S.R
    V_RT = vectVarIniciales[3];                               //Velocidad Alta del motor del S.R
    
    stepsYHomeToPickTube = vectVarIniciales[4];               //Numero de pasos de eje Z para bajar a recoger tubo en lineas
    stepsYHomeToReleaseTube = vectVarIniciales[5];            //Numero de pasos de eje Z para bajar a dejar tubo en S.R
    stepsXCalibrateLineX = vectVarIniciales[6];               //Numero de pasos para centrar el CNC en las lineas de la gradilla
    stepsXLine1 = vectVarIniciales[7];                        //Numero de pasos que se debe mover el eje X para llegar a L1
    stepsXLine2 = vectVarIniciales[8];                        //Numero de pasos que se debe mover el eje X para llegar a L2
    stepsXLine3 = vectVarIniciales[9];                        //Numero de pasos que se debe mover el eje X para llegar a L3
    stepsXLine4 = vectVarIniciales[10];                       //Numero de pasos que se debe mover el eje X para llegar a L4
    stepsXCalibrateReleaseTube = vectVarIniciales[11];        //Numero de pasos para centrar el CNC con el sistema de rotulación cuando el sensor de el eje X esta mal ubicado.

    rpmMaxX = vectVarIniciales[12];                           //Valor de RPM maxima para el movimiento del eje X
    rpmMaxY = vectVarIniciales[13];                           //Valor de RPM maxima para el movimiento del eje Y
    rpmMediaX = vectVarIniciales[14];                         //Valor de RPM media para el movimiento del eje X
    rpmMediaY = vectVarIniciales[15];                         //Valor de RPM media para el movimiento del eje Y
    acelerationX = vectVarIniciales[16];                      //Valor de aceleración para el motor del eje X
    acelerationY = vectVarIniciales[17];                      //Valor de aceleración para el motor del eje Y
}