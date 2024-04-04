#include "Rutinas.h"

void resetArduino();

// MÉTODO PARA RUTINA PRINCIPAL SKL-180 (RECOGER TUBO EN LINEA Y DEJARLO EN SISTEMA ROTULACION)
void Rutinas::RecogerTubo(String VLinea)
{   
    bool HMGl1 = false;
    bool HMGl2 = false;
    bool HMG21 = false;
    bool HMG22 = false;
    bool MVl1 = false;
    bool varSinRot = 0;
    
    lecturaSensoresAux.deteccionSensores();
    if(lecturaSensoresAux.varIOTSensores[14] == 0 || varSGPR == 1)
    {
        int sensor_lineaX = sensor_linea1;
        if (VLinea == "L1" or VLinea == "L2" or VLinea == "L3" or VLinea == "L4")
        {
            EProm.leerInit();
            varIOT[0] = cliente;
            Serial.print(varIOT[0]);
            Serial.print(",");
            varIOT[1] = version;
            Serial.print(varIOT[1]);
            Serial.print(",");
            varIOT[2] = "1";
            Serial.print(varIOT[2]);
            Serial.print(",");
            
            pinMode(servoMotorOn, OUTPUT);
            delay(250);
            Servos[0].write(ZRO);
            delay(250);
            pinMode(servoMotorOn, INPUT);       
            
            // lecturaSensoresAux.deteccionSensores();
            // if(lecturaSensoresAux.varIOTSensores[7] == 1)
            // {
            //     Serial.print("Servo en Home..!");
            // }
            // else if(lecturaSensoresAux.varIOTSensores[7] == 0)
            // {
            //     Serial.print("Error revisar servo");
            //     resetArduino();
            // }

            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[4] == 1 || lecturaSensoresAux.varIOTSensores[5] == 1 || lecturaSensoresAux.varIOTSensores[6] == 1)
            {
                pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
                Servos[0].write(SR); // Fija la posicion del servo de acuerdo al valor definido
                delay(100);
                analogWrite(motor_rotulado_b, V_RT);
                delay(750);
                Servos[0].write(SL);
                delay(200);
                analogWrite(motor_rotulado_b, 0);
                delay(200);
                // Servos[0].write(HMG);
                pinMode(servoMotorOn, INPUT); // APAGO MOTOR    
            }
            
            //Servomotor sin tubo IOT
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[4] == 0 && lecturaSensoresAux.varIOTSensores[5] == 0 && lecturaSensoresAux.varIOTSensores[6] == 0){
            varIOT[3] = 1;
            Serial.print(varIOT[3]);
            Serial.print(",");
            }
            else if(lecturaSensoresAux.varIOTSensores[4] == 1 || lecturaSensoresAux.varIOTSensores[5] == 1 || lecturaSensoresAux.varIOTSensores[6] == 1){
                varIOT[3] = "0";
                for (int i=4; i<=11; i++)
                {
                    varIOT[i] = "-";
                }
                stopIOT();
            }
        
            griperOpen();
            griperClose();
            griperOpen();
            if (encendidoMaquina) {
            encendidoMaquina = false;
            }
            
            t_reset = millis();
            flag_time = true;
            int line = VLinea.substring(1).toInt();
            int stepsXLineX = stepsXLine1;
            switch (line)
            {
            case 1:
            sensor_lineaX = sensor_linea1;
            stepsXLineX = stepsXLine1;
            varIOT[4] = "1";
            Serial.print(varIOT[4]);
            Serial.print(",");
            goToL1 = 1;
            goToL2 = 0;
            goToL3 = 0;
            goToL4 = 0;
            break;
            case 2:
            sensor_lineaX = sensor_linea2;
            stepsXLineX = stepsXLine2;
            varIOT[4] = "2";
            Serial.print(varIOT[4]);
            Serial.print(",");
            goToL1 = 0;
            goToL2 = 1;
            goToL3 = 0;
            goToL4 = 0;
            break;
            case 3:
            sensor_lineaX = sensor_linea3;
            stepsXLineX = stepsXLine3;
            varIOT[4] = "3";
            Serial.print(varIOT[4]);
            Serial.print(",");
            goToL1 = 0;
            goToL2 = 0;
            goToL3 = 1;
            goToL4 = 0;
            break;
            case 4:
            sensor_lineaX = sensor_linea4;
            stepsXLineX = stepsXLine4;
            varIOT[4] = "4";
            Serial.print(varIOT[4]);
            Serial.print(",");
            goToL1 = 0;
            goToL2 = 0;
            goToL3 = 0;
            goToL4 = 1;
            break;
            }

            // LLEVANDO X A LINEA
            //Serial.println("Llevando X a linea");
            stepperAX.estadoHomePasos(false);
            stepperAX.actualPasos = stepsXLineX;
            stepperAX.dirHome = not stepperAX.dirHome;
            stepperAX._pinFinCarrera = sensor_lineaX;
            stepperAX.cambiarRpmActualMotor(rpmMaxX);
            stepperAX.homeMotorFin();
            /*while(stepperAX.home) {
                stepperAX.procesarCNC();
                stepperAX.control();
            }*/

            while(stepperAX.home) {
                if(not digitalRead(sensor_linea1) || not digitalRead(sensor_linea2) || not digitalRead(sensor_linea3) || not digitalRead(sensor_linea4))
                {
                    lecturaSensoresAux.deteccionSensores();
                    bool condicionOn1 = 0;
                    unsigned long tempoOn1 = millis();
                    while(condicionOn1 == 0)
                    {
                        if (not stepperAX.home && lecturaSensoresAux.varIOTSensores[10] == 0 && lecturaSensoresAux.varIOTSensores[11] == 0 && lecturaSensoresAux.varIOTSensores[12] == 0 && lecturaSensoresAux.varIOTSensores[13] == 0)
                        {
                            condicionOn1 = 1;
                        }
                        if(millis() - tempoOn1 >= 10000)
                        {
                            varIOT[5] = "0";
                            Serial.print(varIOT[5]);
                            stopIOT();
                        }
                        stepperAX.procesarCNC();
                        stepperAX.control();
                    }
                }
            }

            stepperAX.estadoHomePasos(true);
            stepperAX.actualPasos = (stepsXLineX-stepperAX.actualPasos);
            stepperAX.dirHome = not stepperAX.dirHome;
            stepperAX._pinFinCarrera = X_MIN_PIN;

            //CNC en Linea IOT
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[10] == 1 || lecturaSensoresAux.varIOTSensores[11] == 1 || lecturaSensoresAux.varIOTSensores[12] == 1 || lecturaSensoresAux.varIOTSensores[13] == 1){
                varIOT[5] = "1";
                Serial.print(varIOT[5]);
                Serial.print(",");
            }
            else if(lecturaSensoresAux.varIOTSensores[10] == 0 && lecturaSensoresAux.varIOTSensores[11] == 0 && lecturaSensoresAux.varIOTSensores[12] == 0 && lecturaSensoresAux.varIOTSensores[13] == 0){
                varIOT[5] = "0";
                Serial.print(varIOT[5]);
                stopIOT();
            }

            // CALIBRANDO X A CENTRO DE LINEA
            //Serial.println("Calibrando X");
            stepperAX.cambiarRpmActualMotor(rpmMaxX);
            stepperAX.moverMotor(stepperAX.actualPasos + stepsXCalibrateLineX);
            while(stepperAX.estadoMov != 0) {
                stepperAX.procesarCNC();
                stepperAX.control();
            }

            // LLEVANDO Y A RECOGER TUBO
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[14] == 0 || varSGPR == 1)
            {
                //Serial.println("Devolviendo Y a home");
                stepperAY.cambiarRpmActualMotor(rpmMaxY);
                stepperAY.moverMotor(stepsYHomeToPickTube);
                while(stepperAY.estadoMov != 0) {
                    stepperAY.procesarCNC();
                    stepperAY.control();  
                    if(not digitalRead(Y_MIN_PIN))
                    {
                        lecturaSensoresAux.deteccionSensores();
                        bool condicionOn2 = 0;
                        unsigned long tempoOn2 = millis();
                        while(condicionOn2 == 0)
                        {
                            if(stepperAY.estadoMov == 0 && lecturaSensoresAux.varIOTSensores[4] == 0 && lecturaSensoresAux.varIOTSensores[5] == 0 && lecturaSensoresAux.varIOTSensores[6] == 0)
                            {
                                condicionOn2 = 1;
                            }
                            if(millis() - tempoOn2 >= 2500)
                            {
                                varIOT[6] = "0";
                                Serial.print(varIOT[6]);
                                stopIOT();
                            }
                            stepperAY.control();  
                        }
                    }
                }
            }
            
            //CERRANDO GRIPPER
            //Serial.println("Cerrando gripper");
            griperClose();
            //delay(1000);

            //Bajar Z y recoger IOT
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[9] == 0){
                varIOT[6] = "1";
                Serial.print(varIOT[6]);
                Serial.print(",");
            }
            else if(lecturaSensoresAux.varIOTSensores[9] == 1){
                varIOT[6] = "0";
                Serial.print(varIOT[6]);
                stopIOT();
            }
            
            // DEVOLVIENDO Y A HOME
            //Serial.println("Recogiendo tubo");
            stepperAY.estadoPerfilVel(true);
            stepperAY.cambiarRpmActualMotor(rpmMediaY);
            stepperAY.homeMotorFin();
            /*while(stepperAY.home) {
                stepperAY.procesarCNC();
                stepperAY.control();
            }*/
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[14] == 1 || varSGPR == 1)
            {
                //Retorna Z y con tubo IOT
                lecturaSensoresAux.deteccionSensores();
                while(stepperAY.home) {
                    if(not digitalRead(Y_MIN_PIN))
                    {
                        bool condicionOn3 = 0;
                        unsigned long tempoOn3 = millis();
                        while(condicionOn3 == 0)
                        {
                            if (digitalRead(Y_MIN_PIN) && lecturaSensoresAux.varIOTSensores[4] == 0 && lecturaSensoresAux.varIOTSensores[5] == 0 && lecturaSensoresAux.varIOTSensores[6] == 0)
                            {
                                condicionOn3 = 1;
                            }
                            if(millis() - tempoOn3 >= 10000)
                            {
                                varIOT[7] = "0";
                                Serial.print(varIOT[7]);
                                Serial.print("fallo 1");
                                stopIOT();
                            }
                            stepperAY.procesarCNC();
                            stepperAY.control();  
                        }
                    }
                }    
            }
            delay(3-000);

            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[9] == 1){
                varIOT[7] = "1";
                Serial.print(varIOT[7]);
                Serial.print(",");
            }
            else if(lecturaSensoresAux.varIOTSensores[9] == 0){
                varIOT[7] = "0";
                Serial.print(varIOT[7]);
                Serial.print("fallo 2");
                stopIOT();
            } 
            
            //Serial.println("Devolviendo X a home");
            stepperAX.cambiarRpmActualMotor(rpmMaxX);
            stepperAX.homeMotorFin();
            /*while(stepperAX.home) {
                stepperAX.procesarCNC();
                stepperAX.control();
            }*/

            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[14] == 1 || varSGPR == 1)
            {
                while(stepperAX.home) {
                    if(not digitalRead(X_MIN_PIN))
                    {
                        lecturaSensoresAux.deteccionSensores();
                        bool condicionOn4 = 0;
                        unsigned long tempoOn4 = millis();
                        while(condicionOn4 == 0)
                        {
                            if (not stepperAX.home && lecturaSensoresAux.varIOTSensores[4] == 0 && lecturaSensoresAux.varIOTSensores[5] == 0 && lecturaSensoresAux.varIOTSensores[6] == 0)
                            {
                                condicionOn4 = 1;
                            }
                            if(millis() - tempoOn4 >= 1500)
                            {
                                varIOT[8] = "0";
                                Serial.print(varIOT[8]);
                                stopIOT();
                            }
                            stepperAX.procesarCNC();
                            stepperAX.control();
                        }
                    }
                }    
            }

            //Retorna X y con tubo IOT
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[8] == 1){            
                varIOT[8] = "1";
                Serial.print(varIOT[8]);
                Serial.print(",");
            }
            else if(lecturaSensoresAux.varIOTSensores[8] == 0){
                varIOT[8] = "0";
                Serial.print(varIOT[8]);
                stopIOT();
            }
            
            
            //Moviendo Eje X para calibrar la colocación del tubo
            stepperAX.cambiarRpmActualMotor(rpmMaxX);
            stepperAX.moverMotor(stepsXCalibrateReleaseTube);
            while(stepperAX.estadoMov != 0) {
                stepperAX.control();
            }


            // LLEVANDO Y A DEJAR TUBO
            //Serial.println("Dejando tubo");
            stepperAY.cambiarRpmActualMotor(rpmMaxY);
            stepperAY.moverMotor(stepsYHomeToReleaseTube);
            /*while(stepperAY.estadoMov != 0) {
                stepperAY.control();
            }*/
            
            //BAJAR A DEJAR TUBO
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[14] == 1 || varSGPR == 1)
            {
                while(stepperAY.estadoMov != 0) {
                    stepperAY.control();  
                    if(not digitalRead(Y_MIN_PIN))
                    {
                        bool condicionOn5 = 0;
                        unsigned long tempoOn5 = millis();
                        while(condicionOn5 == 0)
                        {
                            if(stepperAY.estadoMov == 0)
                            {
                                condicionOn5 = 1;
                            }
                            if(millis() - tempoOn5 >= 2500)
                            {
                                varIOT[9] = "0";
                                Serial.print(varIOT[9]);
                                stopIOT();
                            }
                            stepperAY.control();  
                        }
                    }
                }
            }

            //Baja Z a dejar tubo IOT
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[9] == 0){            
                varIOT[9] = "1";
                Serial.print(varIOT[9]);
                Serial.print(",");
            }
            else if(lecturaSensoresAux.varIOTSensores[9] == 1){
                varIOT[9] = "0";
                Serial.print(varIOT[9]);
                stopIOT();
            } 

            //Servo sostiene tubo en SR
            pinMode(servoMotorOn, OUTPUT); 
            delay(250);
            Servos[0].write(ZRO);
            delay(250);
            pinMode(servoMotorOn, INPUT);
            

            // ABRIENDO GRIPPER
            //Serial.println("Abriendo gripper");
            griperOpen();
            delay(1000);

            // DEVOLVIENDO Y A HOME
            //Serial.println("Devolviendo Y a home");
            stepperAY.cambiarRpmActualMotor(rpmMaxY);
            stepperAY.homeMotorFin();
            /*while(stepperAY.home) {
                stepperAY.procesarCNC();
                stepperAY.control();
            }*/
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[14] == 0 || varSGPR == 1)
            {
                while(stepperAY.home) {
                    if(not digitalRead(Y_MIN_PIN))
                    {
                        bool condicionOn6 = 0;
                        unsigned long tempoOn6 = millis();
                        while(condicionOn6 == 0)
                        {
                            if (digitalRead(Y_MIN_PIN))
                            {
                                condicionOn6 = 1;
                            }
                            if(millis() - tempoOn6 >= 2500)
                            {
                                varIOT[10] = "0";
                                Serial.print(varIOT[10]);
                                stopIOT();
                            }
                            stepperAY.procesarCNC();
                            stepperAY.control();  
                        }
                    }
                }
            }

            //Devolviendo Eje X A Home
            stepperAX.cambiarRpmActualMotor(rpmMaxX);
            stepperAX.moverMotor(-stepsXCalibrateReleaseTube);
            while(stepperAX.estadoMov != 0) {
                stepperAX.control();
            }
            delay(1000);
            LiberarTubo();
            RecogerTubo("L2");

            //Servo acomoda el tubo cuando entra mal
            pinMode(servoMotorOn, OUTPUT); 
            delay(250);
            Servos[0].write(HMG);
            delay(250);
            pinMode(servoMotorOn, INPUT);
            delay(250);
            pinMode(servoMotorOn, OUTPUT); 
            delay(250);
            Servos[0].write(SR);
            delay(250);
            analogWrite(motor_rotulado_b, V_RT);
            delay(500);
            pinMode(servoMotorOn, INPUT);
            delay(100);
            analogWrite(motor_rotulado_b, 0);
            delay(100);
            pinMode(servoMotorOn, OUTPUT); 
            delay(250);
            Servos[0].write(HMG);
            delay(250);
            pinMode(servoMotorOn, INPUT);
    
            //Retorna Z sin tubo IOT
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[9] == 1){            
                varIOT[10] = "1";
                Serial.print(varIOT[10]);
                Serial.print(",");
            }
            else if(lecturaSensoresAux.varIOTSensores[9] == 0){
                varIOT[10] = "0";
                Serial.print(varIOT[10]);
                stopIOT();
            }
                    
            /*
            // DEVOLVIENDO X A HOME
            if(digitalRead(X_MIN_PIN) == 1)
            {
                //Serial.println("Devolviendo X a home");
                stepperAX.cambiarRpmActualMotor(rpmMaxX);
                stepperAX.homeMotorFin();
                while(stepperAX.home) {
                    stepperAX.procesarCNC();
                    stepperAX.control();
                }
            }
            else{
                //Serial.println("Eje X en Home");
            }
            */
           
            //ROTULAR
            //Serial.print("@DS" + VLinea + "&");
            //RotularTuboCamilo();
            if(varSO5 == 0 && varSSR == 0){
                //Serial.println("S.R. con todos los sensores");
                RotularTubo2Sensores();
            }else if(varSO5 == 1 && varSSR == 0){
                //Serial.println("S.R. con un solo sensor (entre rodillos)");
                RotularTubo1Sensor();
            }else if(varSSR == 1 && varSO5 == 1 && varSO5 == 1){
                //Serial.println("S.R. sin sensores de posicionamiento");
                RotularTuboSinSensores();
            }
        }
    }

    else if(lecturaSensoresAux.varIOTSensores[14] == 1 && varSGPR == 0)
    {
        Serial.println("Error: Tubo en gripper");
    }
}

//Rutina para posicionar tubo de dos sensores
void Rutinas::RotularTubo2Sensores()
{
    pinMode(servoMotorOn, OUTPUT); 
    delay(250);
    Servos[0].write(SR);
    delay(250);
    pinMode(servoMotorOn, INPUT);
    banderaSRFallo = false;
        
    //analogWrite(motor_rotulado_b, V_PT);    
    bool val = false;
    bool val2 = false;
    int valRot = 0;
    cnt_time2 = 0;
    while (valRot == 0)
    {
        lecturaSensoresAux.deteccionSensores();
        if(lecturaSensoresAux.varIOTSensores[6] == 1)
        {
            val = true;
        }
        else if(lecturaSensoresAux.varIOTSensores[6] == 0)
        {
            val = false;
            valRot = 1; 
        }

        if (val)
        {            
            analogWrite(motor_rotulado_b, V_PT);
            flag_time2 = true;
            cnt_time2 = 0;
            int valRot2 = 0;
            while(valRot2 == 0)
            {
                lecturaSensoresAux.deteccionSensores();
                if(lecturaSensoresAux.varIOTSensores[4] == 1){
                    int valRot3 = 0;
                    while(valRot3 == 0)
                    {
                        lecturaSensoresAux.deteccionSensores();
                        if(lecturaSensoresAux.varIOTSensores[5] == 0){
                            valRot2 = 1;
                            valRot3 = 1;
                            analogWrite(motor_rotulado_b, 0);
                            val2 = true;
                        }
                        else if (banderaSRFallo == true)
                        {
                            banderaSRFallo= false;
                            //LiberarTuboSRFallo();
                            //Serial.print("@PT&");
                            Serial.print("@pt1&");
                            valRot2 = 1;
                            valRot3 = 1;
                            valRot = 1;
                            analogWrite(motor_rotulado_b, 0);
                        }
                    }
                }
                else if (banderaSRFallo== true)
                {
                    banderaSRFallo= false;
                    //LiberarTuboSRFallo();
                    //Serial.print("@PT&");
                    Serial.print("@pt2&");
                    valRot2 = 1;
                    valRot = 1;
                    analogWrite(motor_rotulado_b, 0);
                }
            }
            delay(100);
        }

        if (val2)
        {
            analogWrite(motor_rotulado_b, V_PT);
            cnt_time2 = 0;
            int valRot3 = 0;
            while(valRot3 == 0)
            {   
                lecturaSensoresAux.deteccionSensores();
                if(lecturaSensoresAux.varIOTSensores[5] == 1){
                valRot3 = 1;
                valRot = 1;
                analogWrite(motor_rotulado_b, 0);
                //Serial.print("@PT&");
                Serial.print("@pt3&");
                }
                else if (banderaSRFallo== true)
                {
                    banderaSRFallo= false;
                    //LiberarTuboSRFallo();
                    //Serial.print("@PT&");
                    Serial.print("@pt4&");
                    valRot = 1;
                    valRot3 = 1;
                    analogWrite(motor_rotulado_b, 0);
                }
            }
        }
        flag_time2 = false;
        cnt_time2 = 0;
        
        //Tubo en posicion IOT
        //banderaIOT = 9;
        lecturaSensoresAux.deteccionSensores();
        if(lecturaSensoresAux.varIOTSensores[4] == 1 && lecturaSensoresAux.varIOTSensores[5] == 1 && lecturaSensoresAux.varIOTSensores[6] == 1){
            varIOT[11] = "1";
            Serial.print(varIOT[11]);
            Serial.print(",");
        }
        else if((lecturaSensoresAux.varIOTSensores[4] == 0 && lecturaSensoresAux.varIOTSensores[5] == 0 && lecturaSensoresAux.varIOTSensores[6] == 0) || varSinRot == 1){
            varSinRot = 0;
            EEPROM.get(130, contaTubNotOk);
            contaTubNotOk = contaTubNotOk + 1;
            EEPROM.put(130, contaTubNotOk); 
            varIOT[2] = "1";
            varIOT[11] = "0";
            Serial.print(varIOT[11]);
            Serial.print(",");
            varIOT[12] = "-";
            Serial.print(varIOT[12]);
            Serial.print(",");
            varIOT[13] = "-";
            Serial.print(varIOT[13]);
            Serial.print(",");
            contadoresIOT();
            sinTubo = 1;
        }
    }
}

//Rutina para posicionar tubo de un sensor
void Rutinas::RotularTubo1Sensor()
{
    pinMode(servoMotorOn, OUTPUT); 
    delay(250);
    Servos[0].write(SR);
    delay(250);
    pinMode(servoMotorOn, INPUT);
        
    //analogWrite(motor_rotulado_b, V_PT);    
    bool val = false;
    bool val2 = false;
    int valRot = 0;
    cnt_time2 = 0;
    while (valRot == 0)
    {
        lecturaSensoresAux.deteccionSensores();
        if(lecturaSensoresAux.varIOTSensores[6] == 1)
        {
            val = true;
        }
        else if(lecturaSensoresAux.varIOTSensores[6] == 0)
        {
            val = false;
            valRot = 1; 
        }

        if (val)
        {            
            analogWrite(motor_rotulado_b, V_PT);
            flag_time2 = true;
            cnt_time2 = 0;
            int valRot2 = 0;
            while(valRot2 == 0)
            {
                lecturaSensoresAux.deteccionSensores();
                if(lecturaSensoresAux.varIOTSensores[5] == 1){
                    flag_time2 = true;
                    cnt_time2 = 0;
                    int valRot3 = 0;
                    while(valRot3 == 0)
                    {
                        lecturaSensoresAux.deteccionSensores();
                        if(lecturaSensoresAux.varIOTSensores[5] == 0){
                            valRot2 = 1;
                            valRot3 = 1;
                            analogWrite(motor_rotulado_b, 0);
                            val2 = true;
                        }
                        else if (banderaSRFallo == true)
                        {
                            banderaSRFallo= false;
                            //LiberarTuboSRFallo();
                            //Serial.print("@PT&");
                            Serial.print("@pt&");
                            valRot2 = 1;
                            valRot3 = 1;
                            valRot = 1;
                            analogWrite(motor_rotulado_b, 0);
                        }
                    }
                }
                else if (banderaSRFallo== true)
                {
                    banderaSRFallo= false;
                    //LiberarTuboSRFallo();
                    //Serial.print("@PT&");
                    Serial.print("@pt&");
                    valRot2 = 1;
                    valRot = 1;
                    analogWrite(motor_rotulado_b, 0);
                }
            }
            delay(100);
        }

        if (val2)
        {
            analogWrite(motor_rotulado_b, V_PT);
            cnt_time2 = 0;
            int valRot3 = 0;
            while(valRot3 == 0)
            {   
                lecturaSensoresAux.deteccionSensores();
                if(lecturaSensoresAux.varIOTSensores[5] == 1){
                valRot3 = 1;
                valRot = 1;
                analogWrite(motor_rotulado_b, 0);
                //Serial.print("@PT&");
                Serial.print("@pt&");
                }
                else if (banderaSRFallo== true)
                {
                    banderaSRFallo= false;
                    //LiberarTuboSRFallo();
                    //Serial.print("@PT&");
                    Serial.print("@pt&");
                    valRot = 1;
                    valRot3 = 1;
                    analogWrite(motor_rotulado_b, 0);
                }
            }
        }
        flag_time2 = false;
        cnt_time2 = 0;
        
        //Tubo en posicion IOT
        //banderaIOT = 9;
        lecturaSensoresAux.deteccionSensores();
        if(lecturaSensoresAux.varIOTSensores[4] == 1 && lecturaSensoresAux.varIOTSensores[5] == 1 && lecturaSensoresAux.varIOTSensores[6] == 1){
            varIOT[11] = "1";
            Serial.print(varIOT[11]);
            Serial.print(",");
        }
        else if((lecturaSensoresAux.varIOTSensores[4] == 0 && lecturaSensoresAux.varIOTSensores[5] == 0 && lecturaSensoresAux.varIOTSensores[6] == 0) || varSinRot == 1){
            varSinRot = 0;
            EEPROM.get(130, contaTubNotOk);
            contaTubNotOk = contaTubNotOk + 1;
            EEPROM.put(130, contaTubNotOk); 
            varIOT[2] = "1";
            varIOT[11] = "0";
            Serial.print(varIOT[11]);
            Serial.print(",");
            varIOT[12] = "-";
            Serial.print(varIOT[12]);
            Serial.print(",");
            varIOT[13] = "-";
            Serial.print(varIOT[13]);
            Serial.print(",");
            contadoresIOT();
            sinTubo = 1;
        }
    }
}

//Rutina para sistema de rotulacion sin sensores
void Rutinas::RotularTuboSinSensores()
{
    pinMode(servoMotorOn, OUTPUT); 
    delay(250);
    Servos[0].write(SR);
    delay(250);
    pinMode(servoMotorOn, INPUT);
        
    //analogWrite(motor_rotulado_b, V_PT);    
    bool val = false;
    bool val2 = false;
    int valRot = 0;
    flag_time2 = true;
    cnt_time2 = 0;
    while (valRot == 0)
    {
        lecturaSensoresAux.deteccionSensores();
        if(lecturaSensoresAux.varIOTSensores[6] == 1)
        {
            val = true;
        }
        else if(lecturaSensoresAux.varIOTSensores[6] == 0)
        {
            val = false;
            valRot = 1; 
        }

        if (val)
        {
            analogWrite(motor_rotulado_b, V_PT);
            flag_time2 = true;
            cnt_time2 = 0;
            int valRot2 = 0;
            while(valRot2 == 0)
            {   
                delay(500);
                if (banderaSRFallo== true)
                {
                    banderaSRFallo= false;
                    valRot = 1;
                    valRot2 = 1;
                    analogWrite(motor_rotulado_b, 0);
                    //LiberarTuboSRFallo();
                    //Serial.print("@PT&");
                    Serial.print("@pt&");
                }
                lecturaSensoresAux.deteccionSensores();
                if(lecturaSensoresAux.varIOTSensores[6] == 0)
                {
                    stopIOT();
                }
            }
        }
        flag_time2 = false;
        cnt_time2 = 0;
        
        //Tubo en posicion IOT
        //banderaIOT = 9;
        lecturaSensoresAux.deteccionSensores();
        if(lecturaSensoresAux.varIOTSensores[4] == 1 && lecturaSensoresAux.varIOTSensores[5] == 1 && lecturaSensoresAux.varIOTSensores[6] == 1){
            varIOT[11] = "1";
            Serial.print(varIOT[11]);
            Serial.print(",");
        }
        else if((lecturaSensoresAux.varIOTSensores[4] == 0 && lecturaSensoresAux.varIOTSensores[5] == 0 && lecturaSensoresAux.varIOTSensores[6] == 0) || varSinRot == 1){
            varSinRot = 0;
            EEPROM.get(130, contaTubNotOk);
            contaTubNotOk = contaTubNotOk + 1;
            EEPROM.put(130, contaTubNotOk); 
            varIOT[2] = "1";
            varIOT[11] = "0";
            Serial.print(varIOT[11]);
            Serial.print(",");
            varIOT[12] = "-";
            Serial.print(varIOT[12]);
            Serial.print(",");
            varIOT[13] = "-";
            Serial.print(varIOT[13]);
            Serial.print(",");
            contadoresIOT();
            sinTubo = 1;
        }
    }
}

// MÉTODO PARA POSICIONAR TUBO DENTRO DEL SISTEMA DE ROTULACIÓN (APRIETA SERVO Y GIRA HASTA ORIENTAR LA ETIQUETA)
void Rutinas::RotularTubo()
{
    pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
    Servos[0].write(SR);
    delay(600);
    pinMode(servoMotorOn, INPUT); // APAGO MOTOR
    delay(350);

    bool val = false;
    for (int i = 0; i<3; i++) {
        if (not digitalRead(sensor_tubo)) {
            val = true;
        }
        delay(50);
    }

    if (val) 
    {
        vlr_sensor_rotulado1 = not digitalRead(sensor_rotulado1);
        delay(150);
        analogWrite(motor_rotulado_b, V_PT);
        //Serial.println("@pt&");
        rta = "PT";
        flag_time = false;
        cnt_time = 0;
        if (vlr_sensor_rotulado1 == 1)
        {
            //Serial.println("Sensor 1"); // Depurado NO ALUMBRA
            flag_time = true;
            // rta = "PT";
            do
            {
                ///////////////////// Motor Rotulado Giro Izq //////////////
                // digitalWrite(motor_rotulado_b,LOW);
                ///////////////////// Actuador Rodillo Salida //////////////
                vlr_sensor_rotulado1 = not digitalRead(sensor_rotulado1);
                analogWrite(motor_rotulado_b, V_PT);
                delay(208);
                // analogWrite(motor_rotulado_b, V_PT);
                // delay(V_Dl);
                if (cnt_time >= 170)
                {
                    analogWrite(motor_rotulado_b, 0);
                    rta = "FAULTPT"; // PRENDE SENSOR
                    Serial.println(cabecera + rta + fintrama);
                    LiberarTubo();
                    break;
                }
            } while (vlr_sensor_rotulado1 == 1);
        }
    
        else if (vlr_sensor_rotulado1 == 0)
        {
            // Serial.println("Sensor 0"); //Depurado
            vlr_sensor_rotulado1 = not digitalRead(sensor_rotulado1);
            flag_time = true;
            do
            {
                rta = "PT_0"; // ALUMBRA
                vlr_sensor_rotulado1 = not digitalRead(sensor_rotulado1);
                analogWrite(motor_rotulado_b, V_PT);
                delay(73);
                // analogWrite(motor_rotulado_b, V_PT);
                // delay(V_Dl+300);
                if (cnt_time >= 170)
                {
                    rta = "FAULTPT"; // NO PREDE
                    Serial.println(cabecera + rta + fintrama);
                    analogWrite(motor_rotulado_b, 0);
                    LiberarTubo();
                    break;
                }
            } while (vlr_sensor_rotulado1 == 0);
            cnt_time = 0;
            do
            {
                rta = "PT";
                vlr_sensor_rotulado1 = not digitalRead(sensor_rotulado1);
                analogWrite(motor_rotulado_b, V_PT);
                delay(206);
                // analogWrite(motor_rotulado_b, V_PT-2);
                // delay(V_Dl);
                if (cnt_time >= 170)
                {
                    rta = "FAULTPT"; // ENTRA APAGADO Y PRENDE
                    Serial.println(cabecera + rta + fintrama);
                    analogWrite(motor_rotulado_b, 0);
                    LiberarTubo();
                    break;
                }
            } while (vlr_sensor_rotulado1 == 1);
        }    
    }
    flag_time = false;
    cnt_time = 0;
    analogWrite(motor_rotulado_b, 0);
}

// MÉTODO PARA ROTULAR TUBO (GIRAR TUBO MIENTRAS LA IMPRESORA IMPRIME Y PEGA ETIQUETA)
void Rutinas::Rotulado()
{
    tube_true = false;
    Servos[0].write(SR); // Fija la posicion del servo de acuerdo al valor definido
    delay(200);
    analogWrite(motor_rotulado_b, V_PT);
    delay(500);
    analogWrite(motor_rotulado_b, 0);
    delay(100);
    LiberarTubo();
}

//Rutina liberar tubo posicionado
void Rutinas::LiberarTubo()
{   
    pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
    delay(250);
    Servos[0].write(SR); // Fija la posicion del servo de acuerdo al valor definido
    delay(250);
    analogWrite(motor_rotulado_b, V_RT);
    delay(1000);
    analogWrite(motor_rotulado_b, 0);
    delay(200);
    Servos[0].write(SL);
    delay(200);
    // Servos[0].write(HMG);
    pinMode(servoMotorOn, INPUT); // APAGO MOTOR

    delay(1000);

    lecturaSensoresAux.deteccionSensores();
    if(lecturaSensoresAux.varIOTSensores[4] == 1 || lecturaSensoresAux.varIOTSensores[5] == 1 || lecturaSensoresAux.varIOTSensores[6] == 1)
    {
        pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
        Servos[0].write(SR); // Fija la posicion del servo de acuerdo al valor definido
        delay(100);
        analogWrite(motor_rotulado_b, V_RT);
        delay(750);
        Servos[0].write(SL);
        delay(200);
        analogWrite(motor_rotulado_b, 0);
        delay(200);
        // Servos[0].write(HMG);
        pinMode(servoMotorOn, INPUT); // APAGO MOTOR    
    }
     
    delay(1000);

    //Tubo rotulado y expulsado IOT
    //banderaIOT = 10;
    lecturaSensoresAux.deteccionSensores();
    if(lecturaSensoresAux.varIOTSensores[4] == 0 && lecturaSensoresAux.varIOTSensores[5] == 0 && lecturaSensoresAux.varIOTSensores[6] == 0){            
        varIOT[12] = "1";
        Serial.print(varIOT[12]);
        Serial.print(",");
    }
    else if(lecturaSensoresAux.varIOTSensores[4] == 1 && lecturaSensoresAux.varIOTSensores[5] == 1 && lecturaSensoresAux.varIOTSensores[6] == 1){
        varIOT[12] = "0";
        Serial.print(varIOT[12]);
        stopIOT();
    }

    //Contador aumento IOT
    lecturaSensoresAux.deteccionSensores();
    if(lecturaSensoresAux.varIOTSensores[4] == 0 && lecturaSensoresAux.varIOTSensores[5] == 0 && lecturaSensoresAux.varIOTSensores[6] == 0){            
        varIOT[13] = "1";
        Serial.print(varIOT[13]);
        Serial.print(",");
        EEPROM.get(120, contaTubOk);
        contaTubOk = contaTubOk + 1;
        varIOT[14] = contaTubOk;
        EEPROM.put(120, contaTubOk);
        tuboExpOk = 1;
        contadoresIOT();
    }
}

//Rutina liberar tubo cuando no se logra posicionar
void Rutinas::LiberarTuboSRFallo()
{   
    Servos[0].write(SR); // Fija la posicion del servo de acuerdo al valor definido
    delay(100);
    analogWrite(motor_rotulado_b, V_RT);
    pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
    delay(750);
    analogWrite(motor_rotulado_b, 0);
    delay(200);
    Servos[0].write(SL);
    delay(200);
    // Servos[0].write(HMG);
    pinMode(servoMotorOn, INPUT); // APAGO MOTOR

    delay(1000);

    lecturaSensoresAux.deteccionSensores();
    if(lecturaSensoresAux.varIOTSensores[4] == 1 || lecturaSensoresAux.varIOTSensores[5] == 1 || lecturaSensoresAux.varIOTSensores[6] == 1)
    {
        pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
        Servos[0].write(SR); // Fija la posicion del servo de acuerdo al valor definido
        delay(100);
        analogWrite(motor_rotulado_b, V_RT);
        delay(750);
        Servos[0].write(SL);
        delay(200);
        analogWrite(motor_rotulado_b, 0);
        delay(200);
        // Servos[0].write(HMG);
        pinMode(servoMotorOn, INPUT); // APAGO MOTOR    
    }
    apagarActuadores();
    varSensoresOk = 0;
    varSinRot = 1;
    delay(1000);
}

//Rutina obtener contadores IOT
void Rutinas::contadoresIOT()
{
    EEPROM.get(500, contaTubosL1);
    EEPROM.get(510, contaTubosL2);
    EEPROM.get(520, contaTubosL3);
    EEPROM.get(530, contaTubosL4);

    if(goToL1 == 1 && tuboExpOk == 1){
        tuboExpOk = 0;
        contaTubosL1 = contaTubosL1 - 1;
        EEPROM.put(500, contaTubosL1);
    }
    else if(goToL2 == 1 && tuboExpOk == 1){
        tuboExpOk = 0;
        contaTubosL2 = contaTubosL2 - 1;
        EEPROM.put(510, contaTubosL2);
    }
    else if(goToL3 == 1 && tuboExpOk == 1){
        tuboExpOk = 0;
        contaTubosL3 = contaTubosL3 - 1;
        EEPROM.put(520, contaTubosL3);
    }
    else if(goToL4 == 1 && tuboExpOk == 1){
        tuboExpOk = 0;
        contaTubosL4 = contaTubosL4 - 1;
        EEPROM.put(530, contaTubosL4);
    }

    EProm.leerIOT();
    varIOT[14] = contaTubOk;
    varIOT[15] = contaTubNotOk;
    varIOT[16] = contaFallos;
    varIOT[17] = contaTubosL1;
    varIOT[18] = contaTubosL2;
    varIOT[19] = contaTubosL3;
    varIOT[20] = contaTubosL4;

    Serial.print(varIOT[14]);
    Serial.print(",");
    Serial.print(varIOT[15]);
    Serial.print(",");
    Serial.print(varIOT[16]);
    Serial.print(",");
    Serial.print(varIOT[17]);
    Serial.print(",");
    Serial.print(varIOT[18]);
    Serial.print(",");
    Serial.print(varIOT[19]);
    Serial.print(",");
    Serial.println(varIOT[20]);

    for (int i=0; i<=20; i++)
    {
        varIOT[i] = "-";
    }

    if(contaTubosL1 <= 1)
    {    
        Serial.println("Linea #1 de gradilla sin tubos");
    }
    if(contaTubosL2 <= 1)
    {    
        Serial.println("Linea #2 de gradilla sin tubos");
    }
    if(contaTubosL3 <= 1)
    {    
        Serial.println("Linea #3 de gradilla sin tubos");
    }
    if(contaTubosL4 <= 1)
    {    
        Serial.println("Linea #4 de gradilla sin tubos");
    }
}

//Rutina monitoreo IOT
void Rutinas::procesoIOT()
{
    varIOT[0] = cliente;
    EProm.leerIOT();
    varIOT[11] = "-";
    varIOT[12] = "-";
    varIOT[13] = "-";
    varIOT[14] = contaTubOk;
    varIOT[15] = contaTubNotOk;
    varIOT[16] = contaFallos;
    varIOT[17] = contaTubosL1;
    varIOT[18] = contaTubosL2;
    varIOT[19] = contaTubosL3;
    varIOT[20] = contaTubosL4;
    
    String txt = "";
    String coma = ",";
    for (int i=0; i<=20; i++)
    {
        txt+=varIOT[i] + coma;
    }
    int longitugVectorIOT;
    longitugVectorIOT = txt.length();
    txt = txt.substring(0,longitugVectorIOT-1);
    Serial.println(txt);
    delay(1000);
    falloStop = txt;
    historialFallos();

    for (int i=0; i<=20; i++)
    {
        varIOT[i] = "-";
    }
    /*
    lecturaSensoresAux.deteccionSensores();
    String txt2 = "";
    String coma2 = ",";
    for (int i=0; i<=13; i++)
    {
        txt2+=lecturaSensoresAux.varIOTSensores[i] + coma2;
    }
    int longitugVectorIOTSensores;
    longitugVectorIOTSensores = txt2.length();
    
    txt2 = txt2.substring(0,longitugVectorIOTSensores-1);
    Serial.println(txt2);    
    */
}

// MÉTODO PARA ABRIR EL GRIPPER (ENCIENDO RELÉ 1 Y APAGO RELÉ 2, Y POR ÚLTIMO APAGO LOS DOS)
void Rutinas::griperOpen()
{
    pinMode(gripClose, HIGH); // ABRO GRIPPER
    pinMode(motorOn, LOW); // PRENDO MOTOR
    delay(200);
    pinMode(gripClose, LOW); // ABRO GRIPPER
    pinMode(motorOn, LOW); // APAGO MOTOR
}

// MÉTODO PARA CERRAR EL GRIPPER (ENCIENDO RELÉ 2 Y APAGO RELÉ 1)
void Rutinas::griperClose()
{
    pinMode(gripClose, LOW); // ABRO GRIPPER
    pinMode(motorOn, HIGH); // PRENDO MOTOR
    delay(200);
}

//Rutina paro en caso de fallo de sensores y/o proceso Monitoreo IOT
void Rutinas::stopIOT()
{
    EEPROM.get(140, contaFallos);
    contaFallos = contaFallos + 1;
    varIOT[16] = contaFallos;
    EEPROM.put(140, contaFallos);
    Serial.println("");
    //Serial.println("Desconexion automatica, reinicio del sistema");
    apagarActuadores();
    EEPROM.get(150, contaHistorialFallos);
    contaHistorialFallos = contaHistorialFallos + 1;
    EEPROM.put(150, contaHistorialFallos);
    procesoIOT();
    resetArduino();
}

//Rutina apagado de actuadores
void Rutinas::apagarActuadores()
{
    //Apagar actuadores
    digitalWrite(gripClose, HIGH);
    digitalWrite(motorOn, HIGH);
    digitalWrite(servoMotorOn, HIGH);
    digitalWrite(motor_rotulado_a, LOW);
    digitalWrite(motor_rotulado_b, LOW);
    digitalWrite(X_STEP_PIN, LOW);
    digitalWrite(X_DIR_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(X_ENABLE_PIN, LOW);
    digitalWrite(Y_ENABLE_PIN, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(B1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(B2, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(B3, LOW);
}

//Rutina historial fallos
void Rutinas::historialFallos()
{
    falloActual = falloStop;
    EEPROM.put(200, falloActual);
}

//Rutina obtener y ver historial fallos
void Rutinas::verHistorialFallos()
{
    EEPROM.get(300, falloAnterior);
    EEPROM.get(200, falloStop);
    vecHistFallos[0] = falloAnterior;
    vecHistFallos[1] = falloStop;
    
    Serial.println(vecHistFallos[0]);
    delay(2000);
    Serial.println(vecHistFallos[1]);
    delay(2000);
}

//Rutina obtener la hora de fallo actual
void Rutinas::ultimoFallo()
{
    EEPROM.get(200, falloActual);
    Serial.println(falloActual);
    delay(2000);
}

//Rutina contadores
void Rutinas::verContadores()
{
    EProm.leerIOT();
    Serial.print(cliente);
    Serial.print(",");
    Serial.print(version);
    Serial.print(",");
    Serial.print(contaTubOk);
    Serial.print(",");
    Serial.print(contaTubNotOk);
    Serial.print(",");
    Serial.print(contaFallos);
    Serial.print(",");
    Serial.print(contaTubosL1);
    Serial.print(",");
    Serial.print(contaTubosL2);
    Serial.print(",");
    Serial.print(contaTubosL3);
    Serial.print(",");
    Serial.print(contaTubosL4);
}

//Rutina lectura de sensores habilitados y deshabilitados
void Rutinas::monitorearSensoresHabilitados()
{
    EProm.leerInit();
    if(varSO1 == 1){
        sensoresHabilitados[0] = "0";
    }else{
        sensoresHabilitados[0] = "1";
    }
    if(varSO2 == 1){
        sensoresHabilitados[1] = "0";
    }else{
        sensoresHabilitados[1] = "1";
    }

    if(varSO3 == 1){
        sensoresHabilitados[2] = "0";
    }else{
        sensoresHabilitados[2] = "1";
    }

    if(varSO4 == 1){
        sensoresHabilitados[3] = "0";
    }else{
        sensoresHabilitados[3] = "1";
    }
    
    if(varSO5 == 1){
        sensoresHabilitados[4] = "0";
    }else{
        sensoresHabilitados[4] = "1";
    }
    
    if(varSO6 == 1){
        sensoresHabilitados[5] = "0";
    }else{
        sensoresHabilitados[5] = "1";
    }
    
    if(varSO7 == 1){
        sensoresHabilitados[6] = "0";
    }else{
        sensoresHabilitados[6] = "1";
    }
    
    if(varSO8 == 1){
        sensoresHabilitados[7] = "0";
    }else{
        sensoresHabilitados[7] = "1";
    }
    
    if(varSH1 == 1){
        sensoresHabilitados[8] = "0";
    }else{
        sensoresHabilitados[8] = "1";
    }
    
    if(varSH2 == 1){
        sensoresHabilitados[9] = "0";
    }else{
        sensoresHabilitados[9] = "1";
    }
    
    if(varSH3 == 1){
        sensoresHabilitados[10] = "0";
    }else{
        sensoresHabilitados[10] = "1";
    }
    
    if(varSH4 == 1){
        sensoresHabilitados[11] = "0";
    }else{
        sensoresHabilitados[11] = "1";
    }
    
    if(varSH5 == 1){
        sensoresHabilitados[12] = "0";
    }else{
        sensoresHabilitados[12] = "1";
    }
    
    if(varSH6 == 1){
        sensoresHabilitados[13] = "0";
    }else{
        sensoresHabilitados[13] = "1";
    }
    
    if(varSH7 == 1){
        sensoresHabilitados[14] = "0";
    }else{
        sensoresHabilitados[14] = "1";
    }
    
    if(varSSR == 1){
        sensoresHabilitados[15] = "0";
    }else{
        sensoresHabilitados[15] = "1";
    }

    if(varSGPR == 1){
        sensoresHabilitados[16] = "0";
    }else{
        sensoresHabilitados[16] = "1";
    }
    String txt = "";
    String coma = ",";
    for (int i=0; i<=16; i++)
    {
        txt+=sensoresHabilitados[i] + coma;
    }
    int longitugVectorIOT;
    longitugVectorIOT = txt.length();
    
    txt = txt.substring(0,longitugVectorIOT-1);
    Serial.println(txt);
}
