#include "config.h"

uint8_t mac[6];

Config::Config(){

}

void Config::init() {

    setBrokerIP({172, 30,1,25});
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

    setAnalogInputNames({"Analog1", "Analog2", "Analog3", "Analog4", "Analog5", "Analog6", "Analog7", "Analog8",});
    setDigitalInputNames({"DI1", "DI2", "DI3", "DI4", "DI5", "DI6", "DI7", "DI8", "DI9", "DI10", "DI11", "DI12", "DI13", "DI14", "DI15", "DI16"});
    setDigitalOutputNames({"Relay1", "Relay2", "Relay3", "Relay4", "Relay5", "Relay6", "Relay7", "Relay8",});

}


std::string Config::getAnalogInputName(int index){
	return analog_input_names[index];
}

std::string Config::getDigitalInputName(int index){
	return digital_input_names[index];
}

std::string Config::getDigitalOutputName(int index){
	return digital_output_names[index];
}

void Config::initmqttConfig() {
    uint8_t mac[6];
    getSHAR(mac);
    char macString[18] = {0}; // Initialize macString with zeros
    for (int i = 0; i < 6; ++i) {
        if (i > 0) {
            strcat(macString, ":"); // Add ':' between bytes except for the first one
        }
        sprintf(macString + strlen(macString), "%02X", mac[i]); // Append two characters per byte
    }

     setSHAR(mac); // Commented out because it seems unnecessary here
    std::string clientID = std::string(macString);
    std::string data = "data/" + clientID;

    // Set MQTT client ID and topic to subscribe
    setClientId(clientID);
    setTopicSubscribe(data);
}


cJSON *createJsonArray(const uint8_t arr[], size_t len) {
       cJSON *jsonArray = cJSON_CreateArray();
       for (size_t i = 0; i < len; ++i) {
           cJSON_AddItemToArray(jsonArray, cJSON_CreateNumber(arr[i]));
       }
       return jsonArray;
   }


char* Config::getInfoList() {
    cJSON *root = cJSON_CreateObject();


    if (root == NULL) {
        return "";
    }

    // Existing configurations
    cJSON_AddItemToObject(root, "ip", createJsonArray(ip.data(), ip.size()));
    cJSON_AddItemToObject(root, "gateway", createJsonArray(gateway.data(), gateway.size()));
    cJSON_AddItemToObject(root, "subnet", createJsonArray(subnet.data(), subnet.size()));
    cJSON_AddItemToObject(root, "dns", createJsonArray(dns.data(), dns.size()));


    cJSON_AddItemToObject(root, "brokerIp", createJsonArray(broker_ip.data(), dns.size()));

    // Serialize Analog Input Names
    auto analogInputNames = getAnalogInputNames();
    cJSON *analogInputsArray = cJSON_CreateArray();
    for (const auto& name : analogInputNames) {
        cJSON_AddItemToArray(analogInputsArray, cJSON_CreateString(name.c_str()));
    }
   cJSON_AddItemToObject(root, "ai", analogInputsArray);

    // Serialize Digital Input Names
    auto digitalInputNames = getDigitalInputNames();
    cJSON *digitalInputsArray = cJSON_CreateArray();
    for (const auto& name : digitalInputNames) {
        cJSON_AddItemToArray(digitalInputsArray, cJSON_CreateString(name.c_str()));
    }
    cJSON_AddItemToObject(root, "di", digitalInputsArray);

    // Serialize Digital Output Names
    auto digitalOutputNames = getDigitalOutputNames();
    cJSON *digitalOutputsArray = cJSON_CreateArray();
    for (const auto& name : digitalOutputNames) {
        cJSON_AddItemToArray(digitalOutputsArray, cJSON_CreateString(name.c_str()));
    }
    cJSON_AddItemToObject(root, "type", cJSON_CreateString("info"));
    cJSON_AddItemToObject(root, "relay", digitalOutputsArray);
    cJSON_AddItemToObject(root, "mac", cJSON_CreateString(getClientId().c_str()));
    cJSON_AddItemToObject(root, "port", cJSON_CreateNumber(getBrokerPort()));
    cJSON_AddItemToObject(root, "net-status", cJSON_CreateBool(getDHCPEnabled()));

    // Serialize JSON to string
    char *serializedData = cJSON_Print(root);
    if (serializedData != NULL) {

    }

    cJSON_Delete(root);
    return serializedData;

}

std::array<uint8_t, 4> Config::extractIPAddress(cJSON* parent, const char* name) {
    std::array<uint8_t, 4> addressArray{};
    cJSON* item = cJSON_GetObjectItemCaseSensitive(parent, name);
    if (cJSON_IsArray(item)) {
        for (int i = 0; i < 4; ++i) {
            cJSON* byteItem = cJSON_GetArrayItem(item, i);
            if (cJSON_IsNumber(byteItem)) {
                addressArray[i] = static_cast<uint8_t>(byteItem->valueint);
            }
        }
    }
    return addressArray;
}



void Config::setNetworkSettings(cJSON* data) {
    cJSON* statusJson = cJSON_GetObjectItemCaseSensitive(data, "status");
    if (cJSON_IsBool(statusJson)) {
    	 bool status = cJSON_IsTrue(statusJson) ? true : false;
       // bool status = cJSON_IsTrue(statusJson);


        if (!status) {
            setIP(extractIPAddress(data, "ip"));
            setGateway(extractIPAddress(data, "gateway"));
            setSubnet(extractIPAddress(data, "subnet"));
            setDNS(extractIPAddress(data, "dns"));
        }

        setDHCPEnabled(status);
    }
}


void Config::setMQTTBroker(cJSON* data) {
	if (data == nullptr) return;
	cJSON* numItem = cJSON_GetObjectItemCaseSensitive(data, "port");
	        if (cJSON_IsNumber(numItem)) {
	            int number = numItem->valueint;
	            setBrokerPort(number);
	            setBrokerIP(extractIPAddress(data, "broker_ip"));
	  }

}



void Config::setAnalogInputNamesFromJson(cJSON* jsonData) {
    if (jsonData == nullptr) {
        return; // Input is null, handle error as needed
    }

    cJSON* analogInputsJson = cJSON_GetObjectItemCaseSensitive(jsonData, "data");
    if (!cJSON_IsArray(analogInputsJson)) {
        return; // Not an array, handle error as needed
    }

    std::array<std::string, MAX_ANALOG_INPUTS> analogInputs;
    size_t index = 0;
    cJSON* analogInputJson;

    // Iterate over the analog input names array
    cJSON_ArrayForEach(analogInputJson, analogInputsJson) {
        if (cJSON_IsString(analogInputJson) && (analogInputJson->valuestring != NULL)) {
            if (index < MAX_ANALOG_INPUTS) {
                analogInputs[index] = std::string(analogInputJson->valuestring);
                ++index;
            } else {
                break; // More items in the list than MAX_ANALOG_INPUTS, handle as needed
            }
        }
    }

    setAnalogInputNames(analogInputs);
}


void Config::setDigitalInputNamesFromJson(cJSON* jsonData) {
    if (jsonData == nullptr) {
        return; // Input is null, handle error as needed
    }

    cJSON* digitalInputsJson = cJSON_GetObjectItemCaseSensitive(jsonData, "data");
    if (!cJSON_IsArray(digitalInputsJson)) {
        return; // Not an array, handle error as needed
    }

    std::array<std::string, MAX_DIGITAL_INPUTS> digitalInputs;
    size_t index = 0;
    cJSON* digitalInputJson;

    // Iterate over the analog input names array
    cJSON_ArrayForEach(digitalInputJson, digitalInputsJson) {
        if (cJSON_IsString(digitalInputJson) && (digitalInputJson->valuestring != NULL)) {
            if (index < MAX_DIGITAL_INPUTS) {
                digitalInputs[index] = std::string(digitalInputJson->valuestring);
                ++index;
            } else {
                break; // More items in the list than MAX_ANALOG_INPUTS, handle as needed
            }
        }
    }

    setDigitalInputNames(digitalInputs);
}


void Config:: setRelayNamesFromJson(cJSON* jsonData){
	 if (jsonData == nullptr) {
	        return; // Input is null, handle error as needed
	    }

	    cJSON* JsonData = cJSON_GetObjectItemCaseSensitive(jsonData, "data");
	    if (!cJSON_IsArray(JsonData)) {
	        return; // Not an array, handle error as needed
	    }

	    std::array<std::string, MAX_DIGITAL_OUTPUTS> relayList;
	    size_t index = 0;
	    cJSON* Json;

	    // Iterate over the analog input names array
	    cJSON_ArrayForEach(Json, JsonData) {
	        if (cJSON_IsString(Json) && (Json->valuestring != NULL)) {
	            if (index < MAX_DIGITAL_OUTPUTS) {
	                relayList[index] = std::string(Json->valuestring);
	                ++index;
	            } else {
	                break; // More items in the list than MAX_ANALOG_INPUTS, handle as needed
	            }
	        }
	    }

	    setDigitalOutputNames(relayList);
}

void Config::setDHCPNetworkConfig(wiz_NetInfo* net_info) {
    std::array<uint8_t, 4> ip = {net_info->ip[0], net_info->ip[1], net_info->ip[2], net_info->ip[3]};
    std::array<uint8_t, 4> gateway = {net_info->gw[0], net_info->gw[1], net_info->gw[2], net_info->gw[3]};
    std::array<uint8_t, 4> subnet = {net_info->sn[0], net_info->sn[1], net_info->sn[2], net_info->sn[3]};
    std::array<uint8_t, 4> dns = {net_info->dns[0], net_info->dns[1], net_info->dns[2], net_info->dns[3]};

    setIP(ip);
    setGateway(gateway);
    setSubnet(subnet);
    setDNS(dns);
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
