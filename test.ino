#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include<ArduinoJson.h>
#include<time.h>

#define pin 4
#define type DHT11
DHT dht(pin,type);

const char* Wifi_ssid = "Redmi Note 13 5G";
const char* Wifi_password = "12345678";

const float threshold = 35.0;
const char* DEVICE_ID = "CC_TEST_01";

const char* mqtt_Server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* MQTT_TOPIC = "CC_TEST_01/temperature";

WiFiClient espClient;
PubSubClient mqttClient(espClient);


unsigned long timegetting(){
  time_t now;
  time(&now);
  return (unsigned long)now;
}


void wificonnect(){
  Serial.println("Connecting to Wifi...");
  WiFi.begin(Wifi_ssid,Wifi_password);
  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi Connected");
}
configTime(0, 0, "pool.ntp.org", "time.nist.gov");


void mqttconnect(){
  while(!mqttClient.connected()){
    Serial.println("Connecting to MQTT broker..");
    String clientID = DEVICE_ID;
    
    clientID += "_";
    clientID += String(random(0xffff), HEX);

    if (mqttClient.connect(clientID.c_str()))
    {
      Serial.println("MQTT connected!");
    }
    else
    {
      Serial.print("MQTT connection failed. State = ");
      Serial.println(mqttClient.state());
      delay(2000);
    }
    
  }
}

void data(){
  float temp =dht.readTemperature(); 
  float hum = dht.readHumidity();

  const char* flag;
  if(temp>= threshold){
    flag="ALERT";
  }else{
    flag="NORMAL";
  }

  JsonDocument doc;
  doc["device_id"] = DEVICE_ID;
  doc["timestamp"] = timegetting();
  doc["sensor_value"] = temp;
  doc["humidity"] = hum;
  doc["status"] = flag;

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);
  mqttClient.publish(MQTT_TOPIC, jsonBuffer);

}



void setup() {
  Serial.begin(115200);  

  dht.begin();
  delay(2000);

  wificonnect();

  mqttClient.setServer(mqtt_Server,mqtt_port);
  mqttconnect();

}
unsigned long lasttime=0;

void loop() {
  if(WiFi.status() !=WL_CONNECTED){
    wificonnect();
  }
  if(!mqttClient.connected()){
    mqttconnect();
  }
  mqttClient.loop();

  unsigned long currtime=millis();
  if(currtime-lasttime>=5000){
    lasttime = currtime;
    data();
  } 
}
