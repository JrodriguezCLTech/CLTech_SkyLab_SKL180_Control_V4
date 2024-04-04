#include "estadoSensores.h"

estadoSensores::estadoSensores()   //constructor
{
}

void estadoSensores::initVar()
{
    sumMonSen = 0;
    s1Bien = 0;
    s2Bien = 0;
    s3Bien = 0;
    s4Bien = 0;
    s5Bien = 0;
    s6Bien = 0;
    s7Bien = 0;
    s8Bien = 0;
    s9Bien = 0;
    s10Bien = 0;
    s11Bien = 0;
    s12Bien = 0;
}

void estadoSensores::monitoreoVectorEstadoSistema()
{
    initVar();
    monitorearS1();
    monitorearS2();
    monitorearS3();
    monitorearS4();
    monitorearS5();
    monitorearS6();
    monitorearS7();
    monitorearS8();
    monitorearS9();
    monitorearS10();
    monitorearS11();
    monitorearS12();

    //Estado Subsistema #1
    if (s1Bien == 1 && s2Bien == 1 && s3Bien == 1 && s4Bien == 1)
    {
        estadoSistema[0] = 1;
    }

    else
    {
        estadoSistema[0] = 0;

    }

    //Estado Subsistema #2
    if (s5Bien == 1 && s6Bien == 1 && s7Bien == 1 && s8Bien == 1)
    {
        estadoSistema[1] = 1;
    }

    else
    {
        estadoSistema[1] = 0;
    }

    //Estado Subsistema #3
    if (s9Bien == 1 && s10Bien == 1 && s11Bien == 1 && s12Bien == 1)
    {
        estadoSistema[2] = 1;
    }

    else
    {
        estadoSistema[2] = 0;
    }

    Serial.print(cliente);
    Serial.print(",");
    Serial.print(version);
    Serial.print(",");
    String txt = "";
    String coma = ",";
    for (int i=0; i<=2 ; i++)
    {
        txt+=estadoSistema[i] + coma;
    }
    int longitugVectorIOTEstado;
    longitugVectorIOTEstado = txt.length();
    
    txt = txt.substring(0,longitugVectorIOTEstado-1);
    Serial.println(txt);

    if(estadoSistema[0] == 0 || estadoSistema[1] == 0 || estadoSistema[2] == 0)
    {
        monitoreoSensores();
        varSensoresOk = 0;
    }
}

void estadoSensores::monitoreoSensores()
{
    if (estadoSistema[0] == 0)
    {
        estadosSubsistemas[0] = s1Bien;
        estadosSubsistemas[1] = s2Bien;
        estadosSubsistemas[2] = s3Bien;
        estadosSubsistemas[3] = s4Bien;

        String txt2 = "";
        String coma = ",";
        for (int i=0; i<=3 ; i++)
        {
            txt2+=estadosSubsistemas[i] + coma;
        }
        int longitugVectorIOT2;
        longitugVectorIOT2 = txt2.length();
        txt2 = txt2.substring(0,longitugVectorIOT2-1);
        Serial.print(txt2);
    }

    if (estadoSistema[1] == 0)
    {
        if(estadoSistema[0] == 0)
        {
            Serial.print(", ");
        }
   
        estadosSubsistemas[4] = s5Bien;
        estadosSubsistemas[5] = s6Bien;
        estadosSubsistemas[6] = s7Bien;
        estadosSubsistemas[7] = s8Bien;
        
        String txt3 = "";
        String coma = ",";
        for (int i=4; i<=7 ; i++)
        {
            txt3+=estadosSubsistemas[i] + coma;
        }
        int longitugVectorIOT3;
        longitugVectorIOT3 = txt3.length();
        txt3 = txt3.substring(0,longitugVectorIOT3-1);
        Serial.print(txt3);
    }

    if (estadoSistema[2] == 0)
    {
        if(estadoSistema[0] == 0 || estadoSistema[1] == 0)
        {
            Serial.print(", ");
        }
        
        estadosSubsistemas[8] = s9Bien;
        estadosSubsistemas[9] = s10Bien;
        estadosSubsistemas[10] = s11Bien;
        estadosSubsistemas[11] = s12Bien;
        /**/
        String txt4 = "";
        String coma = ",";
        for (int i=8; i<=11 ; i++)
        {
            txt4+=estadosSubsistemas[i];
        }
        int longitugVectorIOT4;
        longitugVectorIOT4 = txt4.length();
        txt4 = txt4.substring(0,longitugVectorIOT4-1);
        Serial.print(txt4);
    }
    Serial.println("");
}

void estadoSensores::monitoreoSensores2()
{
    monitorearS1();
    monitorearS2();
    monitorearS3();
    monitorearS4();
    monitorearS5();
    monitorearS6();
    monitorearS7();
    monitorearS8();
    monitorearS9();
    monitorearS10();
    monitorearS11();
    monitorearS12();
    
    estadosSubsistemas[0] = s1Bien;
    estadosSubsistemas[1] = s2Bien;
    estadosSubsistemas[2] = s3Bien;
    estadosSubsistemas[3] = s4Bien;
    estadosSubsistemas[4] = s5Bien;
    estadosSubsistemas[5] = s6Bien;
    estadosSubsistemas[6] = s7Bien;
    estadosSubsistemas[7] = s8Bien;
    estadosSubsistemas[8] = s9Bien;
    estadosSubsistemas[9] = s10Bien;
    estadosSubsistemas[10] = s11Bien;
    estadosSubsistemas[11] = s12Bien;
    
    String txt2 = "";
    String txt3 = "";
    String txt4 = "";

    for (int i=0; i<=3 ; i++)
    {
        txt2+=estadosSubsistemas[i];
    }
    for (int i=4; i<=7 ; i++)
    {
        txt3+=estadosSubsistemas[i];
    }
    for (int i=8; i<=11; i++)
    {
        txt4+=estadosSubsistemas[i];
    }
    Serial.print(txt2);
    Serial.print(", ");
    Serial.print(txt3);
    Serial.print(", ");
    Serial.print(txt4);
}

void estadoSensores::monitorearS1()
{
    //S1
    s1Bien = 0;
    sumMonSen = 0;
    digitalWrite(A1, 0);
    digitalWrite(B1, 0);
    
    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }

    if(sumMonSen >= 95)
    {
        s1Bien = 1;
    }
    else
    {
        s1Bien = 0;
    }
}

void estadoSensores::monitorearS2()
{
    //S2
    s2Bien = 0;
    sumMonSen = 0;
    digitalWrite(A1, 1);
    digitalWrite(B1, 0);
    
    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s2Bien = 1;
    }
    else
    {
        s2Bien = 0;
    }
}

void estadoSensores::monitorearS3()
{ 
    //S3
    s3Bien = 0;
    sumMonSen = 0;
    digitalWrite(A1, 0);
    digitalWrite(B1, 1);
    
    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s3Bien = 1;
    }
    else
    {
        s3Bien = 0;
    }
}

void estadoSensores::monitorearS4()
{ 
    //S4
    s4Bien = 0;
    sumMonSen = 0;
    digitalWrite(A1, 1);
    digitalWrite(B1, 1);

    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s4Bien = 1;
    }
    else
    {
        s4Bien = 0;
    }
}

void estadoSensores::monitorearS5()
{ 
    //S5
    s5Bien = 0;
    sumMonSen = 0;
    digitalWrite(A2, 0);
    digitalWrite(B2, 0);

    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada2) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s5Bien = 1;
    }
    else
    {
        s5Bien = 0;
    }
}

void estadoSensores::monitorearS6()
{ 
    //S6
    s6Bien = 0;
    sumMonSen = 0;
    digitalWrite(A2, 1);
    digitalWrite(B2, 0);

    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada2) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s6Bien = 1;
    }
    else
    {
        s6Bien = 0;
    }
}

void estadoSensores::monitorearS7()
{ 
    //S7
    s7Bien = 0;
    sumMonSen = 0;
    digitalWrite(A2, 0);
    digitalWrite(B2, 1);

    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada2) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s7Bien = 1;
    }
    else
    {
        s7Bien = 0;
    }
}

void estadoSensores::monitorearS8()
{ 
    //S8
    s8Bien = 0;
    sumMonSen = 0;
    digitalWrite(A2, 1);
    digitalWrite(B2, 1);

    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada2) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s8Bien = 1;
    }
    else
    {
        s8Bien = 0;
    }
}

void estadoSensores::monitorearS9()
{ 
    //S9
    s9Bien = 0;
    sumMonSen = 0;
    digitalWrite(A3, 0);
    digitalWrite(B3, 0);

    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada3) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s9Bien = 1;
    }
    else
    {
        s9Bien = 0;
    }
}

void estadoSensores::monitorearS10()
{ 
    //S10
    s10Bien = 0;
    sumMonSen = 0;
    digitalWrite(A3, 1);
    digitalWrite(B3, 0);

    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada3) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s10Bien = 1;
    }
    else
    {
        s10Bien = 0;
    }
}

void estadoSensores::monitorearS11()
{ 
    //S11
    s11Bien = 0;
    sumMonSen = 0;
    digitalWrite(A3, 0);
    digitalWrite(B3, 1);

    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada3) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s11Bien = 1;
    }
    else
    {
        s11Bien = 0;
    }
}

void estadoSensores::monitorearS12()
{ 
    //S12
    s12Bien = 0;
    sumMonSen = 0;
    digitalWrite(A3, 1);
    digitalWrite(B3, 1);

    for(int i = 0; i<100; i++)
    {
        if(digitalRead(multiplexorEntrada3) == 1)
        {
        sumMonSen++;
        }
        else
        {
        sumMonSen = sumMonSen;
        }
    }
    
    if(sumMonSen >= 95)
    {
        s12Bien = 1;
    }
    else
    {
        s12Bien = 0;
    }
}