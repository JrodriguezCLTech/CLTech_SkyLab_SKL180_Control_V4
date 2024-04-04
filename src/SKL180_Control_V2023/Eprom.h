#ifndef Eprom_h
#define Eprom_h

#include <EEPROM.h>
#include "GV.h"

class Eprom {
    private:
    
    public:
        void initEprom(); 
        void leerIOT();
        void leerInit();
        void borrarEEPROM();
        void guardarEEPROMPredet();
        void leerEEPROMPredet();
};

#endif