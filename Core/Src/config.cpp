#include "config.h"

uint8_t mac[6];
const std::array<std::string, 8> DEFAULT_ANALOG_INPUT_NAMES = {
    "Analog1", "Analog2", "Analog3", "Analog4",
    "Analog5", "Analog6", "Analog7", "Analog8"};

const std::array<std::string, 16> DEFAULT_DIGITAL_INPUT_NAMES = {
    "DI1", "DI2", "DI3", "DI4", "DI5", "DI6", "DI7", "DI8",
    "DI9", "DI10", "DI11", "DI12", "DI13", "DI14", "DI15", "DI16"};

const std::array<std::string, 8> DEFAULT_DIGITAL_OUTPUT_NAMES = {
    "Relay1", "Relay2", "Relay3", "Relay4",
    "Relay5", "Relay6", "Relay7", "Relay8"};
constexpr std::array<uint8_t, 4> DEFAULT_BROKER_IP = {175, 210, 42, 26};
constexpr std::array<uint8_t, 4> DEFAULT_IP = {172, 30, 1, 122};
constexpr std::array<uint8_t, 4> DEFAULT_GATEWAY = {172, 30, 1, 254};
constexpr std::array<uint8_t, 4> DEFAULT_SUBNET = {255, 255, 255, 0};
constexpr std::array<uint8_t, 4> DEFAULT_DNS = {8, 8, 8, 8};
constexpr uint16_t DEFAULT_PORT = 1883;
constexpr bool DEFAULT_DHCP_ENABLED = true;
constexpr bool DEFAULT_EXTENSION_ENABLED = true;
constexpr int DEFAULT_INTERVAL_TIME = 3;
constexpr int KEEP_ALIVE_INTERVAL = 60;
constexpr char DEFAULT_PASSWORD[] = "pass";
constexpr int DEFAULT_QOS = 1;


Config::Config(){

}

void Config::init(AT24C* eepromInstance) {


	eeprom = eepromInstance;


}

void Config::setUp() {
    static std::array<uint8_t, 4> ipStatic;

    setBrokerIP(eeprom->ReadIP(BROKER_IP_ID, ipStatic) ? ipStatic : DEFAULT_BROKER_IP);

    uint16_t port = eeprom->ReadInt(BROKER_PORT_ID);
    setBrokerPort(port ? port : DEFAULT_PORT);

    int dhcp = eeprom->ReadInt(DHCP_ENABLED_ID);
    setDHCPEnabled(dhcp == -1 ? DEFAULT_DHCP_ENABLED : static_cast<bool>(dhcp));

    if (!getDHCPEnabled()) {
        setIP(eeprom->ReadIP(IP_ID, ipStatic) ? ipStatic : DEFAULT_IP);
        setGateway(eeprom->ReadIP(GATEWAY_ID, ipStatic) ? ipStatic : DEFAULT_GATEWAY);
        setSubnet(eeprom->ReadIP(SUBNET_ID, ipStatic) ? ipStatic : DEFAULT_SUBNET);
        setDNS(eeprom->ReadIP(DNS_ID, ipStatic) ? ipStatic : DEFAULT_DNS);
    }


    int extension = eeprom->ReadInt(EXTENSION_ENABLED_ID);
    setExtentionEnabled(extension == -1 ? DEFAULT_EXTENSION_ENABLED : static_cast<bool>(extension));

    int interval = eeprom->ReadInt(INTERVAL_TIME_ID);
    setIntervalTime(interval == -1 ? DEFAULT_INTERVAL_TIME : interval);

    setKeepAliveInterval(KEEP_ALIVE_INTERVAL);
    setUsername("iot_devices");

    std::string passwd = eeprom->ReadString(PASSWORD_ID);
    setPassword(!passwd.empty() ? passwd : DEFAULT_PASSWORD);

    setTopicPublish("topic/pub");
    setQoS(DEFAULT_QOS);

    std::array<std::string, 8> analog;
    setAnalogInputNames(eeprom->ReadArrayString(ANALOGNAME_ID, analog) ? analog : DEFAULT_ANALOG_INPUT_NAMES);

    std::array<std::string, 8 > relay;
    setDigitalOutputNames(eeprom->ReadArrayString(RELAYNAME_ID, relay) ? relay : DEFAULT_DIGITAL_OUTPUT_NAMES);

    std::array<std::string, MAX_DIGITAL_INPUTS> digital_input;
    setDigitalInputNames(eeprom->ReadDigitalInput(DIGITALNAME_ID, digital_input) ? digital_input : DEFAULT_DIGITAL_INPUT_NAMES);

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
  //  std::string data = "sub";
    // Set MQTT client ID and topic to subscribe
    setClientId(clientID);
    setTopicSubscribe(data);
}



std::string createListString(std::array<uint8_t, 4> arr ) {
	std::string data;
	for (size_t i = 0; i < arr.size(); ++i) {
		    if (i > 0) {
		        // Add a period before all but the first number
		       data += ",";
		    }
		    data += std::to_string(arr[i]); // Convert each integer to a string
		}

	return data;
}


std::string createStringFromArray(std::array<std::string, MAX_DIGITAL_INPUTS>arr ) {
	std::string data;

	for(size_t i = 0 ; i < arr.size(); i++ ) {
		if (i > 0 ) {
			data += ",";
		}
		std::string val = arr[i];
		if (val != "") data +=val;
	}

	return data;

}



std::string createStringFromArray8len(std::array<std::string, 8>arr) {
	std::string data;

	for(size_t i = 0 ; i < arr.size(); i++ ) {
		if (i > 0 ) {
			data += ",";
		}
		std::string val = arr[i];
		if (val != "") data +=val;
	}

	return data;

}

char* Config::getInfoList(){
	std::string data = "1";
	std::string comma = ";";
	std::array<std::string,11 > lists;


	lists[0] = getClientId();
	lists[1] = createListString(getBrokerIP());
	lists[2] = std::to_string(getBrokerPort());
	lists[3] = createListString(getIP());
	lists[4] = createListString(getSubnet());
	lists[5] = createListString(getGateway());
	lists[6] = createListString(getDNS());
	lists[7] = createStringFromArray8len(getAnalogInputNames());
	lists[8] = createStringFromArray(getDigitalInputNames());
	lists[9] = createStringFromArray8len(getDigitalOutputNames());
	lists[10] = getDHCPEnabled() ? std::to_string(1) : std::to_string(0);
	for (size_t i = 0; i < lists.size(); i ++ ) {
		data += comma;
		data += lists[i];
	}


	data = data+ "\r";
	char* result = new char[data.length() + 1]; // +1 for null terminator
	strcpy(result, data.c_str());

	return result;
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
                size_t len = strlen(analogInputJson->valuestring);
                if (len >= 2 && len < 10) {
                analogInputs[index] = std::string(analogInputJson->valuestring);
                }
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
                size_t valueStringLength = strlen(digitalInputJson->valuestring);
                // Check if the string length is within the specified bounds
                if (valueStringLength >= 2 && valueStringLength <= 8) {
                    if (index < MAX_DIGITAL_INPUTS) {
                        digitalInputs[index] = std::string(digitalInputJson->valuestring);
                    }
                     ++index;
                }
                // Optionally, handle the case where the string does not meet the length requirements
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
	            	size_t len = strlen(Json->valuestring);
	            	if (len >= 2 && len < 10) {

	                relayList[index] = std::string(Json->valuestring);
	            	}
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
bool Config::getIpAssigned() const {return ip_assigned;}
bool Config::getExtentionEnabled() const {return extentionEnabled;}

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
void Config::setBrokerIP(const std::array<uint8_t, 4>& value) {
	broker_ip = value;
    eeprom->WriteIP(BROKER_IP_ID, value);
}
void Config::setBrokerPort(uint16_t value) {
	broker_port = value;
	eeprom->WriteInt(BROKER_PORT_ID, value);
}
void Config::setIP(const std::array<uint8_t, 4>& value) {
	ip = value;
	eeprom->WriteIP(IP_ID, value);
}
void Config::setGateway(const std::array<uint8_t, 4>& value) {
	gateway = value;
    eeprom->WriteIP(GATEWAY_ID, value);
}

void Config::setSubnet(const std::array<uint8_t, 4>& value) {
	subnet = value;
	eeprom->WriteIP(SUBNET_ID, value);
}
void Config::setDNS(const std::array<uint8_t, 4>& value) {
	dns = value;
	eeprom->WriteIP(DNS_ID, value);
}
void Config::setKeepAliveInterval(uint16_t value) {
	keep_alive_interval = value;
}
void Config::setDHCPEnabled(bool value) {
	dhcp_enabled = value;
	eeprom->WriteInt(DHCP_ENABLED_ID, value);

}
void Config::setIpAssigned(bool value) {ip_assigned = value;}
void Config::setExtentionEnabled(bool value) {
	extentionEnabled = value;
	eeprom->WriteInt(EXTENSION_ENABLED_ID, value);
}
void Config::setIntervalTime(uint32_t value) {
	interval_time = value;
	eeprom->WriteInt(INTERVAL_TIME_ID, value);

}

void Config::setUsername(const std::string& value) { username = value; }
void Config::setClientId(const std::string& value) { clientId = value; }
void Config::setPassword(const std::string& value) { password = value; }


void Config::setTopicSubscribe(const std::string& value) { topic_subscribe = value; }
void Config::setTopicPublish(const std::string& value) { topic_publish = value; }
void Config::setQoS(int value) { qos = value; }
void Config::setAnalogInputNames(const std::array<std::string, MAX_ANALOG_INPUTS>& value) {
	eeprom->WriteArrayString(ANALOGNAME_ID, value);
	analog_input_names = value;

}
void Config::setDigitalInputNames(const std::array<std::string, MAX_DIGITAL_INPUTS>& value) {
	digital_input_names = value;
	eeprom->WriteDigitalInput(DIGITALNAME_ID, value);
}
void Config::setDigitalOutputNames(const std::array<std::string, MAX_DIGITAL_OUTPUTS>& value) {
	digital_output_names = value;
    eeprom->WriteArrayString(RELAYNAME_ID, value);
}
