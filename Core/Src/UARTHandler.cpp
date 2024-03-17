// UARTHandler.cpp
#include "UARTHandler.h"

#include "CplusUtils.h"

UARTHandler::UARTHandler() : bufferIndex(0) {
    memset(receiveBuffer, 0, sizeof(receiveBuffer));
}


void UARTHandler::init(UART_HandleTypeDef* uartHandle) {
    huart = uartHandle;
    HAL_UART_Receive_IT(huart, &rxByte, 1); // Start reception in interrupt mode
}

bool UARTHandler::isNewMessageArrived(){
	return newDataAvailable;
}

void UARTHandler::setNewDataAvailable(bool isArrived){
	newDataAvailable = isArrived;
}

void UARTHandler::onReceive() {


    if (bufferIndex < sizeof(receiveBuffer) - 1) {
        receiveBuffer[bufferIndex++] = rxByte;
        // Check for message end (e.g., newline character)
        if (rxByte == '\n') {
            receiveBuffer[bufferIndex] = '\0'; // Null-terminate the string
            processReceivedData();
            bufferIndex = 0; // Reset index for the next message
        }
    } else {
        // Handle buffer overflow
        print("Buffer overflow \r\n");
        bufferIndex = 0; // Reset buffer index
    }


    HAL_UART_Receive_IT(huart, &rxByte, 1); // Prepare to receive the next byte

}


void UARTHandler::processReceivedData() {


	cJSON *json = cJSON_Parse(reinterpret_cast<const char*>(receiveBuffer));
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }

        print("Invalid JSON \r\n");
        // Handle the error
    } else {
        // Process the JSON object
        cJSON *commandItem = cJSON_GetObjectItemCaseSensitive(json, "status");
        if (cJSON_IsString(commandItem) && (commandItem->valuestring != NULL)) {
            print("Received command: %s\n", commandItem->valuestring);
            // Implement your business logic here
        }
            newDataAvailable = false; // Reset the flag after processing
	        bufferIndex = 0; // Ready to start receiving new data

        cJSON_Delete(json);
    }





}
void UARTHandler::handleError(HAL_StatusTypeDef status)  {
	print("UART Receive Error: %d\r\n", status);
}

