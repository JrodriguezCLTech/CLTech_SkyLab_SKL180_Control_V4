#include "MainSerialVector.h"

//Funcion para iniciar las variables de la comunicacion serial
void MainSerialVector::init()
{
    inputString = "";           //Variable en donde guardamos el dato
    stringComplete = false;     //Variable que nos indica si el dato ya esta completo o no
}


//Funcion que delimita la lectura del vector extrayendo unicamente los valores que se encuentren entre los corchetes [...]
void MainSerialVector::serialEvent()
{
    while(variableSolicitar == 1 && Serial.available())
    {
        char inChar = (char)Serial.read();
        if(inChar == ']')
        {
            stringComplete = true;
        }
        else
        {
            if(inChar != '[')
            {
                inputString += inChar;
            }
        }
    }
    
    if(stringComplete)
    {
        datoCompleto = 1;
        leerVector();
    }
}

//Funcion que se encarga de asignar la lectura de cada posicion del vector recibido a la misma posicion del vector del programa
void MainSerialVector::leerVector()
{    
    variableSolicitar = 0;

    char delimitador = ',';
    char inputStringcharArray[inputString.length() + 1];
    inputString.toCharArray(inputStringcharArray, sizeof(inputStringcharArray));

    char *token = strtok(inputStringcharArray, &delimitador);

    while (token != NULL) {
        for (int i=0; i<=17 ; i++)
        {
            vectVarIniciales[i] = atof(token);
            token = strtok(NULL, &delimitador);
        }
    }

    //Se restaura el valor inicial de las variables de comunicacion
    inputString = "";               //La variable en la cual se guarda el mensaje se limpia y deja vacia
    stringComplete = false;         //La variable de dato completo vuelve a su estado inicial
}