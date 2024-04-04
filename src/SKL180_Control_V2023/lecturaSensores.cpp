#include "lecturaSensores.h"

// MÉTODO CONSTRUCTOR CLASE
lecturaSensores::lecturaSensores() {
    
}

void lecturaSensores::leerSensoresTCRT5000() {
    SO1 = 0;
    SO2 = 0;
    SO3 = 0;
    SO4 = 0;
    SO5 = 0;
    SO6 = 0;
    SO7 = 0;
    SO8 = 0;   

    for(int i = 0; i<100; i++) {
        /*//Sensores llenado
        if(not digitalRead(sensor_tubo_linea1)) {
            SO1++;
            Serial.print("1");
        }
        else if(digitalRead(sensor_tubo_linea1)) {
            Serial.print("0");
        }
        Serial.print(",");
        if(not digitalRead(sensor_tubo_linea2)) {
            SO2++;
            Serial.print("1");
        }
        else if(digitalRead(sensor_tubo_linea2)) {
            Serial.print("0");
        }
        Serial.print(",");
        if(not digitalRead(sensor_tubo_linea3)) {
            SO3++;
            Serial.print("1");
        }
        else if(digitalRead(sensor_tubo_linea3)) {
            Serial.print("0");
        }
        Serial.print(",");
        if(not digitalRead(sensor_tubo_linea4)) {
            SO4++;
            Serial.print("1");
        }
        else if(digitalRead(sensor_tubo_linea4)) {
            Serial.print("0");
        }
        Serial.println("");
        delay(10000);*/

        //Sensores llenado
        if(not digitalRead(sensor_tubo_linea1)) {
            SO1++;
        }
        if(not digitalRead(sensor_tubo_linea2)) {
            SO2++;
        }
        if(not digitalRead(sensor_tubo_linea3)) {
            SO3++;
        }
        if(not digitalRead(sensor_tubo_linea4)) {
            SO4++;
        }
        if(not digitalRead(sensor_rotulado1)) {
            SO5++;
        }
        if(not digitalRead(sensor_rotulado2)) {
            SO6++;
        }
        if(not digitalRead(sensor_tubo)) {
            SO7++;
        }
        
        if(not digitalRead(sensor_Home_SR)) {
            SO8++;
        }
    }
}

void lecturaSensores::leerSensoresTCST2103() {
    SH1 = 0;
    SH2 = 0;
    SH3 = 0;
    SH4 = 0;
    SH5 = 0;
    SH6 = 0;
    SH7 = 0;
    
    for(int i = 0; i<100; i++) {
        if(digitalRead(X_MIN_PIN)) {
            SH1++;
        }
        if(digitalRead(Y_MIN_PIN)) {
            SH2++;
        }
        if(digitalRead(sensor_linea1)) {
            SH3++;
        }
        if(digitalRead(sensor_linea2)) {
            SH4++;
        }
        if(digitalRead(sensor_linea3)) {
            SH5++;
        }
        if(digitalRead(sensor_linea4)) {
            SH6++;
        }

        valorSH7 = analogRead(sensor_gripper);
        voltajeSH7 = valorSH7*5/1023;
        if(voltajeSH7 >= 4.5) {
            SH7++;
        }
    }
}

void lecturaSensores::deteccionSensores()
{
    leerSensoresTCRT5000();
    leerSensoresTCST2103();
    
    if (SO1 >= 95 && varSO1 == 0) //sensor tubo linea 1
    {
        varIOTSensores[0] = 1;
        SO1 = 0;
    }
    else if (SO1 <= 94 || varSO1 == 1)
    {
        varIOTSensores[0] = 1;
        SO1 = 0;
    }

    if (SO2 >= 95 && varSO2 == 0) //sensor tubo linea 2
    {
        varIOTSensores[1] = 1;
        SO2 = 0;
    }
    else if (SO2 <= 94 || varSO2 == 1)
    {
        varIOTSensores[1] = 0;
        SO2 = 0;
    }

    if (SO3 >= 95 && varSO3 == 0) //sensor tubo linea 3
    {
        varIOTSensores[2] = 1;
        SO3 = 0;
    }
    else if (SO3 <= 94 || varSO3 == 1)
    {
        varIOTSensores[2] = 0;
        SO3 = 0;
    }

    if (SO4 >= 95 && varSO4 == 0) //sensor tubo linea 4
    {
        varIOTSensores[3] = 1;
        SO4 = 0;
    }
    else if (SO4 <= 95 || varSO4 == 1)
    {
        varIOTSensores[3] = 0;
        SO4 = 0;
    }

    if (SO5 >= 95 && varSO5 == 0) //sensor rotulado 1 (extremo)
    {
        varIOTSensores[4] = 1;
        SO5 = 0;
        //Serial.println("extremo");
    }
    else if (SO5 <= 95 || varSO5 == 1)
    {
        varIOTSensores[4] = 0;
        SO5 = 0;
    }

    if (SO6 >= 95 && varSO6 == 0) //sensor rotulado 2 (entre rodillos)
    {
        varIOTSensores[5] = 1;
        SO6 = 0;
        //Serial.println("rodillo");
    }
    else if (SO6 <= 95 || varSO6 == 1)
    {
        varIOTSensores[5] = 0;
        SO6 = 0;
    }

    if (SO7 >= 95 && varSO7 == 0) //sensor tubo (tapa S.R.)
    {
        varIOTSensores[6] = 1;
        SO7 = 0;
    }

    else if (SO7 <= 95 || varSO7 == 1)
    {
        varIOTSensores[6] = 0;
        SO7 = 0;
    }

    if (SO8 >= 95 && varSO8 == 0) //sensor servo Home (S.R.)
    {
        varIOTSensores[7] = 1;
        SO8 = 0;
    }
    else  if (SO8 <= 95 || varSO8 == 1)
    {
        varIOTSensores[7] = 0;
        SO8 = 0;
    }

    if (SH1 >= 95 && varSH1 == 0) //sensor Eje X Home
    {
        varIOTSensores[8] = 1;
        SH1 = 0;
    }
    else if (SH1 <= 95 || varSH1 == 1)
    {
        varIOTSensores[8] = 0;
        SH1 = 0;
    }

    if (SH2 >= 95 && varSH2 == 0) //sensor Eje Y Home
    {
        varIOTSensores[9] = 1;
        SH2 = 0;
    }
    else if (SH2 <= 95 || varSH2 == 1)
    {
        varIOTSensores[9] = 0;
        SH2 = 0;
    }

    if (SH3 >= 95 && varSH3 == 0) //sensor linea 1
    {
        varIOTSensores[10] = 1;
        SH3 = 0;
    }
    else if (SH3 <= 95 || varSH3 == 1)
    {
        varIOTSensores[10] = 0;
        SH3 = 0;
    }

    if (SH4 >= 95 && varSH4 == 0) //sensor linea 2
    {
        varIOTSensores[11] = 1;
        SH4 = 0;
    }
    else if (SH4 <= 95 || varSH4 == 1)
    {
        varIOTSensores[11] = 0;
        SH4 = 0;
    }

    if (SH5 >= 95 && varSH5 == 0) //sensor linea 3
    {
        varIOTSensores[12] = 1;
        SH5 = 0;
    }
    else if (SH5 <= 95 || varSH5 == 1)
    {
        varIOTSensores[12] = 0;
        SH5 = 0;
    }

    if (SH6 >= 95 && varSH6 == 0) //sensor linea 4
    {
        varIOTSensores[13] = 1;
        SH6 = 0;
    }
    else if (SH6 <= 95 || varSH6 == 1)
    {
        varIOTSensores[13] = 0;
        SH6 = 0;
    }

    if (SH7 >= 95 && varSH7 == 0) //sensor Gripper
    {
        varIOTSensores[14] = 1;
        SH7 = 0;
    }
    else if (SH7 <= 95 || varSH7 == 1)
    {
        varIOTSensores[14] = 0;
        SH7 = 0;
    }

    /*
    for (int i=0; i<=12; i++)
    {
        Serial.print(varIOTSensores[i]);
        Serial.print(",");
    }
    Serial.println(varIOTSensores[13]);*/
}