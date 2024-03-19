#include "UARTHandler.h"
#include "CplusUtils.h"
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
        // Error handling
        if(result == HAL_ERROR) {
            print("UART Receive_IT Error: HAL_ERROR\r\n");
        } else if(result == HAL_BUSY) {
            print("UART Receive_IT Error: HAL_BUSY\r\n");
        } else if(result == HAL_TIMEOUT) {
            print("UART Receive_IT Error: HAL_TIMEOUT\r\n");
        } else {
            print("UART Receive_IT Error: Unknown Error Code %d\r\n", result);
        }
    }
}

void UARTHandler::setRealTimeData(bool requested){

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
        print("Buffer overflow \r\n");
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
        if (cJSON_IsNumber(commandItem)) {
            int type = commandItem->valueint;

            switch(type) {
                case INFO_TYPE: {
                    utils->print("Message has been arrived: %d\r\n", type);
                    // Scope introduced for INFO_TYPE case
                    std::string data = config->getInfoList();
                    const char* dataToSend = data.c_str();
                    HAL_UART_Transmit(&huart1, reinterpret_cast<uint8_t*>(const_cast<char*>(dataToSend)), strlen(dataToSend), HAL_MAX_DELAY);
                    break;
                }
                case REAL_TIME_TYPE: {
                    // Scope for REAL_TIME_TYPE case
                    // Real-time handling code here
                    break;
                }
                case MQTT_SETTING_TYPE: {
                    // Scope for MQTT_SETTING_TYPE case
                    // MQTT setting handling code here
                    break;
                }
                case NETWORK_SETTING_TYPE: {
                    // Scope for NETWORK_SETTING_TYPE case
                    // Network setting handling code here
                    break;
                }
                case ANALOG_NAME_TYPE: {
                    // Scope for ANALOG_NAME_TYPE case
                    // Analog name handling code here
                    break;
                }
                // Continue for other cases, each in its own scope if needed
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



void UARTHandler::handleError(HAL_StatusTypeDef status) {
    print("UART Receive Error: %d\r\n", status);
    // Consider resetting UART reception here to recover from errors
}



