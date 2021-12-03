# PowerMonitor

This library for Arduino is a full operation power monitor for [ESP8266 NodeMCU](https://www.nodemcu.com/index_en.html).

## Instalation
To install the system library, copy the folders of the libraries to your Arduino sketchbook folder.
You can check your Arduino sketchbook folder in Arduino IDE on 
> File > Preferences > Sketchbook
## Configuration
To configure the system, open the file `Configuration.h` at the folder `x` folder. (Still working)
## Dependencies
* Emonlib
* MqttClient
* [CloudIoTCore](https://github.com/GoogleCloudPlatform/google-cloud-iot-arduino) (Depends of lwMQTT)
## Hardware
* Esp8266 based development boards (NodeMCU)
* Non-Invasive current sensor
* Arduino relay module (or just a relay)
* Basic circuit elements
