
#include "mqtt_init.h"
#include <cstring> // For std::memcpy


// Static member definition
MQTTConnection* MQTTConnection::instance = nullptr;

uint8_t MQTTConnection::send_buffer[2048];
uint8_t MQTTConnection::recieve_buff[2048];


MQTTConnection::MQTTConnection() {
    // Set static instance pointer for callback compatibility

/*
    // Setup device configuration (Adjust according to your actual configuration setup)
    std::strcpy(config.getBrokerIP().data(), brokerIp);
    config.broker_port = brokerPort;
    std::strcpy(config.username, username);
    std::strcpy(config.password, password);
    config.keep_alive_interval = keepAliveInterval;
    std::strcpy(config.topic_publish, topicPublish);

    unsigned char mac[6] = {}; // Placeholder for MAC address retrieval logic
    getSHAR(mac); // Assuming getSHAR is your function to retrieve the MAC address
    std::sprintf(clientID, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);


    */


}

void MQTTConnection::init(Config config) {

	    NewNetwork(&network, 1);
	    ConnectNetwork(&network, config.getBrokerIP().data(), config.getBrokerPort());


	    MQTTClientInit(&mqttClient, &network, 1000,send_buffer , sizeof(send_buffer), recieve_buff, sizeof(recieve_buff));

	    if (!connect(config)) {
	      	Print("MQTT Connection has been failed\r\n");
	      }

	     subscribe(config.getTopicSubscribe().c_str());
}

bool MQTTConnection::connect(Config config) {
    // Set MQTT connection parameters
    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    connectData.MQTTVersion = 3;
    connectData.clientID.cstring = "iot";

    Print("%s \r\n", config.getClientId().c_str());
 //   connectData.clientID.cstring = const_cast<char*>(config.getClientId().c_str());
    connectData.username.cstring = const_cast<char*>(config.getUsername().c_str());
    connectData.password.cstring = const_cast<char*>(config.getPassword().c_str());

    connectData.keepAliveInterval = config.getKeepAliveInterval();
    connectData.cleansession = 1;

    // Attempt to connect to the MQTT broker
    if (MQTTConnect(&mqttClient, &connectData) != SUCCESS) {
        Print("Connection failed!\n");
        return false;
    }

    Print("Successfully connected to MQTT broker.\n");
    return true;
}

bool MQTTConnection::publish(  char* message, Config config) {
    MQTTMessage mqttMessage;
    mqttMessage.qos = QOS0;
    mqttMessage.retained = 0;
    mqttMessage.dup = 0;
    mqttMessage.payload = (void*)message;
    mqttMessage.payloadlen = std::strlen(message);

    // Publish message
    if (MQTTPublish(&mqttClient, config.getTopicPublish().c_str(), &mqttMessage) != SUCCESS) {
        Print("Publish failed!\n");
        return false;
    }

    Print("Message published successfully.\n");
    return true;
}

void MQTTConnection::subscribe(std::string topic) {
    // Subscribe to a topic
 char*	subTopic =  const_cast<char*>(topic.c_str());
    if (MQTTSubscribe(&mqttClient,subTopic, QOS0, handleMessage) != SUCCESS) {
        Print("Subscribe failed!\n");
    } else {
        Print("Subscribed to topic successfully.\n");
    }
}

void MQTTConnection::handleMessage(MessageData* data) {
    if (instance) {
        instance->handleIncomingMessage(data);
    }
}

void MQTTConnection::handleIncomingMessage(MessageData* data) {
    // Handle incoming messages here
    // This method would contain logic similar to your HanldeIncomingMessages function
    Print("Message received on topic.\n");
}

MQTTConnection::~MQTTConnection() {
    // Clean up resources, if necessary
    disconnect();
}

void MQTTConnection::disconnect() {
    // Disconnect from the MQTT broker
    MQTTDisconnect(&mqttClient);
    Print("Disconnected from MQTT broker.\n");
}

void MQTTConnection::mqttYield() {
	  MQTTYield(&mqttClient, 60);
}



