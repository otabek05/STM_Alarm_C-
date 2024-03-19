#ifndef UARTHANDLER_H
#define UARTHANDLER_H

#include "CircularBuffer.h" // Include the CircularBuffer header
#include "CplusUtils.h"
extern "C" {
#include "stm32f4xx_hal.h" // Adjust this include according to your STM32 series
#include "cJSON.h"
}


#define INFO_TYPE 1
#define REAL_TIME_TYPE 2
#define MQTT_SETTING_TYPE 3
#define NETWORK_SETTING_TYPE 4
#define ANALOG_NAME_TYPE 5
#define DIGITAL_NAME_TYPE 6
#define RELAY_NAME_TYPE 7
#define RELAY_SWITCH_TYPE 8



class UARTHandler {
public:


    UARTHandler();

    Utils* utils;
    Config* config;

    void onReceive();
    void processReceivedData();
    void init(UART_HandleTypeDef* uartHandle,Utils* utilsInstance, Config* configInstance); // Initialization function
    void handleError(HAL_StatusTypeDef status);


    // Setters
    void setRealTimeData(bool requested);
    void setNewDataAvailable(bool isArrived);


    //Getters
    bool isNewMessageArrived();
    bool getRealTimeData();

private:
    UART_HandleTypeDef* huart;
    uint8_t rxByte;
    CircularBuffer rxBuffer; // Assuming this is correctly implemented elsewhere
    uint8_t receiveBuffer[512]; // Reintroduce this if you need a linear buffer
    size_t bufferIndex; // Reintroduce this for managing position in receiveBuffer
    bool newDataAvailable = false;
    bool realTimeData = false;

};

#endif // UARTHANDLER_H
