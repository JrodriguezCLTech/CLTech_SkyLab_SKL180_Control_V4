#include "postHttp.h"

// MÉTODO PARA RUTINA PRINCIPAL SKL-180 (RECOGER TUBO EN LINEA Y DEJARLO EN SISTEMA ROTULACION)
void postHttp::postW5100()
{   
    Ethernet.begin(mac);
    delay(1000);
    Serial.println("Conectando...");

    if (client.connect(serverIP, port)) 
    {
        Serial.println("Conectado al servidor");
        
        // Construir el cuerpo del mensaje POST
        String postData = "/:session/send-message";
        
        JsonDocument docJsonPost;

        docJsonPost["HMG"] =  vectVarIniciales[0];
        docJsonPost["SR"] =  vectVarIniciales[1];
        docJsonPost["V_PT"] =  vectVarIniciales[2];
        docJsonPost["V_RT"] =  vectVarIniciales[3];
        docJsonPost["stepsYHomeToPickTube"] =  vectVarIniciales[4];
        docJsonPost["stepsYHomeToReleaseTube"] =  vectVarIniciales[5];
        docJsonPost["stepsXCalibrateLineX"] =  vectVarIniciales[6];
        docJsonPost["stepsXLine1"] =  vectVarIniciales[7];
        docJsonPost["stepsXLine2"] =  vectVarIniciales[8];
        docJsonPost["stepsXLine3"] =  vectVarIniciales[9];
        docJsonPost["stepsXLine4"] =  vectVarIniciales[10];
        docJsonPost["stepsXCalibrateReleaseTube"] =  vectVarIniciales[11];
        docJsonPost["rpmMaxX"] =  vectVarIniciales[12];
        docJsonPost["rpmMaxY"] =  vectVarIniciales[13];
        docJsonPost["rpmMediaX"] =  vectVarIniciales[14];
        docJsonPost["rpmMediaY"] =  vectVarIniciales[15];
        docJsonPost["acelerationX"] =  vectVarIniciales[16];
        docJsonPost["acelerationY"] =  vectVarIniciales[17];
        
        String docStringData;
        serializeJson(docJsonPost, docStringData);
        Serial.println(docStringData);
        
        // Realizar la solicitud HTTP POST
        client.println("POST /api/nova/send-message HTTP/1.1");
        client.println("Host: 181.48.43.69:36810");
        client.println("Authorization: Bearer $2b$10$EC9cpQNXLQ0IKfn.xreHkO4upirFWeaDXcr..BPj1zxmdW4PDEjrq");
        client.println("Content-Type: application/json");
        client.print("Content-Length: ");
        client.println(docStringData.length());
        client.println();
        client.print(docStringData);
        varAuxCiclico = true;
    } 
    else 
    {
        Serial.println("Error de conexión");
    }

    while (varAuxCiclico == true)
    {
        if (client.available()) 
        {
            char c = client.read();
            Serial.print(c);
        }

        if (!client.connected()) 
        {
            Serial.println();
            Serial.println("Desconectado");
            varAuxCiclico = false;
            client.stop();
        }
    }
}
