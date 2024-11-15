#include <SoftwareSerial.h>

SoftwareSerial sim808(10, 11);  // RX, TX

void setup() {
    Serial.begin(9600);
    sim808.begin(9600);

    delay(1000);
    Serial.println("Sending Telemetry Data to ThingsBoard via TCP");

  
}

void loop() {
    sim808.println("AT+CIPSTART=\"TCP\",\"thingsboard.cloud\",80");
    delay(2000);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // Create JSON formatted telemetry data
    String telemetryData = "{\"temp\":  150, \"humidity\":  150}";

    // Prepare TCP payload
    String tcpPayload = "POST /api/v1/97x6bTouG3w9kJHJ3ddC/telemetry HTTP/1.1\r\n";
    tcpPayload += "Host: thingsboard.cloud\r\n";
    tcpPayload += "Content-Type: application/json\r\n";
    tcpPayload += "Content-Length: " + String(telemetryData.length()) + "\r\n\r\n";
    tcpPayload += telemetryData;

    // Send TCP payload using AT+CIPSEND
    sim808.print("AT+CIPSEND=");
    sim808.println(tcpPayload.length());
    delay(1000);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }
    sim808.print(tcpPayload);
    delay(1000);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // Terminate TCP connection
    sim808.println("AT+CIPCLOSE");
    delay(2000);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // Deactivate GPRS context
    sim808.println("AT+SAPBR=0,1");
    delay(1000);

    delay(10000); 
}
