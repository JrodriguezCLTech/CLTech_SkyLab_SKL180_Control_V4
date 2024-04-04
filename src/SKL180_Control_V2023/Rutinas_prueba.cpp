#include "Rutinas_prueba.h"

// MÉTODO PARA RUTINA PRINCIPAL SKL-180 (RECOGER TUBO EN LINEA Y DEJARLO EN SISTEMA ROTULACION)
void Rutinas_prueba::RecogerTubo(String VLinea)
{
    bool HMGl1 = false;
    bool HMGl2 = false;
    bool HMG21 = false;
    bool HMG22 = false;
    bool MVl1 = false;

    /*
    int sensor_lineaX = sensor_linea1;
    if (VLinea == "L1" or VLinea == "L2" or VLinea == "L3" or VLinea == "L4")
    {
        if (encendidoMaquina)
        {
            encendidoMaquina = false;
            griperOpen();
            griperClose();
            griperOpen();
        }

        t_reset = millis();

        flag_time = true;
        int line = VLinea.substring(1).toInt();
        int stepsXLineX = stepsXLine1;
        int stepsXCalibrateLineX = stepsXCalibrateLine1;
        switch (line)
        {
        case 1:
            sensor_lineaX = sensor_linea1;
            stepsXLineX = stepsXLine1;
            stepsXCalibrateLineX = stepsXCalibrateLine1;
            break;
        case 2:
            sensor_lineaX = sensor_linea2;
            stepsXLineX = stepsXLine2;
            stepsXCalibrateLineX = stepsXCalibrateLine2;
            break;
        case 3:
            sensor_lineaX = sensor_linea3;
            stepsXLineX = stepsXLine3;
            stepsXCalibrateLineX = stepsXCalibrateLine3;
            break;
        case 4:
            sensor_lineaX = sensor_linea4;
            stepsXLineX = stepsXLine4;
            stepsXCalibrateLineX = stepsXCalibrateLine4;
            break;
        }

        // LLEVANDO X A LINEA
        // Serial.println("Llevando X a linea");
        stepperAX.estadoHomePasos(false);
        stepperAX.actualPasos = stepsXLineX;
        stepperAX.dirHome = not stepperAX.dirHome;
        stepperAX._pinFinCarrera = sensor_lineaX;
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.homeMotorFin();
        while (stepperAX.home)
        {
            stepperAX.procesarCNC();
            stepperAX.control();
        }
        stepperAX.estadoHomePasos(true);
        stepperAX.actualPasos = (stepsXLineX - stepperAX.actualPasos);
        stepperAX.dirHome = not stepperAX.dirHome;
        stepperAX._pinFinCarrera = X_MIN_PIN;

        // CALIBRANDO X A CENTRO DE LINEA
        // Serial.println("Calibrando X");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.moverMotor(stepperAX.actualPasos + stepsXCalibrateLineX);
        while (stepperAX.estadoMov != 0)
        {
            stepperAX.procesarCNC();
            stepperAX.control();
        }

        // LLEVANDO Y A RECOGER TUBO
        // Serial.println("Devolviendo Y a home");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.moverMotor(stepsYHomeToPickTube);
        while (stepperAY.estadoMov != 0)
        {
            stepperAY.procesarCNC();
            stepperAY.control();
        }

        // CERRANDO GRIPPER
        // Serial.println("Cerrando gripper");
        griperClose();

        // DEVOLVIENDO Y A HOME
        // Serial.println("Recogiendo tubo");
        stepperAY.estadoPerfilVel(true);
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.homeMotorFin();
        while (stepperAY.home)
        {
            stepperAY.procesarCNC();
            stepperAY.control();
        }

        // CALIBRANDO X A DEJAR TUBO
        // Serial.println("Calibrando X 2");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.moverMotor(stepsXCalibrateReleaseTube);
        while (stepperAX.estadoMov != 0)
        {
            stepperAX.control();
        }

        // LLEVANDO Y A DEJAR TUBO
        // Serial.println("Dejando tubo");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.moverMotor(stepsYHomeToReleaseTube);
        while (stepperAY.estadoMov != 0)
        {
            stepperAY.control();
        }

        // ABRIENDO GRIPPER
        // Serial.println("Abriendo gripper");
        griperOpen();

        // DEVOLVIENDO Y A HOME
        // Serial.println("Devolviendo Y a home");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.homeMotorFin();
        while (stepperAY.home)
        {
            stepperAY.procesarCNC();
            stepperAY.control();
        }

        // DEVOLVIENDO X A HOME
        // Serial.println("Devolviendo X a home");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.homeMotorFin();
        while (stepperAX.home)
        {
            stepperAX.procesarCNC();
            stepperAX.control();
        }

        // Serial.print("@DS" + VLinea + "&");
        PosicionarTubo();
        Serial.print("@PT&");
    }*/
    
    //Codificado por JRodriguez
    pinMode(servoMotorOn, OUTPUT); 
    delay(750);
    Servos[0].write(SL);
    delay(1000);
    pinMode(servoMotorOn, INPUT);

    int sensor_lineaX = sensor_linea1;
    if (VLinea == "L1" or VLinea == "L2" or VLinea == "L3" or VLinea == "L4")
    {
        griperOpen();
        griperClose();
        griperOpen();
        if (encendidoMaquina) {
          encendidoMaquina = false;
          griperOpen();
          griperClose();
          griperOpen();
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
          break;
        case 2:
          sensor_lineaX = sensor_linea2;
          stepsXLineX = stepsXLine2;
          break;
        case 3:
          sensor_lineaX = sensor_linea3;
          stepsXLineX = stepsXLine3;
          break;
        case 4:
          sensor_lineaX = sensor_linea4;
          stepsXLineX = stepsXLine4;
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
        while(stepperAX.home) {
            stepperAX.procesarCNC();
            stepperAX.control();
        }
        stepperAX.estadoHomePasos(true);
        stepperAX.actualPasos = (stepsXLineX-stepperAX.actualPasos);
        stepperAX.dirHome = not stepperAX.dirHome;
        stepperAX._pinFinCarrera = X_MIN_PIN;

        // CALIBRANDO X A CENTRO DE LINEA
        //Serial.println("Calibrando X");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.moverMotor(stepperAX.actualPasos + stepsXCalibrateLineX);
        while(stepperAX.estadoMov != 0) {
            stepperAX.procesarCNC();
            stepperAX.control();
        }

        // LLEVANDO Y A RECOGER TUBO
        //Serial.println("Devolviendo Y a home");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.moverMotor(stepsYHomeToPickTube);
        while(stepperAY.estadoMov != 0) {
            stepperAY.procesarCNC();
            stepperAY.control();
        }

        //CERRANDO GRIPPER
        //Serial.println("Cerrando gripper");
        griperClose();
        
        // DEVOLVIENDO Y A HOME
        //Serial.println("Recogiendo tubo");
        stepperAY.estadoPerfilVel(true);
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.homeMotorFin();
        while(stepperAY.home) {
            stepperAY.procesarCNC();
            stepperAY.control();
        } 

        // CALIBRANDO X A DEJAR TUBO
        //Serial.println("Calibrando X 2");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.moverMotor(stepsXCalibrateReleaseTube);
        while(stepperAX.estadoMov != 0) {
            stepperAX.control();
        }
        
        // LLEVANDO Y A DEJAR TUBO
        //Serial.println("Dejando tubo");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.moverMotor(stepsYHomeToReleaseTube);
        while(stepperAY.estadoMov != 0) {
            stepperAY.control();
        }

        //HOME SERVO
         pinMode(servoMotorOn, OUTPUT); 
        delay(750);
        Servos[0].write(HMG);
        delay(1000);
        pinMode(servoMotorOn, INPUT);
        

        // ABRIENDO GRIPPER
        //Serial.println("Abriendo gripper");
        griperOpen();

        // DEVOLVIENDO Y A HOME
        //Serial.println("Devolviendo Y a home");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.homeMotorFin();
        while(stepperAY.home) {
            stepperAY.procesarCNC();
            stepperAY.control();
        }
        
        // DEVOLVIENDO X A HOME
        //Serial.println("Devolviendo X a home");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.homeMotorFin();
        while(stepperAX.home) {
            stepperAX.procesarCNC();
            stepperAX.control();
        }

        //ROTULAR
        PosicionarTubo();
        Serial.print("@PT&");
    }
}

void Rutinas_prueba::RecogerYDevolverTubo(String VLinea)
{
    bool HMGl1 = false;
    bool HMGl2 = false;
    bool HMG21 = false;
    bool HMG22 = false;
    bool MVl1 = false;

    int sensor_lineaX = sensor_linea1;
    if (VLinea == "L1" or VLinea == "L2" or VLinea == "L3" or VLinea == "L4")
    {
        if (encendidoMaquina)
        {
            encendidoMaquina = false;
            griperOpen();
            griperClose();
            griperOpen();
            griperClose();
            griperOpen();
        }
        pinMode(servoMotorOn, OUTPUT);
        Servos[0].write(HMG);
        pinMode(servoMotorOn, INPUT);
        t_reset = millis();

        flag_time = true;
        int line = VLinea.substring(1).toInt();
        int stepsXLineX = stepsXLine1;
        switch (line)
        {
        case 1:
            sensor_lineaX = sensor_linea1;
            stepsXLineX = stepsXLine1;
            break;
        case 2:
            sensor_lineaX = sensor_linea2;
            stepsXLineX = stepsXLine2;
            break;
        case 3:
            sensor_lineaX = sensor_linea3;
            stepsXLineX = stepsXLine3;
            break;
        case 4:
            sensor_lineaX = sensor_linea4;
            stepsXLineX = stepsXLine4;
            break;
        }

        // LLEVANDO X A LINEA
        // Serial.println("Llevando X a linea");
        stepperAX.estadoHomePasos(false);
        stepperAX.actualPasos = stepsXLineX;
        stepperAX.dirHome = not stepperAX.dirHome;
        stepperAX._pinFinCarrera = sensor_lineaX;
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.homeMotorFin();
        while (stepperAX.home)
        {
            stepperAX.procesarCNC();
            stepperAX.control();
        }
        stepperAX.estadoHomePasos(true);
        stepperAX.actualPasos = (stepsXLineX - stepperAX.actualPasos);
        stepperAX.dirHome = not stepperAX.dirHome;
        stepperAX._pinFinCarrera = X_MIN_PIN;

        // CALIBRANDO X A CENTRO DE LINEA
        // Serial.println("Calibrando X");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.moverMotor(stepperAX.actualPasos + stepsXCalibrateLineX);
        while (stepperAX.estadoMov != 0)
        {
            stepperAX.procesarCNC();
            stepperAX.control();
        }

        // LLEVANDO Y A RECOGER TUBO
        // Serial.println("Devolviendo Y a home");
        stepperAY.estadoPerfilVel(true);
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.moverMotor(stepsYHomeToPickTube);
        while (stepperAY.estadoMov != 0)
        {
            stepperAY.procesarCNC();
            stepperAY.control();
        }

        // CERRANDO GRIPPER
        // Serial.println("Cerrando gripper");
        griperClose();

        // DEVOLVIENDO Y A HOME
        // Serial.println("Recogiendo tubo");
        stepperAY.estadoPerfilVel(true);
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.homeMotorFin();
        while (stepperAY.home)
        {
            stepperAY.procesarCNC();
            stepperAY.control();
        }

        // CALIBRANDO X A DEJAR TUBO
        // Serial.println("Calibrando X 2");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.moverMotor(stepsXCalibrateReleaseTube);
        while (stepperAX.estadoMov != 0)
        {
            stepperAX.control();
        }

        // LLEVANDO Y A DEJAR TUBO
        // Serial.println("Dejando tubo");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.moverMotor(stepsYHomeToReleaseTube);
        while (stepperAY.estadoMov != 0)
        {
            stepperAY.control();
        }

        // DEVOLVIENDO Y A HOME
        // Serial.println("Devolviendo Y a home");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.homeMotorFin();
        while (stepperAY.home)
        {
            stepperAY.procesarCNC();
            stepperAY.control();
        }

        // LLEVANDO X A LINEA
        // Serial.println("Llevando X a linea");
        stepperAX.estadoHomePasos(false);
        stepperAX.actualPasos = stepsXLineX;
        stepperAX.dirHome = not stepperAX.dirHome;
        stepperAX._pinFinCarrera = sensor_lineaX;
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.homeMotorFin();
        while (stepperAX.home)
        {
            stepperAX.procesarCNC();
            stepperAX.control();
        }
        stepperAX.estadoHomePasos(true);
        stepperAX.actualPasos = (stepsXLineX - stepperAX.actualPasos);
        stepperAX.dirHome = not stepperAX.dirHome;
        stepperAX._pinFinCarrera = X_MIN_PIN;

        // CALIBRANDO X A CENTRO DE LINEA
        // Serial.println("Calibrando X");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.moverMotor(stepperAX.actualPasos + stepsXCalibrateLineX);
        while (stepperAX.estadoMov != 0)
        {
            stepperAX.control();
        }

        // LLEVANDO Y A RECOGER TUBO
        // Serial.println("Devolviendo Y a home");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.moverMotor(stepsYHomeToPickTube);
        while (stepperAY.estadoMov != 0)
        {
            stepperAY.control();
        }

        // CERRANDO GRIPPER
        // Serial.println("Cerrando gripper");
        griperOpen();

        // DEVOLVIENDO Y A HOME
        // Serial.println("Devolviendo Y a home");
        stepperAY.cambiarRpmActualMotor(rpmMaxY);
        stepperAY.homeMotorFin();
        while (stepperAY.home)
        {
            stepperAY.procesarCNC();
            stepperAY.control();
        }

        // DEVOLVIENDO X A HOME
        // Serial.println("Devolviendo X a home");
        stepperAX.cambiarRpmActualMotor(rpmMaxX);
        stepperAX.homeMotorFin();
        while (stepperAX.home)
        {
            stepperAX.procesarCNC();
            stepperAX.control();
        }

        // Serial.print("@DS" + VLinea + "&");
        PosicionarTubo();
        Serial.println("@PT&");
    }
}

// MÉTODO PARA POSICIONAR TUBO DENTRO DEL SISTEMA DE ROTULACIÓN (APRIETA SERVO Y GIRA HASTA ORIENTAR LA ETIQUETA)
void Rutinas_prueba::PosicionarTubo()
{
    pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
    Servos[0].write(SR);
    delay(600);
    pinMode(servoMotorOn, INPUT); // APAGO MOTOR
    delay(350);

    bool val = false;
    for (int i = 0; i < 3; i++)
    {
        if (not digitalRead(sensor_tubo))
        {
            val = true;
        }
        delay(50);
    }

    if (val)
    {
        vlr_sensor_rotulado1 = not digitalRead(sensor_rotulado1);
        delay(150);
        analogWrite(motor_rotulado_b, V_PT);
        // Serial.println("@pt&");
        rta = "PT";
        flag_time = false;
        cnt_time = 0;
        if (vlr_sensor_rotulado1 == 1)
        {
            // Serial.println("Sensor 1"); // Depurado NO ALUMBRA
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
    Serial.println(cabecera + rta + fintrama);
}

// MÉTODO PARA ROTULAR TUBO (GIRAR TUBO MIENTRAS LA IMPRESORA IMPRIME Y PEGA ETIQUETA)
void Rutinas_prueba::RotularTubo()
{
    tube_true = false;
    Servos[0].write(SR); // Fija la posicion del servo de acuerdo al valor definido
    delay(200);
    analogWrite(motor_rotulado_b, V_PT);
    delay(2900);
    analogWrite(motor_rotulado_b, 0);
    delay(700);
    LiberarTubo();
}
// MÉTODO PARA LIBERAR TUBO (MIENTRAS GIRA, SUELTA SERVO Y DEJA CAER TUBO)
void Rutinas_prueba::LiberarTubo()
{
    analogWrite(motor_rotulado_b, V_RT);
    pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
    delay(1000);
    analogWrite(motor_rotulado_b, 0);
    delay(750);
    Servos[0].write(SL);
    delay(750);
    // Servos[0].write(HMG);
    pinMode(servoMotorOn, INPUT); // APAGO MOTOR
}
// MÉTODO PARA ABRIR EL GRIPPER (ENCIENDO RELÉ 1 Y APAGO RELÉ 2, Y POR ÚLTIMO APAGO LOS DOS)
void Rutinas_prueba::griperOpen()
{
    pinMode(gripClose, HIGH); // ABRO GRIPPER
    pinMode(motorOn, LOW);    // PRENDO MOTOR
    delay(600);
    pinMode(gripClose, LOW); // ABRO GRIPPER
    pinMode(motorOn, LOW);   // APAGO MOTOR
}
// MÉTODO PARA CERRAR EL GRIPPER (ENCIENDO RELÉ 2 Y APAGO RELÉ 1)
void Rutinas_prueba::griperClose()
{
    pinMode(gripClose, LOW); // ABRO GRIPPER
    pinMode(motorOn, HIGH);  // PRENDO MOTOR
    delay(600);
}
