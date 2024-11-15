
#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_MODEM_SIM808
#define TINY_GSM_MODEM_SIM900
#include <TinyGsmClient.h>
#include <SoftwareSerial.h>
#include <ThingsBoard.h>

#if THINGSBOARD_ENABLE_PROGMEM
constexpr char APN[] PROGMEM = "iot.1nce.net";
constexpr char USER[] PROGMEM = "";
constexpr char PASS[] PROGMEM = "";
#else
constexpr char APN[] = "iot.1nce.net";
constexpr char USER[] = "";
constexpr char PASS[] = "";
#endif

#if THINGSBOARD_ENABLE_PROGMEM
constexpr char TOKEN[] PROGMEM = "97x6bTouG3w9kJHJ3ddC";
#else
constexpr char TOKEN[] = "97x6bTouG3w9kJHJ3ddC";
#endif

#if THINGSBOARD_ENABLE_PROGMEM
constexpr char THINGSBOARD_SERVER[] PROGMEM = "thingsboard.cloud";
#else
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud";
#endif
#if THINGSBOARD_ENABLE_PROGMEM
//USING MQTT PROTOCOL
constexpr uint16_t THINGSBOARD_PORT PROGMEM = 1883U;
#else
constexpr uint16_t THINGSBOARD_PORT = 1883U;
#endif
#if THINGSBOARD_ENABLE_PROGMEM
constexpr uint32_t MAX_MESSAGE_SIZE PROGMEM = 128U;
#else
constexpr uint32_t MAX_MESSAGE_SIZE = 128U;
#endif
#if THINGSBOARD_ENABLE_PROGMEM
constexpr uint32_t SERIAL_DEBUG_BAUD PROGMEM = 115200U;
#else
constexpr uint32_t SERIAL_DEBUG_BAUD = 115200U;
#endif

#if THINGSBOARD_ENABLE_PROGMEM
constexpr char CONNECTING_MSG[] = "Connecting to: (%s) with token (%s)";
constexpr char TEMPERATURE_KEY[] PROGMEM = "temp";
constexpr char HUMIDITY_KEY[] PROGMEM = "humidity";
#else
constexpr char CONNECTING_MSG[] = "Connecting to: (%s) with token (%s)";
constexpr char TEMPERATURE_KEY[] = "temp";
constexpr char HUMIDITY_KEY[] = "humidity";
#endif

SoftwareSerial serialGsm(10U, 11U); 
TinyGsm modem(serialGsm);
TinyGsmClient client(modem);
ThingsBoard tb(client, MAX_MESSAGE_SIZE);
bool modemConnected = false;


void setup() {
  randomSeed(analogRead(0));
  Serial.begin(SERIAL_DEBUG_BAUD);
  serialGsm.begin(115200);
  delay(3000);
  serialGsm.write("AT+IPR=9600\r\n");
  serialGsm.end();
  serialGsm.begin(9600);


#if THINGSBOARD_ENABLE_PROGMEM
  Serial.println(F("Initializing modem..."));
#else
  Serial.println("Initializing modem...");
#endif
  modem.restart();

  String modemInfo = modem.getModemInfo();
#if THINGSBOARD_ENABLE_PROGMEM
  Serial.print(F("Modem: "));
#else
  Serial.print("Modem: ");
#endif
  Serial.println(modemInfo);
}

void loop() {
  delay(1000);

  if (!modemConnected) {
#if THINGSBOARD_ENABLE_PROGMEM
    Serial.print(F("Waiting for network..."));
#else
    Serial.print("Waiting for network...");
#endif
    if (!modem.waitForNetwork()) {
#if THINGSBOARD_ENABLE_PROGMEM
        Serial.println(F(" fail"));
#else
        Serial.println(" fail");
#endif
        delay(10000);
        return;
    }
#if THINGSBOARD_ENABLE_PROGMEM
    Serial.println(F(" OK"));
#else
    Serial.println(" OK");
#endif

#if THINGSBOARD_ENABLE_PROGMEM
    Serial.print(F("Connecting to "));
#else
    Serial.print("Connecting to ");
#endif
    Serial.print(APN);
    if (!modem.gprsConnect(APN, USER, PASS)) {
#if THINGSBOARD_ENABLE_PROGMEM
        Serial.println(F(" fail"));
#else
        Serial.println(" fail");
#endif
        delay(10000);
        return;
    }

    modemConnected = true;
#if THINGSBOARD_ENABLE_PROGMEM
    Serial.println(F(" OK"));
#else
    Serial.println(" OK");
#endif
  }

  if (!tb.connected()) {
    char message[ThingsBoard::detectSize(CONNECTING_MSG, THINGSBOARD_SERVER, TOKEN)];
    snprintf_P(message, sizeof(message), CONNECTING_MSG, THINGSBOARD_SERVER, TOKEN);
    Serial.println(message);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
#if THINGSBOARD_ENABLE_PROGMEM
      Serial.println(F("Failed to connect"));
#else
      Serial.println("Failed to connect");
#endif
      return;
    }
  }

#if THINGSBOARD_ENABLE_PROGMEM
  Serial.println(F("Sending temperature data..."));
#else
  Serial.println("Sending temperature data...");
#endif
  tb.sendTelemetryInt(TEMPERATURE_KEY, random(0, 90));

#if THINGSBOARD_ENABLE_PROGMEM
  Serial.println(F("Sending humidity data..."));
#else
  Serial.println("Sending humidity data...");
#endif
  tb.sendTelemetryFloat(HUMIDITY_KEY, random(10, 150));
  delay(7000);
  tb.loop();
}
