/*
 * utils.h
 *
 *  Created on: Mar 5, 2024
 *      Author: user
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

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

#ifdef __cplusplus
}
#endif

#include "main.h"
#include <array> // Use std::array for fixed-size array management
#include <string> // Use std::string for string management

#define MAX_PAYLOAD_LEN 1024 // Maximum payload length

extern UART_HandleTypeDef huart1;

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} PortAndPins;

typedef struct {
    std::string name; // Changed to std::string
    int status;
} Status;

extern PortAndPins digitalInputPins[16];
extern PortAndPins switchPins[8];

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif
/*
// C++ specific function declarations
void ReadStatus(std::string &buffer, SystemConfig *conf); // Adjusted to use std::string

void GetMAC(SystemConfig *conf);

void receive_and_send_back();


void Switch(GPIO_TypeDef* port, uint16_t switchPin, int status);


void messageArrived(MessageData* data);

*/
void PlayButtonSound(void);
void Print(const char* fmt, ...);
void UART_Printf(const char *fmt, ...);
#endif /* SRC_UTILS_H_ */
