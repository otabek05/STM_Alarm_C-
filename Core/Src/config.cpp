#include "config.h"

uint8_t mac[6];

Config::Config(){

}

void Config::init() {

    setBrokerIP({175, 210, 42,26});
    setBrokerPort(1883);
    setIP({172, 30, 1, 123});
    setGateway({172, 30, 1, 254});
    setSubnet({255, 255, 255, 0});
    setDNS({8, 8, 8, 8}); // Google's DNS for example
    setKeepAliveInterval(60);
    setDHCPEnabled(true);
    setIntervalTime(1000); // Example interval time

    setUsername("user");
    setClientId(std::string(clientId));


    setPassword("pass");
    setTopicPublish("topic/pub");
    setQoS(1); // Quality of Service level


    setAnalogInputNames({"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10"});
    setDigitalInputNames({"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10"});
    setDigitalOutputNames({"O1", "O2", "O3", "O4", "O5", "O6", "O7", "O8", "O9", "O10"});
}


// Getters
std::array<uint8_t, 4> Config::getBrokerIP() const { return broker_ip; }
uint16_t Config::getBrokerPort() const { return broker_port; }
std::array<uint8_t, 4> Config::getIP() const { return ip; }
std::array<uint8_t, 4> Config::getGateway() const { return gateway; }
std::array<uint8_t, 4> Config::getSubnet() const { return subnet; }
std::array<uint8_t, 4> Config::getDNS() const { return dns; }
uint16_t Config::getKeepAliveInterval() const { return keep_alive_interval; }
bool Config::getDHCPEnabled() const { return dhcp_enabled; }
uint32_t Config::getIntervalTime()  const { return interval_time;}
std::string Config::getUsername()const { return username; }
std::string Config::getClientId()const  { return clientId; }
std::string Config::getPassword()const { return password; }
std::string Config::getTopicSubscribe()const { return topic_subscribe; }
std::string Config::getTopicPublish()const {return topic_publish;}
int Config::getQoS() const { return qos; }
std::array<std::string, MAX_ANALOG_INPUTS> Config::getAnalogInputNames() { return analog_input_names; }
std::array<std::string, MAX_DIGITAL_INPUTS> Config::getDigitalInputNames()  { return digital_input_names; }
std::array<std::string, MAX_DIGITAL_OUTPUTS> Config::getDigitalOutputNames()  { return digital_output_names; }

// Setters
void Config::setBrokerIP(const std::array<uint8_t, 4>& value) { broker_ip = value; }
void Config::setBrokerPort(uint16_t value) { broker_port = value; }
void Config::setIP(const std::array<uint8_t, 4>& value) { ip = value; }
void Config::setGateway(const std::array<uint8_t, 4>& value) { gateway = value; }
void Config::setSubnet(const std::array<uint8_t, 4>& value) { subnet = value; }
void Config::setDNS(const std::array<uint8_t, 4>& value) { dns = value; }
void Config::setKeepAliveInterval(uint16_t value) { keep_alive_interval = value; }
void Config::setDHCPEnabled(bool value) { dhcp_enabled = value; }
void Config::setIntervalTime(uint32_t value) { interval_time = value; }

void Config::setUsername(const std::string& value) { username = value; }
void Config::setClientId(const std::string& value) { clientId = value; }
void Config::setPassword(const std::string& value) { password = value; }


void Config::setTopicSubscribe(const std::string& value) { topic_subscribe = value; }
void Config::setTopicPublish(const std::string& value) { topic_publish = value; }
void Config::setQoS(int value) { qos = value; }
void Config::setAnalogInputNames(const std::array<std::string, MAX_ANALOG_INPUTS>& value) { analog_input_names = value; }
void Config::setDigitalInputNames(const std::array<std::string, MAX_DIGITAL_INPUTS>& value) { digital_input_names = value; }
void Config::setDigitalOutputNames(const std::array<std::string, MAX_DIGITAL_OUTPUTS>& value) { digital_output_names = value; }
