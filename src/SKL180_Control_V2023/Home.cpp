#include "Home.h"

// RUTINA PARA MANTENER EN HOME EL SISTEMA CNC MIENTRAS NO SE UTILICE
void Home::initHome() {
    bool xHome = false;
    bool yHome = false;
    stepperAX._idMotor = 3;
    stepperAY._idMotor = 3;

    while (not xHome or not yHome) {
        stepperAX.procesarCNC();
        stepperAY.procesarCNC();

        if (not stepperAY.finCarreraDetectado and not stepperAY.home) {
            yHome = false;
            stepperAY.homeMotorFin();
            stepperAX.resetearTodasBanderas();
        }
    
        if (yHome and not stepperAX.finCarreraDetectado and not stepperAX.home) {
            stepperAX.homeMotorFin();
        }
    
        if (stepperAX.finCarreraDetectado and not stepperAX.home) {
            xHome = true;
        }
    
        if (stepperAY.finCarreraDetectado and not stepperAY.home) {
            yHome = true;
        }
        
        if (stepperAX.home) {
            stepperAX.control();
        } 
        if (stepperAY.home) {
            stepperAY.control();
        }
    }
    
    stepperAX._idMotor = 0;
    stepperAY._idMotor = 1;
}
