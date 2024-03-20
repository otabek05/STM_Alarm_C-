#include "UARTHandler.h"
#include <cstring> // For memset and memcpy
#include <array>
#include <string>

UARTHandler::UARTHandler() : bufferIndex(0), newDataAvailable(false) {
    memset(receiveBuffer, 0, sizeof(receiveBuffer));
}

void UARTHandler::init(UART_HandleTypeDef* uartHandle, Utils* utilsInstance, Config* configInstance) {
    huart = uartHandle;
    utils = utilsInstance;
    config = configInstance;

    HAL_StatusTypeDef result = HAL_UART_Receive_IT(huart, &rxByte, 1);

    if(result != HAL_OK) {

    }
}

void UARTHandler::setRealTimeData(bool requested){
     realTimeData = requested;
}

bool UARTHandler::getRealTimeData(){
	return realTimeData;
}

bool UARTHandler::isNewMessageArrived() {
    return newDataAvailable;
}

void UARTHandler::setNewDataAvailable(bool isArrived) {
    newDataAvailable = isArrived;
}

void UARTHandler::onReceive() {


    if (bufferIndex < sizeof(receiveBuffer) - 1) {
        receiveBuffer[bufferIndex++] = rxByte;
        // Check for message end (e.g., newline character)
      //  utils->print("Entered to this function \r\n");
        if (rxByte == '\n') {
            receiveBuffer[bufferIndex] = '\0';

            bufferIndex = 0; // Reset index for the next message
            setNewDataAvailable(true);
        }
    } else {
        // Handle buffer overflow
      //  print("Buffer overflow \r\n");
        bufferIndex = 0; // Reset buffer index
    }


    HAL_UART_Receive_IT(huart, &rxByte, 1); // Prepare to receive the next byte

}

void UARTHandler::processReceivedData() {
    if (!isNewMessageArrived()) return; // Early exit if no new data
    cJSON *json = cJSON_Parse(reinterpret_cast<const char*>(receiveBuffer));
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
    } else {
        cJSON *commandItem = cJSON_GetObjectItemCaseSensitive(json, "type");
        cJSON *item = cJSON_GetObjectItemCaseSensitive(json, "data");
        if (cJSON_IsNumber(commandItem)) {
            int type = commandItem->valueint;

            switch(type) {
                case INFO_TYPE: {
                	 utils->print("Message has been arrived: %d\r\n", type);
                	    char* data = config->getInfoList();
                	    size_t data_len = strlen(data);
                	    HAL_UART_Transmit(&huart1, reinterpret_cast<uint8_t*>(data), data_len, HAL_MAX_DELAY); // +1 for the added "\r"
                }
                case REAL_TIME_TYPE: {
                	utils->playSound();
                	 if (cJSON_IsBool(item)) {
                       bool status = cJSON_IsTrue(item) ? true : false;
            	       setRealTimeData(status);
                	 }
                	break;
                }
                case MQTT_SETTING_TYPE: {
                	utils->playSound();
                	config->setMQTTBroker(item);
                	utils->print("MQTT config has been arrived!!! \r\n");
                    break;
                }
                case NETWORK_SETTING_TYPE :{
                	config->setNetworkSettings(item);
                	utils->playSound();
                	utils->print("Netwokr Settings has been successfully configured \r\n");
                    break;
                }
                case ANALOG_NAME: {
                	utils->playSound();
                	config->setAnalogInputNamesFromJson(json);
                    utils->print("Analog Names has been arrived!!! \r\n");
                    break;
                }
                case DIGITAL_NAME: {
                	utils->playSound();
                	config->setDigitalInputNamesFromJson(json);
                	utils->print("Digital Names has been arrived!!! \r\n");
                	break;
                }
                case RELAY_NAME: {
                	config->setRelayNamesFromJson(json);
                	utils->print("Relay Names has been arrived!!! \r\n");
                	break;
                }

                case RELAY_SWITCH: {
                	utils->usartSwitch(item);
                	utils->print("Relay Switch has been arrived \r\n");
                	break;
                }
                default: {
                    // Handle unknown type
                    break;
                }
            }
        }
        cJSON_Delete(json); // Ensure json is deleted here to avoid memory leak
    }

    setNewDataAvailable(false); // Reset the flag after processing
    memset(receiveBuffer, 0, bufferIndex); // Clear the buffer
    bufferIndex = 0; // Ready for new data
}


void UARTHandler::SendRealTimeData(std::string* data) {


    utils->createUSARTJson(data);
    // Append "\r" to the end of the data
    *data += "\r";
    const char* serializedData = data->c_str();
    HAL_UART_Transmit(&huart1, reinterpret_cast<uint8_t*>(const_cast<char*>(serializedData)), strlen(serializedData), HAL_MAX_DELAY);

}



void UARTHandler::handleError(HAL_StatusTypeDef status) {
// print("UART Receive Error: %d\r\n", status);
    // Consider resetting UART reception here to recover from errors
}



