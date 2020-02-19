# NodeMCU with PIR motion sensor connected via MQTT to Homebridge
I built an Homebridge accessory that detects motion using a NodeMCU connected to a PIR motion sensor.  
My Homebridge instance is running on a RPI3 which works also as the MQTT broker.  
Here is my code for the NodeMCU. 

Arduino IDE settings:  
NodeMCU 1.0, 115200, 80Mhz, Flash, Disabled, 4M, v2 Lower Memory, Disabled, None, Only Sketch  
  
HC-SR501 settings:
- jumper on L-position  
- max delay  
- max sensitivity 

I used the homebridge plugin https://github.com/heisice/homebridge-mqtt-motionsensor

Sample config.json:  
```
"accessories": [ 
  {
    "accessory": "mqtt-motionsensor",  
    "name": "Living Room",  
    "url": "mqtt://localhost",  
    "topic": "home/livingroom/motionsensor",  
    "username": "username",  
    "password": "password"  
  }  
],  
```
Explanation:  
- choose the same topic you already used in the Arduino sketch  
- choose the same name you already used in the Arduino sketch  
- username and password are the ones to the MQTT broker and depends on your MQTT broker settings  
- the url ```mqtt://localhost``` does work since the MQTT broker runs on the same RPI3 than the Homebridge instance

If you want to use several motion sensors, just add another accessory to the config.json.  
Keep in mind to use another topic:  
```  
"accessories": [
  {
    "accessory": "mqtt-motionsensor",
    "name": "Living Room",  
    "url": "mqtt://localhost",  
    "topic": "home/livingroom/motionsensor",  
    "username": "username",  
    "password": "password"  
  },  
  {  
    "accessory": "mqtt-motionsensor",  
    "name": "Hall",  
    "url": "mqtt://localhost",  
    "topic": "home/hall/motionsensor",  
    "username": "username",  
    "password": "password"  
  }  
],  
```
