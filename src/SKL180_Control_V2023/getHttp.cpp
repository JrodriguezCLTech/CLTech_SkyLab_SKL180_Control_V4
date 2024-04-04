#include "getHttp.h"

//Funcion para movimiento de la nevera por pasos
void getHttp::getW5100()
{  
    Ethernet.begin(mac);
    delay(1000);
    Serial.println("Conectando...");

    if (client.connect(serverIP, 36810))
    {
        Serial.println("Conectado al servidor");
        client.println("GET /api/nova/check-connection-session HTTP/1.1");
        client.println("Host: 181.48.43.69:36810");
        client.println("Authorization: Bearer $2b$10$EC9cpQNXLQ0IKfn.xreHkO4upirFWeaDXcr..BPj1zxmdW4PDEjrq");
        client.println("Connection: close");
        varAuxCiclico = true;
        client.println();
    }
    
    else 
    {
        Serial.println("Fallo al conectar al servidor");
    }

    while (varAuxCiclico == true)
    {
        if (client.available()) 
        {
            char c = client.read();
            //Serial.print(c);
            
            if(c == '{')
            {
                x = true;
            }

            if(x == true)
            {
                if(c == '}')
                {
                    getString += c;
                    getStringComplete = true;
                    x = false;
                }
                else
                {
                    getString += c;
                }
            }
        }
    
        if(getStringComplete == true)
        {
            // Serial.println("..Get realizado correctamente..");
            // Serial.println("El mensaje leido es:");
            Serial.println(getString);
            getString = "";
            getStringComplete = false;
        }

        if (!client.connected()) {
            Serial.println();
            Serial.println("Desconectado");
            varAuxCiclico = false;
            client.stop();
        }
    }
}