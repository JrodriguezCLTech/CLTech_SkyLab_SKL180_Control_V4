#include <Arduino.h>
#include "GV.h"

class MainSerialVector
{
    private:
    
    public:
        String inputString;
        bool stringComplete;
        int datoCompleto;
        void init();
        void serialEvent();
        void leerVector();
};