
#include "mqtt_init.h"
#include <cstring> // For std::memcpy


uint8_t MQTTConnection::send_buffer[2048];
uint8_t MQTTConnection::recieve_buff[2048];
MQTTConnection* MQTTConnection::instance = nullptr;


MQTTConnection::MQTTConnection() {

	MQTTConnection::instance = this;

}

void MQTTConnection::init(Config* configInstance, Utils * utilInstance) {
	    utils = utilInstance;
	    config = configInstance;
}

bool MQTTConnection::connect() {
	NewNetwork(&network, 1);
	ConnectNetwork(&network, config->getBrokerIP().data(), config->getBrokerPort());
    MQTTClientInit(&mqttClient, &network, 1000,send_buffer , sizeof(send_buffer), recieve_buff, sizeof(recieve_buff));
    // Set MQTT connection parameters
    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    connectData.MQTTVersion = 3;
    connectData.clientID.cstring = strdup(config->getClientId().c_str());
    connectData.username.cstring = const_cast<char*>(config->getUsername().c_str());
    connectData.password.cstring = const_cast<char*>(config->getPassword().c_str());
    connectData.keepAliveInterval = config->getKeepAliveInterval();
    connectData.cleansession = 1;

    // Attempt to connect to the MQTT broker
    if (MQTTConnect(&mqttClient, &connectData) != SUCCESS) {
        utils->print("Connection failed!\n");
        return false;
    }
    subscribe(config->getTopicSubscribe());

    setIsConnected(true);

    utils->print("Successfully connected to MQTT broker.\r\n");

    return true;
}

bool MQTTConnection::publish(const std::string& message) {
    MQTTMessage mqttMessage;
    mqttMessage.qos = QOS0;
    mqttMessage.retained = 0;
    mqttMessage.dup = 0;
    const char* cMessage = message.c_str();
    mqttMessage.payload = (void*)cMessage;
    mqttMessage.payloadlen = message.length();

    if (MQTTPublish(&mqttClient, config->getTopicPublish().c_str(), &mqttMessage) != SUCCESS) {
    	setIsConnected(false);
         utils->print("Publish failed! \r\n");
        return false;
    }

   //  utils->print("Message published successfully.\r\n");
    return true;
}

void MQTTConnection::subscribe(std::string topic) {
	const char* subTopic = strdup(topic.c_str());
    if (MQTTSubscribe(&mqttClient, subTopic, QOS0,  handleMessage) != SUCCESS) {
       utils->print("Subscribe failed!\n");
    } else {
       utils->print("Subscribed to topic successfully.\r\n");
    }
}

void MQTTConnection::handleMessage(MessageData* data) {
//	print("Message has been arrived !!! \r\n");
	 if (MQTTConnection::instance) {
           MQTTConnection::instance->handleIncomingMessage(data);
	  }
}

MQTTConnection::~MQTTConnection() {
    // Clean up resources, if necessary
    disconnect();
    if (MQTTConnection::instance == this) {
    	MQTTConnection::instance = nullptr;
    }
}

void MQTTConnection::disconnect() {
    // Disconnect from the MQTT broker
    MQTTDisconnect(&mqttClient);
  //  utils->print("Disconnected from MQTT broker.\n");
}

void MQTTConnection::mqttYield() {
	 if (getIsConnected()) {
		 MQTTYield(&mqttClient, 1000);
	 }

}


void MQTTConnection::setIsConnected(bool val) {
	isConnected = val;
}

bool MQTTConnection::getIsConnected(){
	return isConnected;
}


void MQTTConnection::handleIncomingMessage(MessageData* data) {
	    if (data->message->payloadlen >= 1024) {
	        utils->print("Data size is bigger than expected \r\n");
	        return;
	    }
	    char payloadStr[1024]; // Static allocation
	    memcpy(payloadStr, data->message->payload, data->message->payloadlen);
	    payloadStr[data->message->payloadlen] = '\0'; // Null-terminate

	    cJSON *json = cJSON_Parse(payloadStr);
	    if (!json) {
	    	utils->print("JSON format is not matching!!! \r\n");
	        return;
	    }
	    const cJSON *typeJson = cJSON_GetObjectItemCaseSensitive(json, "type");
	    int type = typeJson->valueint;

	    switch (type){
	    case 1:
	    	config->setAnalogInputNamesFromJson(json);
	    	utils->playSound();
	    	utils->print("Analog names has been changed! \r\n");
	    	break;
	    case 2:
	    	config->setDigitalInputNamesFromJson(json);
	    	utils->print("Digital Input Names has been changed! \r\n");
	    	utils->playSound();
	    	break;
	    case 3:
	    	config->setRelayNamesFromJson(json);
	    	utils->print("Relay Names has been changed!! \r\n");
	    	utils->playSound();
	    	break;
	    case 4:
		    const cJSON *number = cJSON_GetObjectItemCaseSensitive(json, "number");
			const cJSON *status = cJSON_GetObjectItemCaseSensitive(json, "status");
			if (!cJSON_IsNumber(number) && !cJSON_IsNumber(status)) return;
			if (number->valueint >= 1 && number->valueint <= 8) {
				    int arrayIndex = number->valueint - 1;
				    PortAndPins targetSwitch = utils->switches[arrayIndex];
				    bool success = utils->switchRelay(targetSwitch.port, targetSwitch.pin, status->valueint);
				     if (success) {
				    	  utils->print("The %d switch has been toggled.\r\n", number->valueint);
				  } else {
				    	utils->print("There is an issue with switch \r\n");
		          }
		    }
			break;
	    }

	    cJSON_Delete(json);
}


