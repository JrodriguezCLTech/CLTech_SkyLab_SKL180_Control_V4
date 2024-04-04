#include "Main.h"

// RUTINA PRINCIPAL DE CLASE (SE EJECUTA CON LAS INTERRUPCIONES DEL TIMER1)
void Main::ISRMode() {
    vlr_sensor_ln1 =  digitalRead(sensor_linea1);
    vlr_sensor_ln2 =  digitalRead(sensor_linea2);
    vlr_sensor_ln3 =  digitalRead(sensor_linea3);
    vlr_sensor_ln4 =  digitalRead(sensor_linea4);
    vlr_sensor_tubo = digitalRead(sensor_tubo);
    vlr_sensor_rotulado1 = digitalRead(sensor_rotulado1);
    vlr_sensor_rotulado1 = digitalRead(sensor_rotulado2);
    e_endX = digitalRead(X_MIN_PIN);
    e_endY = digitalRead(Y_MIN_PIN);
    
    if (flag_time == true) {
        cnt_time+=10;
        //Serial.println(cnt_time);
        if (cnt_time >= 200) {
            flag_time = false;
            cnt_time = 0;
            pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
            //Servos[0].write(HMG);
            delay(600);
            pinMode(servoMotorOn, INPUT); // APAGO MOTOR
            // Fija la posicion del servo de acuerdo al valor definido
            analogWrite(motor_rotulado_a, 0);
            analogWrite(motor_rotulado_b, 0);
        }
    }
    if (flag_time2 == true) {
        cnt_time2+=10;
        //Serial.println(cnt_time2);
        if (cnt_time2 >= 20) {
            flag_time2 = false;
            cnt_time2 = 0;
            banderaSRFallo = true;
        }
    }
}
