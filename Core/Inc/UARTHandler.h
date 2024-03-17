#ifndef UARTHANDLER_H
#define UARTHANDLER_H

#include "CircularBuffer.h" // Include the CircularBuffer header
extern "C" {
#include "stm32f4xx_hal.h" // Adjust this include according to your STM32 series
#include "cJSON.h" // If using cJSON
}

class UARTHandler {
public:
    UARTHandler();
    void onReceive();
    void processReceivedData();
    void init(UART_HandleTypeDef* uartHandle); // Initialization function
    void handleError(HAL_StatusTypeDef status);
    void setNewDataAvailable(bool isArrived) ;
    bool isNewMessageArrived();
private:
    UART_HandleTypeDef* huart;
    uint8_t rxByte;
    CircularBuffer rxBuffer; // Assuming this is correctly implemented elsewhere
    uint8_t receiveBuffer[1024]; // Reintroduce this if you need a linear buffer
    size_t bufferIndex; // Reintroduce this for managing position in receiveBuffer
    bool newDataAvailable = false;
};

#endif // UARTHANDLER_H
