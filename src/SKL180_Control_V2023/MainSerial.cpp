#include "MainSerial.h"
void variablesPredet();
void vectEnviar();
void vectRecebir();

// MÉTODO PARA LEER BUFFER DE SERIAL
void MainSerial::conect() {
    if (Serial.available()) {
        readC = Serial.read();
        //Serial.print(readC);
        if (readC == 64) {
            cnt_in = 0;
            cmd = "";
        } else if (readC != 38) { // Recibe y almacena los caracteres desde el ultimo hasta que uart_rx es '&'
            buffer[cnt_in] = readC; // Almacena en vector externo bufferin posicion contrx el caracter uart_rx recibido
            cnt_in += 1;            // Aumenta la variable externa tipo entera cnt para guardar en la siguiente posicion del vector el dato
        } else {
            flag_rx = true; // Bandera de Recepcion Uart BT
            for (int i = 0; i < cnt_in; i++) {
                // Serial.println(i);
                cmd = cmd + buffer[i];
            }
            // Serial.println("CMD_: "+cmd);
        }
        if (flag_rx == true) {
            Run(cmd);
        }
    }
}

// MÉTODO PARA PROCESAMIENTO COMANDOS USUARIO (SERIAL)
void MainSerial::Run(String cmd) {

    //Comando que informa que las variables van a ser modificadas y se espera que llegue el vector
    if (cmd == "solicitarVar") {
        Serial.println("...En espera de las variables a modificar...");
        variableSolicitar = 1;
        while(variableSolicitar == 1)
        {
            MainSerialVectorAux.serialEvent();
        }
        vectRecebir();
        EpromAux.guardarEEPROMPredet();
        Serial.println("Las variables de movimiento han sido modificadas");
        variableSolicitar = 0;
    }

    //Comando para iniciar variables predeterminadamente
    if (cmd == "varPred") {
        Serial.println("Las variables de movimiento se encuentran en configuracion predeterminada");
        variablesPredet();
        EpromAux.guardarEEPROMPredet();
    }

    //Comando que se encarga de mostrar o enviar las variables de movimiento
    if (cmd == "vecEnviar") {
        Serial.println("Enviando las variables de movimiento");
        EpromAux.leerEEPROMPredet();
        vectEnviar();
        String txt = "";
        String coma = ",";
        for (int i=0; i<=17; i++)
        {
            txt+=vectVarIniciales[i] + coma;
        }
        int longitugVectorIOT;
        longitugVectorIOT = txt.length();
        txt = txt.substring(0,longitugVectorIOT-1);
        Serial.print("[");
        Serial.print(txt);
        Serial.println("]");
    } 

    if (cmd == "PostVecVar") {
        Serial.println("API REST - Enviando las variables de movimiento mediante Post");
        EpromAux.leerEEPROMPredet();
        vectEnviar();
        postHttpAux.postW5100();
    }

    if (cmd == "GetVecVar") {
        Serial.println("API REST - Obteniendo las variables de movimiento mediante Get");
        getHttpAux.getW5100();
        // EpromAux.guardarEEPROMPredet();
        // Serial.println("Las variables de movimiento han sido modificadas");
    } 

    //Comando para monitorear el estado de los sensores
    if (cmd == "init") {
        estadoSensoresAux.monitoreoVectorEstadoSistema();
        EEPROM.get(500, contaTubosL1);
        EEPROM.get(510, contaTubosL2);
        EEPROM.get(520, contaTubosL3);
        EEPROM.get(530, contaTubosL4);

        if(contaTubosL1 <= 1 || contaTubosL2 <= 1 || contaTubosL3 <= 1 || contaTubosL4 <= 1)
        {    
            contaTubosL1 = 30;
            contaTubosL2 = 30;
            contaTubosL3 = 30;
            contaTubosL4 = 30;
            EEPROM.put(500, contaTubosL1);
            EEPROM.put(510, contaTubosL2);
            EEPROM.put(520, contaTubosL3);
            EEPROM.put(530, contaTubosL4);
        }
        init1 = 1;
        //rutinas.varIOT[0] = 1;
        //rutinas.procesoIOT();
    }
    
    //En el siguiente if se realiza un nuevo monitoreo cada vez que se termina un proceso de clasificacion de tubos sin errores
    //Se realiza para que quede el funcionamiento quede del equipo se realice ciclico sin necesidad de enviar init para iniciar un proceso
    if(init1 == 1 && varSensoresOk == 2)
    {
        //Serial.println("-----Inicio Nuevo Testo-----");
        estadoSensoresAux.monitoreoVectorEstadoSistema();
    }

    //Comando para ver el historial de fallos del equipo
    if (cmd == "hist") {
        rutinas.verHistorialFallos();
    }

    //Comando para ver el ultimo fallo del equipo
    if (cmd == "ultfal") {
        rutinas.ultimoFallo();
    }
    
    //Comando para ver el estado de los contadores
    if (cmd == "conts") {
        rutinas.verContadores();
    }
    
    //Comando para limpiar la memoria eeprom y asignarle a cada posicion un valor de cero
    if (cmd == "clreeprom") {
        Serial.println("...Espere un instante estamos restableciendo los valores de la memoria...");
        EpromAux.borrarEEPROM();
        Serial.println("Registros de memoria limpios");
    }
     
    //Comando para ver cuales son los sensores habilitados y deshabilitados de el equipo
    if (cmd == "senhab") {
        rutinas.monitorearSensoresHabilitados();
    }

    //Comando para deshabilitar el sensor de llenado de tubos de gradilla L1
    if (cmd == "SGL1 OFF") {
        Serial.println("Sensor llenado gradilla L1 deshabilitado");
        varSO1 = 1;
        EEPROM.put(600, varSO1);
    }
    
    //Comando para habilitar el sensor de llenado de tubos de gradilla L1
    else if (cmd == "SGL1 ON") {
        Serial.println("Sensor llenado gradilla L1 habilitado");
        varSO1 = 0;
        EEPROM.put(600, varSO1);
    }

    //Comando para para deshabilitar el sensor de llenado de tubos de gradilla L2
    if (cmd == "SGL2 OFF") {
        Serial.println("Sensor llenado gradilla L2 deshabilitado");
        varSO2 = 1;
        EEPROM.put(610, varSO2);
    }
    
    //Comando para habilitar el sensor de llenado de tubos de gradilla L2
    else if (cmd == "SGL2 ON") {
        Serial.println("Sensor llenado gradilla L2 habilitado");
        varSO2 = 0;
        EEPROM.put(610, varSO2);
    }
    
    //Comando para para deshabilitar el sensor de llenado de tubos de gradilla L3
    if (cmd == "SGL3 OFF") {
        Serial.println("Sensor llenado gradilla L3 deshabilitado");
        varSO3 = 1;
        EEPROM.put(620, varSO3);
    }
    
    //Comando para habilitar el sensor de llenado de tubos de gradilla L3
    else if (cmd == "SGL3 ON") {
        Serial.println("Sensor llenado gradilla L3 habilitado");
        varSO3 = 0;
        EEPROM.put(620, varSO3);
    }
    
    //Comando para para deshabilitar el sensor de llenado de tubos de gradilla L4
    if (cmd == "SGL4 OFF") {
        Serial.println("Sensor llenado gradilla L4 deshabilitado");
        varSO4 = 1;
        EEPROM.put(630, varSO4);
    }
    
    //Comando para habilitar el sensor de llenado de tubos de gradilla L4
    else if (cmd == "SGL4 ON") {
        Serial.println("Sensor llenado gradilla L4 habilitado");
        varSO4 = 0;
        EEPROM.put(630, varSO4);
    }

    //Comando para deshabilitar el sensor de tapa del sistema de rotulacion
    if (cmd == "SSR1 OFF") {
        Serial.println("Sensor de tapa SR deshabilitado");
        varSO7 = 1;
        EEPROM.put(660, varSO7);
    }
    
    //Comando para habilitar el sensor tapa del sistema de rotulacion
    else if (cmd == "SSR1 ON") {
        Serial.println("Sensor de tapa SR habilitado");
        varSO7 = 0;
        EEPROM.put(660, varSO7);
    }
    
    //Comando para deshabilitar el sensor de posicionamiento (entre rodillos) del sistema de rotulacion
    if (cmd == "SSR2 OFF") {
        Serial.println("Sensor posicion 2 (entre rodillos) SR deshabilitado");
        varSO6 = 1;
        EEPROM.put(650, varSO6);
    }
    
    //Comando para habilitar el sensor de posicionamiento (entre rodillos) del sistema de rotulacion
    else if (cmd == "SSR2 ON") {
        Serial.println("Sensor posicion 2 (entre rodillos) SR habilitado");
        varSO6 = 0;
        EEPROM.put(650, varSO6);
    }

    //Comando para deshabilitar el sensor de posicionamiento (extremo) del sistema de rotulacion
    if (cmd == "SSR3 OFF") {
        Serial.println("Sensor posicion 1 (extremo) SR deshabilitado");
        varSO5 = 1;
        EEPROM.put(640, varSO5);
    }
    
    //Comando para habilitar el sensor de posicionamiento (extremo) del sistema de rotulacion
    else if (cmd == "SSR3 ON") {
        Serial.println("Sensor posicion 1 (extremo) SR habilitado");
        varSO5 = 0;
        EEPROM.put(640, varSO5);
    }

    //Comando para deshabilitar los sensores de posicionamiento del sistema de rotulacion
    if (cmd == "SSRPOS OFF") {
        Serial.println("Sensores de posicionamiento de SR deshabilitados");
        varSSR = 1;
        EEPROM.put(750, varSSR);
        varSO5 = 1;
        EEPROM.put(640, varSO5);
        varSO6 = 1;
        EEPROM.put(650, varSO6);
    }
    
    //Comando para habilitar el sensor de posicionamiento del sistema de rotulacion
    else if (cmd == "SSRPOS ON") {
        Serial.println("Sensores de posicionamiento de SR habilitados");
        varSSR = 0;
        EEPROM.put(750, varSSR);
        varSO5 = 0;
        EEPROM.put(640, varSO5);
        varSO6 = 0;
        EEPROM.put(650, varSO6);
    }

    //Comando para deshabilitar el sensor optico #8
    if (cmd == "SO8 OFF") {
        Serial.println("Sensor optico 8 deshabilitado");
        varSO8 = 1;
        EEPROM.put(670, varSO8);
    }
    
    //Comando para habilitar el sensor optico #8
    else if (cmd == "SO8 ON") {
        Serial.println("Sensor optico 8 habilitado");
        varSO8 = 0;
        EEPROM.put(670, varSO8);
    }

    //Comando para deshabilitar el sensor de home del eje X
    if (cmd == "SCNCX OFF") {
        Serial.println("Sensor Home eje X deshabilitado");
        varSH1 = 1;
        EEPROM.put(680, varSH1);
    }
    
    //Comando para habilitar el sensor de home del eje X
    else if (cmd == "SCNCX ON") {
        Serial.println("Sensor Home eje X habilitado");
        varSH1 = 0;
        EEPROM.put(680, varSH1);
    }

    //Comando para deshabilitar el sensor de home del eje Y
    if (cmd == "SCNCY OFF") {
        Serial.println("Sensor Home eje Y deshabilitado");
        varSH2 = 1;
        EEPROM.put(690, varSH2);
    }
    
    //Comando para habilitar el sensor de home del eje Y
    else if (cmd == "SCNCY ON") {
        Serial.println("Sensor Home eje Y habilitado");
        varSH2 = 0;
        EEPROM.put(690, varSH2);
    }

    //Comando para deshabilitar el sensor de L1
    if (cmd == "SL1 OFF") {
        Serial.println("Sensor Ir a L1 deshabilitado");
        varSH3 = 1;
        EEPROM.put(700, varSH3);
    }
    
    //Comando para habilitar el sensor de L1
    else if (cmd == "SL1 ON") {
        Serial.println("Sensor Ir a L1 habilitado");
        varSH3 = 0;
        EEPROM.put(700, varSH3);
    }

    //Comando para deshabilitar el sensor de L2
    if (cmd == "SL2 OFF") {
        Serial.println("Sensor Ir a L2 deshabilitado");
        varSH4 = 1;
        EEPROM.put(710, varSH4);
    }
    
    //Comando para habilitar el sensor de L2
    else if (cmd == "SL2 ON") {
        Serial.println("Sensor Ir a L2 habilitado");
        varSH4 = 0;
        EEPROM.put(710, varSH4);
    }

    //Comando para deshabilitar el sensor de L3
    if (cmd == "SL3 OFF") {
        Serial.println("Sensor Ir a L3 deshabilitado");
        varSH5 = 1;
        EEPROM.put(720, varSH5);
    }
    
    //Comando para habilitar el sensor de L3
    else if (cmd == "SL3 ON") {
        Serial.println("Sensor Ir a L3 habilitado");
        varSH5 = 0;
        EEPROM.put(720, varSH5);
    }

    //Comando para deshabilitar el sensor de L4
    if (cmd == "SL4 OFF") {
        Serial.println("Sensor Ir a L4 deshabilitado");
        varSH6 = 1;
        EEPROM.put(730, varSH6);
    }
    
    //Comando para habilitar el sensor de L4
    else if (cmd == "SL4 ON") {
        Serial.println("Sensor Ir a L4 habilitado");
        varSH6 = 0;
        EEPROM.put(730, varSH6);
    }

    //Comando para deshabilitar el sensor del gripper
    if (cmd == "SGPR OFF") {
        Serial.println("Sensor gripper deshabilitado");
        varSGPR = 1;
        EEPROM.put(760, varSGPR);
        varSH7 = 1;
        EEPROM.put(740, varSH7);
    }
    
    //Comando para habilitar el sensor del gripper
    else if (cmd == "SGPR ON") {
        Serial.println("Sensor gripper habilitado");
        varSGPR = 0;
        EEPROM.put(760, varSGPR);
        varSH7 = 0;
        EEPROM.put(740, varSH7);
    }

    //Comando para deshabilitar todos los sensores del equipo
    if (cmd == "ALLSKL180 OFF") {
        Serial.println("Todos los sensores del SKL180 estan deshabilitados");
        varSO1 = 1;
        EEPROM.put(600, varSO1);
        varSO2 = 1;
        EEPROM.put(610, varSO2);
        varSO3 = 1;
        EEPROM.put(620, varSO3);
        varSO4 = 1;
        EEPROM.put(630, varSO4);
        varSO7 = 1;
        EEPROM.put(660, varSO7);
        varSO6 = 1;
        EEPROM.put(650, varSO6);
        varSO5 = 1;
        EEPROM.put(640, varSO5);
        varSSR = 1;
        EEPROM.put(750, varSSR);
        varSO5 = 1;
        EEPROM.put(640, varSO5);
        varSO6 = 1;
        EEPROM.put(650, varSO6);
        varSO8 = 1;
        EEPROM.put(670, varSO8);
        varSH1 = 1;
        EEPROM.put(680, varSH1);
        varSH2 = 1;
        EEPROM.put(690, varSH2);
        varSH3 = 1;
        EEPROM.put(700, varSH3);
        varSH4 = 1;
        EEPROM.put(710, varSH4);
        varSH5 = 1;
        EEPROM.put(720, varSH5);
        varSH6 = 1;
        EEPROM.put(730, varSH6);
        varSGPR = 1;
        EEPROM.put(760, varSGPR);
        varSH7 = 1;
        EEPROM.put(740, varSH7);
    }
    
    //Comando para habilitar todos los sensores del equipo
    else if (cmd == "ALLSKL180 ON") {
        Serial.println("Todos los sensores del SKL180 estan habilitados");
        varSO1 = 0;
        EEPROM.put(600, varSO1);
        varSO2 = 0;
        EEPROM.put(610, varSO2);
        varSO3 = 0;
        EEPROM.put(620, varSO3);
        varSO4 = 0;
        EEPROM.put(630, varSO4);
        varSO7 = 0;
        EEPROM.put(660, varSO7);
        varSO6 = 0;
        EEPROM.put(650, varSO6);
        varSO5 = 0;
        EEPROM.put(640, varSO5);
        varSSR = 0;
        EEPROM.put(750, varSSR);
        varSO5 = 0;
        EEPROM.put(640, varSO5);
        varSO6 = 0;
        EEPROM.put(650, varSO6);
        varSO8 = 0;
        EEPROM.put(670, varSO8);
        varSH1 = 0;
        EEPROM.put(680, varSH1);
        varSH2 = 0;
        EEPROM.put(690, varSH2);
        varSH3 = 0;
        EEPROM.put(700, varSH3);
        varSH4 = 0;
        EEPROM.put(710, varSH4);
        varSH5 = 0;
        EEPROM.put(720, varSH5);
        varSH6 = 0;
        EEPROM.put(730, varSH6);
        varSGPR = 0;
        EEPROM.put(760, varSGPR);
        varSH7 = 0;
        EEPROM.put(740, varSH7);
    }

    //Comando para accionar el gripper
    if (cmd == "hmgrp") {
        rutinas.griperClose();
        delay(300);
        rutinas.griperOpen();
        Delay.start(2600);
        rutinas.griperClose();
        Delay.start(2600);
        pinMode(gripClose, LOW);
        rutinas.griperOpen();
        //Serial.print(cabecera + "GROK" + fintrama);
    }

    //Comando para accionar el servo y ubicarlo en posicion ZRO o retraer el brazo y no presionar el tubo
    if (cmd == "sv0") {
        pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
        Servos[0].write(ZRO);
        delay(600);
        pinMode(servoMotorOn, INPUT); // APAGO MOTOR
        delay(200);

        lecturaSensoresAux.deteccionSensores();
        if(lecturaSensoresAux.varIOTSensores[7] == 1)
        {
            String String_ZRO = String(ZRO);
            Serial.print(cabecera + String_ZRO + fintrama);
        }
        else if(lecturaSensoresAux.varIOTSensores[7] == 0)
        {
            Serial.print("Error revisar servo");
        }
    } 

    //Comando para accionar el servo y ubicarlo en posicion SR o presionar el tubo
    if (cmd == "sr") {
        pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
        Servos[0].write(SR);
        delay(600);
        pinMode(servoMotorOn, INPUT); // APAGO MOTOR
        String String_SR = String(SR);
        Serial.println(cabecera + String_SR + fintrama);
        // Serial.print(SR,DEC);
    } 
    
    //Comando para accionar el servo y ubicarlo en posicion HMG o home
    if (cmd == "hm") {
        pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
        Servos[0].write(HMG);
        delay(600);
        pinMode(servoMotorOn, INPUT); // APAGO MOTOR
        delay(200);
        String String_HM = String(HMG);
        Serial.println(cabecera + String_HM + fintrama);
    } 

    //Comando para reiniciar el contador de tubos de L1 de la gradilla
    if (cmd == "RL1") {
        Serial.println("Reiniciando contador gradilla L1");
        EEPROM.get(500, contaTubosL1);
        contaTubosL1 = 30;
        EEPROM.put(500, contaTubosL1);
    } 
    
    //Comando para reiniciar el contador de tubos de L2 de la gradilla
    if (cmd == "RL2") {
        Serial.println("Reiniciando contador gradilla L2");
        EEPROM.get(510, contaTubosL2);
        contaTubosL2 = 30;
        EEPROM.put(510, contaTubosL2);
    } 
    
    //Comando para reiniciar el contador de tubos de L3 de la gradilla
    if (cmd == "RL3") {
        Serial.println("Reiniciando contador gradilla L3");
        EEPROM.get(520, contaTubosL3);
        contaTubosL3 = 30;
        EEPROM.put(520, contaTubosL3);
    } 
    
    //Comando para reiniciar el contador de tubos de L4 de la gradilla
    if (cmd == "RL4") {
        Serial.println("Reiniciando contador gradilla L4");
        EEPROM.get(530, contaTubosL4);
        contaTubosL4 = 30;
        EEPROM.put(530, contaTubosL4);
    } 

    //Comando para accionar el motor haciéndolo girar hacia la izquierda lado mediante el pin referente a motor_rotulado_a
    if (cmd == "m2a") {
        analogWrite(motor_rotulado_a, V_RT);
        delay(5000);
        analogWrite(motor_rotulado_a, 0);
        Serial.print("@OK&");
    } 
    
    //Comando para accionar el motor haciéndolo girar hacia la derecha lado mediante el pin referente a motor_rotulado_b a velocidad media
    if (cmd == "m2bPT") {
        analogWrite(motor_rotulado_b, V_PT);
        delay(5000);
        analogWrite(motor_rotulado_b, 0);
        Serial.print("@OK&");
    } 
    //Comando para accionar el motor haciéndolo girar hacia la derecha lado mediante el pin referente a motor_rotulado_b a velocidad alta
    if (cmd == "m2bRT") {
        analogWrite(motor_rotulado_b, V_RT);
        delay(5000);
        analogWrite(motor_rotulado_b, 0);
        Serial.print("@OK&");
    } 

    //Comando para verificar el funcionamiento de la comunicacion
    if (cmd == "H") {
        Serial.println("hola");
    }
    
    flag_rx = false;

    //En el siguiente if se evalua el estado de los sistemas de los sensores
    //Si los sensores estan bien recibe los comandos de funcionamiento de lo contrario no
    if(estadoSensoresAux.estadoSistema[0] == 1 && estadoSensoresAux.estadoSistema[1] == 1 && estadoSensoresAux.estadoSistema[2] == 1)
    {
        varSensoresOk = 1;

        //Comando para realizar la rutina de recoger tubo y devolverlo a L1
        if (cmd == "loopl1") {
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_prueba.RecogerYDevolverTubo("L1");
        } 
        
        //Comando para realizar la rutina de recoger tubo y devolverlo a L2
        else if (cmd == "loopl2") {
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_prueba.RecogerYDevolverTubo("L2");
        } 
        
        //Comando para realizar la rutina de recoger tubo y devolverlo a L3
        else if (cmd == "loopl3") {
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_prueba.RecogerYDevolverTubo("L3");
        }

        //Comando para realizar la rutina de recoger tubo y devolverlo a L4
        else if (cmd == "loopl4") {
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_prueba.RecogerYDevolverTubo("L4");
        } 
        
        //Comando para ir a L1 a recoger tubo (rutina de funcionamiento)
        else if (cmd == "l1") {
            rutinas.RecogerTubo("L1");
            varPrueba = 1;
        }
        
        //Comando para ir a L1 a recoger tubo (rutina de funcionamiento)
        else if (cmd == "l2") {
            rutinas.RecogerTubo("L2");
            varPrueba = 1;
        }
        
        //Comando para ir a L1 a recoger tubo (rutina de funcionamiento)
        else if (cmd == "l3") {
            rutinas.RecogerTubo("L3");
            varPrueba = 1;
        } 
        
        //Comando para ir a L1 a recoger tubo (rutina de funcionamiento)
        else if (cmd == "l4") {
            rutinas.RecogerTubo("L4");
            varPrueba = 1;
        } 
        
        //Comando para realizar  rutinas de prueba para L1 (rutina de prueba)
        else if (cmd == "L1") {
            rutinas_p.LiberarTubo();
            delay(400);
            rutinas_p.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_p.RecogerTubo("L1");
            varPrueba = 0;
        } 
        
        //Comando para realizar  rutinas de prueba para L2 (rutina de prueba)
        else if (cmd == "L2") {
            rutinas_p.LiberarTubo();
            delay(400);
            rutinas_p.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_p.RecogerTubo("L2");
            varPrueba = 0;
        } 
        
        //Comando para realizar  rutinas de prueba para L3 (rutina de prueba)
        else if (cmd == "L3") {
            rutinas_p.LiberarTubo();
            delay(400);
            rutinas_p.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_p.RecogerTubo("L3");
            varPrueba = 0;
        } 
        
        //Comando para realizar  rutinas de prueba para L4 (rutina de prueba)
        else if (cmd == "L4") {
            rutinas_p.LiberarTubo();
            delay(400);
            rutinas_p.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_p.RecogerTubo("L4");
            varPrueba = 0;
        } 
        
        //Comando para liberar el tubo del sistema de rotulacion
        else if (cmd == "lb") {
            rutinas.LiberarTubo();
            Servos[0].write(SL);
            String String_SL = String(SL);
            Serial.print(cabecera + String_SL + fintrama);
            Serial.print("@OK&");
        } 
                
        //Comando para liberar tubo del sistema de rotulación
        else if (cmd == "svlb") {
            rutinas.LiberarTubo();
            Serial.print("@OK&");
        } 
        
        //Comando para presentar el estado de la maquina
        else if (cmd == "?est") {
            rutinas.procesoIOT();

            /*
            String String_EST = " HM: " + String(HMG) + "SR: " + String(SR) + "HM: " + String(HMG) + "LB: " + String(SL) + "\n" 
            + " l1: " + String(vlr_sensor_ln1) + " l2: " + String(vlr_sensor_ln2) + " l3: " + String(vlr_sensor_ln3) + " l4: " + String(vlr_sensor_ln4) + "\n" 
            + " SensorHmX: " + String(e_endX) + " SensorHmY: " + String(e_endY) + " SensorTubo: " + String(vlr_sensor_tubo);
            Serial.println(cabecera + String_EST + fintrama);*/
        }
                
        //Comando para posicionar el tubo en el sistema de rotulacion
        else if (cmd == "pt") {
            //rutinas.RotularTubo();
            rutinas_p.PosicionarTubo();
            Serial.print(cabecera + rta + fintrama);
            // Serial.print("@PT&");
        } 
        
        //Comando liberar el tubo ya posicionado en el sistema de rotulación
        else if (cmd == "rt") {
            if(varPrueba == 1)
            {
                if (RTD == 1) {
                //rutinas.Rotulado();
                rutinas.Rotulado();
                } else {
                    rutinas.LiberarTubo();
                }
                // Serial.print(cabecera+"OK"+fintrama);
                //Serial.print("@OK&");
                
                estadoSensoresAux.estadoSistema[0] = 0;
                estadoSensoresAux.estadoSistema[1] = 0;
                estadoSensoresAux.estadoSistema[2] = 0;
                varSensoresOk = 2;
            }

            else if(varPrueba == 0)
            {
                if (RTD == 1) {
                //rutinas.Rotulado();
                rutinas_p.RotularTubo();
                } else {
                    rutinas_p.LiberarTubo();
                }
                // Serial.print(cabecera+"OK"+fintrama);
                Serial.print("@OK&");
            }
        } 
        
        //Comando para que variable RTD adquiera el valor de 1
        else if (cmd == "rton") {
            RTD = 1;
            EEPROM.write(26, RTD);
            Serial.print("@OK&");
        } 
        
        //Comando para que variable RTD adquiera el valor de 0
        else if (cmd == "rtof") {
            RTD = 0;
            EEPROM.write(26, RTD);
            Serial.print("@OK&");
        }                
        flag_rx = false;
    }
}
