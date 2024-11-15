#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_MODEM_SIM808
#define TINY_GSM_MODEM_SIM900
#define SerialMon Serial

#include <SoftwareSerial.h>
SoftwareSerial SerialAT(10, 11);  // RX, TX

// See all AT commands, if wanted  Optional
// #define DUMP_AT_COMMANDS

#define TINY_GSM_DEBUG SerialMon

#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200

#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false


// GPRS credentials:
const char apn[]      = "iot.1nce.net";
const char gprsUser[] = "";
const char gprsPass[] = "";

// MQTT details
const char* broker = "mqtt.thingsboard.cloud"; 
const char* topicmqtt  = "v1/devices/me/telemetry";
const char* mqttUser = "gRoq5wOOX0uZUm3ZoIsh";

#include <TinyGsmClient.h>
#include <PubSubClient.h>

TinyGsm        modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient  mqtt(client);
//---------------------------------------------

uint32_t lastReconnectAttempt = 0;
//---------------------------------------------
void mqttCallback(char* topic, byte* payload, unsigned int len) {
  SerialMon.print("Message arrived [");
  SerialMon.print(topic);
  SerialMon.print("]: ");
  SerialMon.write(payload, len);
  SerialMon.println();
}
//String payload = "{\"temp\":  90, \"humidity\":  105}";

boolean mqttConnect() {
  SerialMon.print("Connecting to ");
  SerialMon.print(broker);

  // Connect to MQTT Broker
  boolean status_mq = mqtt.connect("arduinoClient",mqttUser,"");
  if (status_mq == false) {
    SerialMon.println(" fail");
    return false;
  }
  while(status_mq){
    float randomTemperature = random(0, 90);
    float randomHumidity = random(60, 150);
    float frequency = random(0, 50);
    float power=random(190,250);
    float current=20;
    float voltage=random(220,250);
    float status2 = random(0, 2);
    float battery= random(0, 12);
    String status= "active";   //create if condition;1-->active and recursively
    String payload = "{\"temp\":" + String(randomTemperature, 1) +
                     ",\"humidity\":" + String(randomHumidity, 1) + 
                     ",\"Battery\":" + String(battery, 1) +
                     ",\"power\":" + String(power, 1) + 
                     ",\"Voltage\":" + String(voltage, 1) + 
                     ",\"current\":" + String(current, 1) + 
                     ",\"frequency\":" + String(frequency, 1) +
                     ",\"status\":" + status + 
                     ",\"light\":" + String(status2, 1) + "}";

    SerialMon.println(" success");
    mqtt.publish(topicmqtt,payload.c_str());
    //the battery should be placed outside the loop so it can decrease the value
    delay(5000);
  }
  //SerialMon.println(" success");
  //mqtt.publish(topicmqtt,payload.c_str());
  return mqtt.connected();
}


void setup() {
  SerialMon.begin(115200);
  delay(10);
  SerialMon.println("Wait...");

  //TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  SerialAT.begin(9600);
  delay(6000);

  SerialMon.println("Initializing modem...");
  modem.restart();
  // modem.init();  if restart takes some time use this instead

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);


  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success_OK");

  if (modem.isNetworkConnected()) { SerialMon.println("Network connected"); }

#if TINY_GSM_USE_GPRS
  SerialMon.print(F("Connecting to "));
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isGprsConnected()) { SerialMon.println("GPRS connected"); }
#endif

  // MQTT Broker setup
  mqtt.setServer(broker, 1883);
  mqtt.setCallback(mqttCallback);
}

void loop() {
  // check the network is registred
  if (!modem.isNetworkConnected()) {
    SerialMon.println("Network disconnected");
    if (!modem.waitForNetwork(180000L, true)) {
      SerialMon.println(" fail");
      delay(10000);
      return;
    }
    if (modem.isNetworkConnected()) {
      SerialMon.println("Network re-connected");
    }

#if TINY_GSM_USE_GPRS
    // and make sure GPRS/EPS is still connected
    if (!modem.isGprsConnected()) {
      SerialMon.println("GPRS disconnected!");
      SerialMon.print(F("Connecting to "));
      SerialMon.print(apn);
      if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
        SerialMon.println(" fail");
        delay(10000);
        return;
      }
      if (modem.isGprsConnected()) { SerialMon.println("GPRS reconnected"); }
    }
#endif
  }

  if (!mqtt.connected()) {
    SerialMon.println("!!! MQTT NOT CONNECTED !!!???");
    // Reconnect every 10 seconds
    uint32_t t = millis();
    if (t - lastReconnectAttempt > 10000L) {
      lastReconnectAttempt = t;
      if (mqttConnect()) { lastReconnectAttempt = 0; }
    }
    delay(100);
    return;
  }

  mqtt.loop();
}
