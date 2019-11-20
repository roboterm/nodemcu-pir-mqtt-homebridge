char* ssid = "Auenland"; //Wi-Fi AP Name
char* password = "xxxxxxxx"; //Wi-Fi Password
char* mqtt_server = "192.168.2.102"; //MQTT Server IP
char* mqtt_name = "Wohnzimmer Bewegungssensor"; //MQTT device name
char* mqtt_topic = "home/livingroom/sensors/motion"; //MQTT topic for communication
int pirPin = 13; //set the GPIO which you will connect the PIR sensor
bool lowPower = false; //set to true if you want low power use
int delayTime = 2000; //ONLY FOR LOW POWER - how long motion detected should be active

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
WiFiClient mainESP;
PubSubClient MQTT(mainESP);

char* mqtt_maintopic = mqtt_topic;

void setup() {
	pinMode(pirPin, INPUT_PULLUP);
	Serial.begin(115200);
}

void loop() {
	if (!lowPower && WiFi.status() != WL_CONNECTED) 
		startWiFi();
	Serial.println(digitalRead(pirPin));

	if ((digitalRead(pirPin)) == 0) 
		delay(250);
	else {
		if (WiFi.status() != WL_CONNECTED) 
			startWiFi();
		MQTT.loop();
		if (!MQTT.connected()) 
			reconnect();
		MQTT.publish(mqtt_topic, "1");
		Serial.println("Message Published: TRUE");
		while (digitalRead(pirPin) == 1) {
			if (!MQTT.connected()) 
				reconnect();
			MQTT.publish(mqtt_topic, "1");
			Serial.println("Message Published: TRUE");
			delay(5000);
		}
		if (!MQTT.connected()) 
			reconnect();
		if (lowPower) 
			delay(delayTime);
		MQTT.publish(mqtt_topic, "0");
		Serial.println("Message Published: FALSE");
		MQTT.loop();
		delay(5000);
	}
	if (lowPower) {
		WiFi.disconnect();
		WiFi.mode(WIFI_OFF);
		WiFi.forceSleepBegin();
		delay(1);
	}
}

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();
}

void reconnect() {
	while (!MQTT.connected()) {
		Serial.print("Attempting MQTT connection...");
		if (MQTT.connect(mqtt_name)) {
			Serial.println("connected");
		} else {
			Serial.print("failed, rc=");
			Serial.print(MQTT.state());
			Serial.println(" try again in 5 seconds");
			for (int i = 0; i < 5000; i++) {
				delay(1);
			}
		}
	}
}

void startWiFi() {
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		delay(1000);
		ESP.restart();
	}
	WiFi.hostname(mqtt_name);
	Serial.println("Ready");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	MQTT.setServer(mqtt_server, 1883);
	MQTT.setCallback(callback);
}
