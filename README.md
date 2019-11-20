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
