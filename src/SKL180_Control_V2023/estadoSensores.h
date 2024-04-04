#ifndef estadoSensores_h
#define estadoSensores_h

#include <Arduino.h>
#include "Pins.h"
#include "GV.h"

class estadoSensores
{
    private:
        int sumMonSen;
        bool s1Bien;
        bool s2Bien;
        bool s3Bien;
        bool s4Bien;
        bool s5Bien;
        bool s6Bien;
        bool s7Bien;
        bool s8Bien;
        bool s9Bien;
        bool s10Bien;
        bool s11Bien;
        bool s12Bien;
        void monitorearS1();
        void monitorearS2();
        void monitorearS3();
        void monitorearS4();
        void monitorearS5();
        void monitorearS6();
        void monitorearS7();
        void monitorearS8();
        void monitorearS9();
        void monitorearS10();
        void monitorearS11();
        void monitorearS12();
        void initVar();
        
    public:
        int estadoSistema[2] = {};
        int estadosSubsistemas[12] = {};      
        estadoSensores();   //constructor
        void monitoreoSensores();
        void monitoreoSensores2();
        void monitoreoVectorEstadoSistema();
};
#endif