#include "PinMode.h"

// MÉTODO PARA CONFIGURAR TODOS LOS PINES DEL MCU
void PinMode::initPin() {
        pinMode(X_STEP_PIN, OUTPUT);
        pinMode(X_DIR_PIN, OUTPUT);
        pinMode(X_ENABLE_PIN, OUTPUT);
        //pinMode(X_MAX_PIN, INPUT);
        pinMode(X_MIN_PIN, INPUT);

        pinMode(Y_STEP_PIN, OUTPUT);
        pinMode(Y_DIR_PIN, OUTPUT);
        pinMode(Y_ENABLE_PIN, OUTPUT);
        //pinMode(Y_MAX_PIN, INPUT);
        pinMode(Y_MIN_PIN, INPUT);

        digitalWrite(X_ENABLE_PIN, LOW);
        digitalWrite(Y_ENABLE_PIN, LOW);

        pinMode(sensor_rotulado1, INPUT_PULLUP);
        pinMode(sensor_rotulado2, INPUT_PULLUP);
        pinMode(sensor_tubo, INPUT_PULLUP);
        pinMode(sensor_Home_SR, INPUT_PULLUP);

        pinMode(sensor_linea1, INPUT);
        pinMode(sensor_linea2, INPUT);
        pinMode(sensor_linea3, INPUT);
        pinMode(sensor_linea4, INPUT);

        pinMode(servoMotorOn, OUTPUT);
        
        pinMode(motorOn    , OUTPUT);
        digitalWrite(motorOn, HIGH);
        pinMode(gripClose    , OUTPUT);

        pinMode(motor_rotulado_a, OUTPUT);
        digitalWrite(motor_rotulado_a, HIGH);
        pinMode(motor_rotulado_b, OUTPUT);
        digitalWrite(motor_rotulado_b, HIGH);

        analogWrite(motor_rotulado_a, 0);
        analogWrite(motor_rotulado_b, 0);

        //Monitoreo IOT Estado Sensores
        pinMode(multiplexorEntrada, INPUT_PULLUP);
        pinMode(A1, OUTPUT);
        pinMode(B1, OUTPUT);
        pinMode(multiplexorEntrada2, INPUT_PULLUP);
        pinMode(A2, OUTPUT);
        pinMode(B2, OUTPUT);
        pinMode(multiplexorEntrada3, INPUT_PULLUP);
        pinMode(A3, OUTPUT);
        pinMode(B3, OUTPUT);
}
