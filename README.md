# ESP32 DHT11 MQTT Temperature Monitoring

## Overview

This project uses an ESP32 and DHT11 sensor to measure temperature and humidity and publish the sensor data to an MQTT broker.

The ESP32 connects to Wi-Fi, reads the DHT11 sensor every 5 seconds, creates a JSON message, and publishes it to the MQTT topic.

## Components

* ESP32
* DHT11 Temperature & Humidity Sensor
* Jumper wires
* Breadboard
* Wi-Fi connection

## Software & Libraries

* Arduino IDE
* WiFi.h
* PubSubClient
* DHT.h
* ArduinoJson
* time.h

## MQTT Configuration

**MQTT Broker:** `test.mosquitto.org`

**MQTT Port:** `1883`

**MQTT Topic:** `CC_TEST_01/temperature`

**Device ID:** `CC_TEST_01`

## DHT11 Connection

| DHT11 | ESP32  |
| ----- | ------ |
| VCC   | 3.3V   |
| DATA  | GPIO 4 |
| GND   | GND    |

## Working

1. ESP32 connects to the configured Wi-Fi network.
2. ESP32 synchronizes the time using an NTP server.
3. ESP32 connects to the MQTT broker.
4. DHT11 measures temperature and humidity.
5. Temperature is compared with the threshold value of 35°C.
6. The status is set to `NORMAL` or `ALERT`.
7. Sensor data is converted into JSON format.
8. The JSON data is published to the MQTT topic.
9. The process repeats every 5 seconds.

## JSON Data Format

```json
{
  "device_id": "CC_TEST_01",
  "timestamp": 17906,
  "sensor_value": 32.5,
  "humidity": 65,
  "status": "NORMAL"
}
```

## Threshold

The temperature threshold is set to:

```text
35°C
```

If:

```text
Temperature >= 35°C
```

the status becomes:

```text
ALERT
```

Otherwise:

```text
NORMAL
```

## MQTT Data Flow

```text
DHT11 Sensor
     ↓
    ESP32
     ↓
   Wi-Fi
     ↓
 MQTT Broker
     ↓
MQTT Subscriber
```

## Project Structure

```text
ESP32-MQTT-DHT11/
│
├── ESP32-MQTT-DHT11.ino
└── README.md
```
<img width="1526" height="2034" alt="image" src="https://github.com/user-attachments/assets/c8fbb9fc-571b-4ef2-b479-4cdffffe0275" />
<img width="1366" height="768" alt="Screenshot (1115)" src="https://github.com/user-attachments/assets/d5ba001b-ff31-476d-9b01-5bde30c38116" />
<img width="1366" height="768" alt="Screenshot (1113)" src="https://github.com/user-attachments/assets/8591ee7b-5d8b-4545-a510-1a9b67480db6" />


