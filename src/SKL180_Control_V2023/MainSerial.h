#include <EEPROM.h>
#include "Rutinas_prueba.h"
#include "Rutinas.h"
#include "GV.h"
#include "estadoSensores.h"
#include "Eprom.h"
#include "lecturaSensores.h"
#include "MainSerialVector.h"
#include "getHttp.h"
#include "postHttp.h"

class MainSerial {
public:
    void conect();
    void Run(String);
    int init1;
    Rutinas rutinas;
    Rutinas_prueba rutinas_prueba;
    estadoSensores estadoSensoresAux;
    Eprom EpromAux;
    lecturaSensores lecturaSensoresAux;
    MainSerialVector MainSerialVectorAux;
    getHttp getHttpAux;
    postHttp postHttpAux;
    
private:
    Rutinas_prueba rutinas_p;
    int varPrueba = 0;
};
