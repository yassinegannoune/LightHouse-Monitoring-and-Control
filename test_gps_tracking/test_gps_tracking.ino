#include <SoftwareSerial.h>

SoftwareSerial sim808(10, 11);  // RX, TX

void setup() {
    Serial.begin(9600);
    sim808.begin(9600);

    delay(1000);
    Serial.println("SIM808 Test");
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

    // Retrieve operator information
    sim808.println("AT+COPS?");
    delay(500);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }
    //retieve sim number
    sim808.println("AT+CNUM");
    delay(500);
    while (sim808.available()) {
        char c = sim808.read();
        Serial.write(c);
    }

    // Send an SMS
    //sim808.println("AT+CMGF=1");  // Set SMS mode to text
    //delay(500);
    //sim808.println("AT+CMGS="212***********""); // Replace with recipient's number
    //delay(500);
    //sim808.print("Hello, this is a test SMS from SIM808!");
    //delay(500);
    //sim808.write(0x1A); // Send Ctrl+Z to end the message
    //delay(5000); // Wait for SMS to be sent

    // Make a call
    sim808.println("ATD+212***********;"); // Replace with recipient's number
    delay(30000); // Wait for the call to connect for 10 seconds
    sim808.println("ATH"); // Hang up the call

    delay(10000); // Wait before looping again
}
