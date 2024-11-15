#include <PubSubClient.h>
//we can set the way we transmit and receive data later
const char apn[]      = "iot.1nce.net";
const char gprsUser[] = "";
const char gprsPass[] = "";
const char* broker = "mqtt.thingsboard.cloud"; 
const int mqttPort = 1883; // Default MQTT port
const char* topicmqtt  = "v1/devices/me/telemetry";
const char* mqttUser = "$access token ";
int cntr=0;
int status=0;
unsigned long previousMillis = 0;  
const unsigned long interval = 1000; 
#define avg_tour 3
#define works_fine true        //make the code more practical
void callback(char* topic, byte* payload, unsigned int length) {
 //we can put the publish code here if we want to launch it after the status alarm arrived ----->more usefull
 //take into consideration memory limitation and copying the payload to avoid unexpected data comming later
}
PubSubClient client();

void setup() {
  Serial.begin(9600);
  pinMode(7,INPUT);
  client.setServer(broker, mqttPort);
  client.setCallback(callback);  //we need to define callback function
  //we can put the start time here if we are sure that the reference is in it initial  point
}

void loop() {
  #if !works_fine 
      //publish data to repair mode if it send to topic is repaired start again
      while(!status){
        boolean stats=reconnect();
        if(stats==true){
          status=stats;
          break; //quit the loop after fixing the error
        }

      }
  #endif
  if(digitalRead(7)==0){   //active reverse logic 0-->HIGH
    //start point time reference
    status=1;
    cntr=1;
    unsigned long startTime=millis();
  }
  if (status==1){
     while(startTime - previousMillis <= 1000){
      if(digitalRead(7)==0){
        cntr+=1;
      }
    }
    if(cntr!=avg_tour){
      //send mqtt message to launch an alarm of malfunction
      #undef works_fine
      #define works_fine false
      status=0;cntr=0;previousMillis = 0; 
      mqtt_fct();

    }else{   //it works normal
      cntr=0;
      previousMillis = 0; 
      status=0;

    }
  }
}
boolean reconnect() {
  while (!client.connected()) {
    if (client.connect("ArduinoClient", mqttUser, "")) {
      Serial.println("Reconnected to MQTT broker");
      client.subscribe("mqtt_topic"); 
      return true;
    } else {
      Serial.print("MQTT reconnection failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying...");
      delay(2000);
      return false;
    }
  }
}
