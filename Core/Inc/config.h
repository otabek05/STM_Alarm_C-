#ifndef CONFIG_H
#define CONFIG_H

#include <array>
#include <string>
#include <cstdint>
#include "AT24C.h"
#include "utils.h"

extern "C" {
#include "stm32f4xx_hal.h"
#include "wizchip_conf.h"
#include "string.h"
#include "cJSON.h"


}
constexpr size_t MAX_ANALOG_INPUTS = 8;
constexpr size_t MAX_DIGITAL_INPUTS = 16;
constexpr size_t MAX_DIGITAL_OUTPUTS = 8;


class Key{
public:
	std::string Key;
	uint8_t Val;
};

#define BROKER_IP_ID         1
#define BROKER_PORT_ID       2
#define IP_ID                3
#define GATEWAY_ID           4
#define SUBNET_ID            5
#define DNS_ID               6
#define DHCP_ENABLED_ID      7  // Changed from 8 to 7
#define EXTENSION_ENABLED_ID 8  // Changed from 9 to 8
#define INTERVAL_TIME_ID     9  // Changed from 10 to 9
#define USERNAME_ID          10 // Changed from 11 to 10
#define PASSWORD_ID          11 // Changed from 13 to 11
#define TOPIC_SUBSCRIBE_ID   12 // Changed from 14 to 12
#define TOPIC_PUBLISH_ID     13 // Changed from 15 to 13
#define DIGITALNAME_ID       14 // Changed from 16 to 14
#define ANALOGNAME_ID        15 // Changed from 17 to 15
#define RELAYNAME_ID         16 // Changed from 18 to 16


class Utils;

class AT24C;

class Config {
public:
    Config();
    // Getters
    AT24C* eeprom;
    Utils* utils;
    std::array<uint8_t, 4> getBrokerIP() const;
    uint16_t getBrokerPort() const;
    std::array<uint8_t, 4> getIP()const ;
    std::array<uint8_t, 4> getGateway()const;
    std::array<uint8_t, 4> getSubnet() const;
    std::array<uint8_t, 4> getDNS() const ;
    uint16_t getKeepAliveInterval() const;
    bool getDHCPEnabled() const;
    bool getIpAssigned() const;
    bool getExtentionEnabled() const;
    uint32_t getIntervalTime() const;
    std::string getUsername() const;
    std::string getClientId() const;
    std::string getPassword() const;
    std::string getTopicSubscribe() const;
    std::string getTopicPublish() const;
    int getQoS() const;
    std::array<std::string, MAX_ANALOG_INPUTS> getAnalogInputNames() ;
    std::array<std::string, MAX_DIGITAL_INPUTS> getDigitalInputNames() ;
    std::array<std::string, MAX_DIGITAL_OUTPUTS> getDigitalOutputNames();

    // Setters
    void setBrokerIP(const std::array<uint8_t, 4>& value);
    void setBrokerPort(uint16_t value);
    void setIP(const std::array<uint8_t, 4>& value);
    void setGateway(const std::array<uint8_t, 4>& value);
    void setSubnet(const std::array<uint8_t, 4>& value);
    void setDNS(const std::array<uint8_t, 4>& value);
    void setKeepAliveInterval(uint16_t value);
    void setDHCPEnabled(bool value);
    void setIpAssigned(bool value);
    void setExtentionEnabled(bool val);
    void setIntervalTime(uint32_t value);
    void setUsername(const std::string& value);
    void setClientId(const std::string& value);
    void setPassword(const std::string& value);
    void setTopicSubscribe(const std::string& value);
    void setTopicPublish(const std::string& value);
    void setQoS(int value);
    void setAnalogInputNames(const std::array<std::string, MAX_ANALOG_INPUTS>& value);
    void setDigitalInputNames(const std::array<std::string, MAX_DIGITAL_INPUTS>& value);
    void setDigitalOutputNames(const std::array<std::string, MAX_DIGITAL_OUTPUTS>& value);

    std::string getAnalogInputName(int index);
    std::string getDigitalInputName(int index);
    std::string getDigitalOutputName(int index);
    void init(AT24C* eepromInstance, Utils* utilsInstance);
    void setUp();
    void initmqttConfig();
    char* getInfoList();
    std::array<uint8_t, 4> extractIPAddress(cJSON* parent, const char* name);

    void setNetworkSettings(cJSON *data);
    void setMQTTBroker(cJSON* data);

    void setAnalogInputNamesFromJson(cJSON* jsonData);
    void setDigitalInputNamesFromJson(cJSON* jsonData);
    void setRelayNamesFromJson(cJSON* jsonData);

    void setDHCPNetworkConfig(wiz_NetInfo* net_info) ;


private:
    // Member variables
    std::array<uint8_t, 4> broker_ip;
    uint16_t broker_port;
    std::array<uint8_t, 4> ip;
    std::array<uint8_t, 4> gateway;
    std::array<uint8_t, 4> subnet;
    std::array<uint8_t, 4> dns;
    uint16_t keep_alive_interval;
    bool dhcp_enabled;
    bool ip_assigned = false;
    bool extentionEnabled = false;
    uint32_t interval_time;
    std::string username;
    std::string clientId;
    std::string password;
    std::string topic_subscribe;
    std::string topic_publish;
    int qos;


    std::array<std::string, MAX_ANALOG_INPUTS> analog_input_names;
    std::array<std::string, MAX_DIGITAL_INPUTS> digital_input_names;
    std::array<std::string, MAX_DIGITAL_OUTPUTS> digital_output_names;



};





#endif // CONFIG_H

