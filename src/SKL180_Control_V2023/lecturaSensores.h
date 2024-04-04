#ifndef lecturaSensores_h
#define lecturaSensores_h

#include <Arduino.h>
#include "Pins.h"
#include "GV.h"

class lecturaSensores {
    private:
    public:
        int SO1;
        int SO2;
        int SO3;
        int SO4;
        int SO5;
        int SO6;
        int SO7;
        int SO8;
        int SH1;
        int SH2;
        int SH3;
        int SH4;
        int SH5;
        int SH6;
        int SH7;
        float valorSH7;
        float voltajeSH7;
        lecturaSensores();   //constructor
        void leerSensoresTCRT5000();
        void leerSensoresTCST2103();
        void deteccionSensores();
        int varIOTSensores[14] = {}; 
};
#endif