#include "GV.h"

class getHttp
{
private:
    bool x;
    bool getStringComplete;
    String getString;
    char jsonBuffer[1024]; // Tamaño del buffer para almacenar los datos JSON recibidos

public:
    void getW5100();
};
