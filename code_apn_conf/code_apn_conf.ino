#include <SoftwareSerial.h>

SoftwareSerial sim808(10, 11);  // RX, TX

void setup() {
    Serial.begin(9600);
    sim808.begin(9600);

    delay(1000);
    Serial.println("APN Configuration and GPRS Test");
}

void loop() {
    // Set APN settings 
    sim808.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    delay(500);
    sim808.println("AT+SAPBR=3,1,\"APN\",\"iot.1nce.net\"");
    delay(500);

    // Activate the GPRS context
    sim808.println("AT+SAPBR=1,1");
    delay(1000);

    // Check GPRS context activation
    sim808.println("AT+SAPBR=2,1");
    delay(500);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // If context is active, send  AT command to an external server
    if (gprsContextActive()) {
        sim808.println("AT+HTTPINIT");
        delay(1000);
        while (sim808.available()) {
            char c = sim808.read();
            Serial.write(c);
        }
        sim808.println("AT+HTTPPARA=\"CID\",1");
        delay(1000);
        while (sim808.available()) {
            char c = sim808.read();
            Serial.write(c);
        }
        sim808.println("AT+HTTPPARA=\"URL\",\"http://google.com\"");
        delay(1000);
        while (sim808.available()) {
            char c = sim808.read();
            Serial.write(c);
        }
        sim808.println("AT+HTTPACTION=0");
        delay(1000);
        while (sim808.available()) {
            char c = sim808.read();
            Serial.write(c);
        }
        sim808.println("AT+HTTPREAD");
        delay(1000);
        while (sim808.available()) {
            char c = sim808.read();
            Serial.write(c);
        }
        sim808.println("AT+HTTPTERM");
        delay(1000);
        while (sim808.available()) {
            char c = sim808.read();
            Serial.write(c);
        }
    }

    delay(30000); 
}

bool gprsContextActive() {
    sim808.println("AT+SAPBR=2,1");
    delay(500);
    String response = "";
    while (sim808.available()) {
        char c = sim808.read();
        response += c;
    }
    return response.indexOf("+SAPBR: 1,1") != -1;
}
