#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h" // C library
#include "MQTTClient.h"    // C library
#include "mqtt_interface.h" // C library
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "cJSON.h"

extern UART_HandleTypeDef huart1;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "main.h"
#include <array>
#include <string>
#include "config.h"
#include "MuxSelect.h"


#define MAX_PAYLOAD_LEN 1024

class Config;
class MuxSelect;
class PortAndPins {
public:
    GPIO_TypeDef* port;
    uint16_t pin;
};

class Status {
public:
    std::string name;
    int status;
};

class Utils {
public:
    Utils();


    void init(Config* configInstance, MuxSelect* muxInstance);
    void createJSON(std::string *message);
    void createUSARTRealTime(std::string *messsage);
    void createUSARTJson(std::string *message);
    bool switchRelay(GPIO_TypeDef* port, uint16_t switchPin, int status);
    static void playSound();
    static void print(const char* fmt, ...);
    void usartSwitch(cJSON* data);

    Config* conf;
    MuxSelect* mux;
    size_t getSwitchesCount() const;
    PortAndPins switches[8];
    PortAndPins digitalInputs[16];
    PortAndPins analogInputs[8];

private:
    int readGPIOPinState(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
    static Utils* instance;

};

//void print(const char* fmt, ...);

#endif // __cplusplus

#endif /* INC_UTILS_H_ */
