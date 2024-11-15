#include <SoftwareSerial.h>

SoftwareSerial sim808(10, 11);  // RX, TX

void setup() {
    Serial.begin(9600);
    sim808.begin(9600);

    delay(1000);
    Serial.println("SIM Card and Network Check");
}

void loop() {
    // Check modem responsiveness
    sim808.println("AT");
    delay(500);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // Check SIM card status
    sim808.println("AT+CPIN?");
    delay(500);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // Check network registration
    sim808.println("AT+CREG?");
    delay(500);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // Check signal strength
    sim808.println("AT+CSQ");
    delay(500);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // Check operator information
    sim808.println("AT+COPS?");
    delay(500);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // Check GPRS/Internet connectivity (optional)
    sim808.println("AT+CGATT?");
    delay(500);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    delay(10000); // Wait before looping again
}
