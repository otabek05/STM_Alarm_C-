#ifndef MQTT_CONNECTION_H
#define MQTT_CONNECTION_H

// Ensure C libraries are included correctly in C++
extern "C" {
#include "MQTTClient.h"    // C library for MQTT Client
#include "mqtt_interface.h" // C library for MQTT network interface
#include "cJSON.h"
}



#include "CplusUtils.h"
#include "config.h"

class Utils;
class MQTTConnection{
public:
    MQTTConnection();
    ~MQTTConnection();
    void init(Config config, Utils *utilInstance);
    Utils* utils;
    bool connect(Config conf);
    bool publish(const std::string& message, Config config);
    void subscribe(std::string topic);
    void disconnect();
    void mqttYield();

private:
    static void handleMessage(MessageData* data);
    void handleIncomingMessage(MessageData* data); // Instance method to handle messages

    MQTTClient mqttClient;
    Network network;
    static MQTTConnection* instance; // Static instance pointer for static callback compatibility

    static uint8_t send_buffer[2048];
    static uint8_t recieve_buff[2048];
};

void messageArrived(MessageData* md);

#endif // MQTT_CONNECTION_H
