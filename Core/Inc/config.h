#ifndef CONFIG_H
#define CONFIG_H

#include <array>
#include <string>
#include <cstdint>



extern "C" {
#include "stm32f4xx_hal.h"
#include "wizchip_conf.h"

}
constexpr size_t MAX_ANALOG_INPUTS = 10;
constexpr size_t MAX_DIGITAL_INPUTS = 10;
constexpr size_t MAX_DIGITAL_OUTPUTS = 10;

class Config {
public:
    Config();
    // Getters
    std::array<uint8_t, 4> getBrokerIP() const;
    uint16_t getBrokerPort() const;
    std::array<uint8_t, 4> getIP() const;
    std::array<uint8_t, 4> getGateway() const;
    std::array<uint8_t, 4> getSubnet() const;
    std::array<uint8_t, 4> getDNS() const;
    uint16_t getKeepAliveInterval() const;
    bool getDHCPEnabled() const;
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


    void init();
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

