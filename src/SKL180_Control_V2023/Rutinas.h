#include <EEPROM.h>
#include <avr/wdt.h>
#include "Eprom.h"
#include "GV.h"
#include "lecturaSensores.h"

class Rutinas
{
private:
    /* data */
    bool varSinRot;
    bool goToL1;
    bool goToL2;
    bool goToL3;
    bool goToL4;
    bool tuboExpOk;
    int auxHist;

public:
    void RecogerTubo(String);
    void RecogerYDevolverTubo(String);
    void RotularTubo();
    void Rotulado();
    void LiberarTubo();
    void griperOpen();
    void griperClose();
    void RotularTubo2Sensores();
    void RotularTubo1Sensor();
    void RotularTuboSinSensores();
    int estapasProcesoEquipo[12] = {};
    Eprom EProm;
    lecturaSensores lecturaSensoresAux;
    void procesoIOT();
    void procesoIOTprueba();
    void procesoIOTpruebaSensores();
    void stopIOT();
    void apagarActuadores();
    void contadoresIOT();
    void verContadores();
    String varIOT[20] = {};
    int sinTubo;
    void historialFallos();
    void verHistorialFallos();
    String vecHistFallos[1] = {};
    void LiberarTuboSRFallo();
    void monitorearSensoresHabilitados();
    String sensoresHabilitados[17] = {};
    void ultimoFallo();
    void historialFallo2();
};
