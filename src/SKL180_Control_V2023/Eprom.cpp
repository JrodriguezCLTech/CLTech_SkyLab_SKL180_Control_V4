#include "Eprom.h"

// MÉTODO PARA INICIALIZAR MEMORIA EEPROM
void Eprom::initEprom() {
    //*Iniciacion de Variables EEPROM*//
    if (value == 255 or true) {
        EEPROM.write(20, HMG);
        EEPROM.write(21, SR);
        EEPROM.write(22, SL);
        EEPROM.write(25, V_PT);
        EEPROM.write(26, RTD);
        EEPROM.write(27, V_RT);
    } else if (flag_first == false and false) {
        HMG = EEPROM.read(20);
        SR = EEPROM.read(21);
        SL = EEPROM.read(22);
        V_PT = EEPROM.read(25);
        RTD = EEPROM.read(26);
        V_RT = EEPROM.read(27);
        flag_first = true;
        // Serial.println("@Conectado&");

        //Variables IOT Proceso
        leerIOT();
    }
}
 
void Eprom::leerIOT() {
    EEPROM.get(120, contaTubOk);
    EEPROM.get(130, contaTubNotOk);
    EEPROM.get(140, contaFallos);
    EEPROM.get(500, contaTubosL1);
    EEPROM.get(510, contaTubosL2);
    EEPROM.get(520, contaTubosL3);
    EEPROM.get(530, contaTubosL4);
}

void Eprom::leerInit() {
    EEPROM.get(600, varSO1);
    EEPROM.get(610, varSO2);
    EEPROM.get(620, varSO3);
    EEPROM.get(630, varSO4);
    EEPROM.get(640, varSO5);
    EEPROM.get(650, varSO6);
    EEPROM.get(660, varSO7);
    EEPROM.get(670, varSO8);
    EEPROM.get(680, varSH1);
    EEPROM.get(690, varSH2);
    EEPROM.get(700, varSH3);
    EEPROM.get(710, varSH4);
    EEPROM.get(720, varSH5);
    EEPROM.get(730, varSH6);
    EEPROM.get(740, varSH7);
    EEPROM.get(750, varSSR);
    EEPROM.get(760, varSGPR);   
}

void Eprom::borrarEEPROM() {
    for (int E = 0; E < EEPROM.length(); E++)
    {
        EEPROM.write(E, 0);   // Itera por toda la EEPROM y reemplaza cualquier valor que esté en algún byte por cero
    } 
}

void Eprom::guardarEEPROMPredet() {
    EEPROM.put(800, HMG);
    EEPROM.put(810, SR);
    EEPROM.put(820, V_PT);
    EEPROM.put(830, V_RT);
    EEPROM.put(840,stepsYHomeToPickTube);
    EEPROM.put(850,stepsYHomeToReleaseTube);
    EEPROM.put(860,stepsXCalibrateLineX);
    EEPROM.put(870,stepsXLine1);
    EEPROM.put(880,stepsXLine2);
    EEPROM.put(890,stepsXLine3);
    EEPROM.put(900,stepsXLine4);
    EEPROM.put(910,stepsXCalibrateReleaseTube); 
    EEPROM.put(920,rpmMaxX);
    EEPROM.put(930,rpmMaxY);
    EEPROM.put(940,rpmMediaX);
    EEPROM.put(950,rpmMediaY);
    EEPROM.put(960,acelerationX);
    EEPROM.put(970,acelerationY);
}

void Eprom::leerEEPROMPredet() {
    EEPROM.get(800, HMG);
    EEPROM.get(810, SR);
    EEPROM.get(820, V_PT);
    EEPROM.get(830, V_RT);
    EEPROM.get(840,stepsYHomeToPickTube);
    EEPROM.get(850,stepsYHomeToReleaseTube);
    EEPROM.get(860,stepsXCalibrateLineX);
    EEPROM.get(870,stepsXLine1);
    EEPROM.get(880,stepsXLine2);
    EEPROM.get(890,stepsXLine3);
    EEPROM.get(900,stepsXLine4);
    EEPROM.get(910,stepsXCalibrateReleaseTube); 
    EEPROM.get(920,rpmMaxX);
    EEPROM.get(930,rpmMaxY);
    EEPROM.get(940,rpmMediaX);
    EEPROM.get(950,rpmMediaY);
    EEPROM.get(960,acelerationX);
    EEPROM.get(970,acelerationY);
}