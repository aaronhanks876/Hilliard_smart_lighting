#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <RBDdimmer.h>//

//#define USE_SERIAL  Serial


//PWM 1
#define outputPin1  3 // RX
#define zerocross1  13 //D7
//PWM 2
#define outputPin2  14 //D5
#define zerocross2  2  //D4
//Pwm 3
#define outputPin3  4 //D2
#define zerocross3  16 //D0

dimmerLamp dimmer1(outputPin1, zerocross1);
dimmerLamp dimmer2(outputPin2, zerocross2);
dimmerLamp dimmer3(outputPin3, zerocross3);

#define LED D0 // GPIO 5 (D1) for LED
int ACState = 0;

// WiFi settings
const char *ssid = "HCL Interns";             // Replace with your WiFi name
const char *password = "Interns123!";   // Replace with your WiFi password

// MQTT Broker settings
const char *mqtt_broker = "192.168.60.6";  // EMQX broker endpoint
const char *mqtt_topic = "lights/AC/box1";     // Needs to be changed with box number
const char *will_topic = "lights/AC/box1/connection"; // Needs to be changed with box number

const char *mqtt_username = "AC1";  // MQTT username for authentication
const char *mqtt_password = "HilliardAC#1";  // MQTT password for authentication
const int mqtt_port = 1883;  // MQTT port (TCP)

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void connectToWiFi();

void connectToMQTTBroker();

void mqttCallback(char *topic, byte *payload, unsigned int length);

void mode1();

void setup() {
    //Serial.begin(115200);
    // pinMode(LED, OUTPUT);
    dimmer1.begin(NORMAL_MODE, ON);
    dimmer2.begin(NORMAL_MODE, ON);
    dimmer3.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 
    connectToWiFi();
    mqtt_client.setServer(mqtt_broker, mqtt_port);
    mqtt_client.setCallback(mqttCallback);
    connectToMQTTBroker();
}

void connectToWiFi() {
    WiFi.begin(ssid, password);
    //Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        //Serial.print(".");
    }
    Serial.println("\nConnected to the WiFi network");
}

void connectToMQTTBroker() {
    while (!mqtt_client.connected()) {
        String client_id = "esp8266-client-" + String(WiFi.macAddress());
        //Serial.printf("Connecting to MQTT Broker as %s.....\n", client_id.c_str());
        if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password, will_topic, 2, true, "Disconnected")) {
            //Serial.println("Connected to MQTT broker");
            mqtt_client.subscribe(mqtt_topic);
            // Publish message upon successful connection
            mqtt_client.publish(will_topic, "Connected");
        } else {
            //Serial.print("Failed to connect to MQTT broker, rc=");
            //Serial.print(mqtt_client.state());
            //Serial.println(" try again in 2 seconds");
            delay(2000);
        }
    }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
    //Serial.print("Message received on topic: ");
    //Serial.println(topic);
    //Serial.print("Message:");
    String message;
    for (int i = 0; i < length; i++) {
       message += (char)payload[i];
    }
    //Serial.println(message);
    int intMessage = message.toInt();
    if (intMessage == 1){
        mode1();
        //Serial.print("1");
    }
    else if (intMessage == 2){
        mode2();
        //Serial.print("2");
    }
    else if (intMessage == 3){
        mode3();
        //Serial.print("3");
    }





    // off
    
    

}

void mode1 (){ //Twinkle
	for (int i = 50; i < 100; i +=1){
		dimmer1.setPower(round(i));
        dimmer2.setPower(round(i));
        dimmer3.setPower(round(i));
	}
	for (int i = 100; i > 50; i -= 1){
		dimmer1.setPower(round(i));
        dimmer2.setPower(round(i));
        dimmer3.setPower(round(i));
	}
}

void mode2 (){ //Flash
	for (int i = 30; i < 100; i +=1){
		dimmer1.setPower(round(i));
        dimmer2.setPower(round(i));
        dimmer3.setPower(round(i));
	}
	for (int i = 100; i > 30; i -= 1){
		dimmer1.setPower(round(i));
        dimmer2.setPower(round(i));
        dimmer3.setPower(round(i));
	}
}

void mode3 (){ //Slow flash
	for (float i = 30.0; i < 100.0; i += 0.1){
		dimmer1.setPower(int(round(i)));
        dimmer2.setPower(int(round(i)));
        dimmer3.setPower(int(round(i)));
	}
	for (int i = 100.0; i > 30.0; i -= 0.1){
		dimmer1.setPower(int(round(i)));
        dimmer2.setPower(int(round(i)));
        dimmer3.setPower(int(round(i)));
	}
}


void loop() {
    if (!mqtt_client.connected()) {
        connectToMQTTBroker();
    }
    mqtt_client.loop();
}