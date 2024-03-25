
#include "utils.h"
#include <cmath>


Utils* Utils::instance = nullptr;

Utils::Utils(){
	Utils::instance = this;
}

void Utils::init(Config* config, MuxSelect* muxInstance){
	mux = muxInstance;
	conf = config;


	switches[0] = {GPIOE, GPIO_PIN_12}; // switch1
	switches[1] = {GPIOE, GPIO_PIN_13}; // switch2
	switches[2] = {GPIOE, GPIO_PIN_14}; // switch3
	switches[3] = {GPIOE, GPIO_PIN_15}; // switch4
	switches[4] = {GPIOA, GPIO_PIN_4};  // switch5
	switches[5] = {GPIOA, GPIO_PIN_5};  // switch6
	switches[6] = {GPIOA, GPIO_PIN_6};  // switch7
	switches[7] = {GPIOA, GPIO_PIN_7};  // switch8


    digitalInputs[0] = {GPIOC, GPIO_PIN_0};   // DI1
    digitalInputs[1] = {GPIOC, GPIO_PIN_1};   // DI2
    digitalInputs[2] = {GPIOC, GPIO_PIN_2};   // DI3
    digitalInputs[3] = {GPIOC, GPIO_PIN_3};   // DI4
    digitalInputs[4] = {GPIOD, GPIO_PIN_8};   // DI5
    digitalInputs[5] = {GPIOD, GPIO_PIN_9};   // DI6
    digitalInputs[6] = {GPIOD, GPIO_PIN_10};  // DI7
    digitalInputs[7] = {GPIOD, GPIO_PIN_13};  // DI8
    digitalInputs[8] = {GPIOC, GPIO_PIN_6};   // DI9
    digitalInputs[9] = {GPIOC, GPIO_PIN_7};   // DI10
    digitalInputs[10] = {GPIOC, GPIO_PIN_8};  // DI11
    digitalInputs[11] = {GPIOC, GPIO_PIN_9};  // DI12
    digitalInputs[12] = {GPIOA, GPIO_PIN_8};  // DI13
    digitalInputs[13] = {GPIOA, GPIO_PIN_9};  // DI14
    digitalInputs[14] = {GPIOA, GPIO_PIN_10}; // DI15
    digitalInputs[15] = {GPIOA, GPIO_PIN_11}; // DI16


}
void Utils::print(const char* fmt, ...){

	 char buff[256];
	 va_list args;
	 va_start(args, fmt);
	 vsnprintf(buff, sizeof(buff), fmt, args);
	 HAL_UART_Transmit(&huart1, (uint8_t*)buff, strlen(buff),
	                      HAL_MAX_DELAY);
	 va_end(args);

}


size_t Utils::getSwitchesCount() const {
    return sizeof(switches) / sizeof(switches[0]);
}

void Utils::playSound(){
	HAL_GPIO_WritePin(sound_GPIO_Port, sound_Pin, GPIO_PIN_SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(sound_GPIO_Port, sound_Pin, GPIO_PIN_RESET);
	HAL_Delay(20);
}

bool Utils::switchRelay(GPIO_TypeDef* port, uint16_t switchPin, int status){
    if (status > 1) {
    	print("Status is not valid %d \r\n", status);
    	return false;
    }
	GPIO_PinState gpioStatus = status == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET;
	playSound();
	HAL_GPIO_WritePin(port, switchPin, gpioStatus);
	return true;
}

int Utils::readGPIOPinState(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET ? 0 : 1;
}


void Utils::createJSON(std::string *message) {
    cJSON *root = cJSON_CreateObject();
    // Change aiArray from an array to an object.
    cJSON *aiObj = cJSON_CreateObject();
    cJSON *diObj = cJSON_CreateObject();
    cJSON *doObj = cJSON_CreateObject();

    AnalogReadings analogValue = mux->SwitchAnalog();

    uint8_t lenrelay = conf->getExtentionEnabled() ? 8 : 4;
    for (int i = 0; i < lenrelay; i++) {
    	char formattedStr[32];
        int status = readGPIOPinState(switches[i].port, switches[i].pin);
        snprintf(formattedStr, sizeof(formattedStr), "%d,%d", i+1, status);
        cJSON_AddStringToObject(doObj, conf->getDigitalOutputName(i).c_str(), formattedStr);
    }
    uint8_t len = conf->getExtentionEnabled() ? 16 : 8;
    for (int i = 0; i < len; i++) {

    	char formattedStr[32];
        int status = readGPIOPinState(digitalInputs[i].port, digitalInputs[i].pin);
    	snprintf(formattedStr, sizeof(formattedStr), "%d,%d", i+1, status);
        cJSON_AddStringToObject(diObj, conf->getDigitalInputName(i).c_str(),formattedStr);
    }

    for (int i = 0; i < 8; i++) {
        float status = analogValue.values[i]; // Placeholder, adjust according to your implementation
        char formattedStatus[32]; // Buffer to hold the formatted float string
        snprintf(formattedStatus, sizeof(formattedStatus), "%d,%.2f", i+1, status);
        cJSON_AddStringToObject(aiObj, conf->getAnalogInputName(i).c_str(), formattedStatus);
    }

    // Attach the modified aiObj directly to the root, instead of an array.
    cJSON_AddItemToObject(root, "ai", aiObj);
    cJSON_AddItemToObject(root, "di", diObj);
    cJSON_AddItemToObject(root, "do", doObj);
    cJSON_AddStringToObject(root, "mac", conf->getClientId().c_str());

    // Print and assign the JSON string
    char* json_string = cJSON_Print(root);
    if (json_string != nullptr) {
        *message = json_string;
        free(json_string); // Free the allocated memory
    }
    cJSON_Delete(root); // Clean up the cJSON object
}

void Utils::createUSARTRealTime(std::string *messsage) {
	std::string data = "2";
	std::string comma = ";";
	std::array<std::string, 3 > list;
	AnalogReadings analogValue = mux->SwitchAnalog();


	for (size_t i = 0 ; i < 8 ; i++) {
		float status = analogValue.values[i]; // Placeholder, adjust according to your implementation
		char formattedStatus[32];
		snprintf(formattedStatus, sizeof(formattedStatus), "%.2f", status);
		if (i > 0 ) {
			list[0] += ",";
		}

		list[0] += formattedStatus;
	}

	//uint8_t len = conf->getExtentionEnabled() ? 16 : 8;
	for (size_t i = 0; i < 16; i ++) {
		int status = readGPIOPinState(digitalInputs[i].port, digitalInputs[i].pin);
		if (i > 0 ) {
			list[1] += ",";
		}
		list[1] += std::to_string(status);
	}

	//uint8_t relayLen = conf->getExtentionEnabled() ? 8 : 4;
	for (size_t i = 0; i < 8;  i++) {
		int status = readGPIOPinState(switches[i].port, switches[i].pin);
		if (i > 0 ) {
			list[2] += ",";
		}
		list[2] += std::to_string(status);
	}

	for (size_t i = 0; i < list.size(); i ++) {
		data += comma;
		data+= list[i];
	}

	data = data+ "\r";
    *messsage = data;

}



void Utils::createUSARTJson(std::string *message) {
	 cJSON* rootJson = cJSON_CreateObject();
	 cJSON* outputsArray = cJSON_CreateArray();
	 cJSON* inputsArray = cJSON_CreateArray();

	    for (int i = 0; i < 8; i++) {
	        int status = readGPIOPinState(switches[i].port, switches[i].pin);
	        cJSON_AddItemToArray(outputsArray, cJSON_CreateBool(status));
	    }

	    for (int i = 0; i < 16; i++) {
	        int status = readGPIOPinState(digitalInputs[i].port, digitalInputs[i].pin);
	        cJSON_AddItemToArray(inputsArray, cJSON_CreateBool(status));
	    }

	    cJSON_AddItemToObject(rootJson, "type", cJSON_CreateString("realTime"));
	    cJSON_AddItemToObject(rootJson, "di", inputsArray);
	    cJSON_AddItemToObject(rootJson, "relay", outputsArray);

	    char* json_string = cJSON_Print(rootJson);
	    if (json_string != nullptr) {
	        *message = json_string;
	        free(json_string); // Remember to free the allocated memory
	    }

	    cJSON_Delete(rootJson);
}

void Utils::usartSwitch(cJSON* data) {
    const cJSON *number = cJSON_GetObjectItemCaseSensitive(data, "number");
    // Directly getting the status as expected to be true/false (1/0)
    const cJSON *status = cJSON_GetObjectItemCaseSensitive(data, "status");


    // Validate number as a numeric value and status also; although boolean, it comes as numeric in cJSON.
    if (cJSON_IsNumber(number) && cJSON_IsBool(status)) { // Assuming status comes as a numeric representation of a boolean

        if (number->valueint >= 1 && number->valueint <= 8) {
            int arrayIndex = number->valueint - 1;
            PortAndPins targetSwitch = switches[arrayIndex];

            bool success = switchRelay(targetSwitch.port, targetSwitch.pin, status->valueint);
            if (success) {
                print("The %d switch has been toggled.\r\n", number->valueint);
            } else {
                print("There is an issue with switch \r\n");
            }
        }
    }
}

/*

void print(const char* fmt, ...){
	 char buff[256];
	 va_list args;
	 va_start(args, fmt);
	 vsnprintf(buff, sizeof(buff), fmt, args);
	 HAL_UART_Transmit(&huart1, (uint8_t*)buff, strlen(buff),
	                      HAL_MAX_DELAY);
	 va_end(args);
}

*/



/*
void print(const char* fmt, ...) {
    char formattedString[1024];
    va_list args;

    // Start variadic arguments handling.
    va_start(args, fmt);
    // Format the string according to the arguments passed.
    vsnprintf(formattedString, sizeof(formattedString), fmt, args);
    // End variadic arguments handling.
    va_end(args);

    // Create a JSON object.
    cJSON *root = cJSON_CreateObject();

    // Check if root creation was successful.
    if (root == NULL) {
        return;
    }

    // Add "type" and "data" to the JSON object.
    cJSON_AddItemToObject(root, "type", cJSON_CreateString("console"));
    cJSON_AddItemToObject(root, "data", cJSON_CreateString(formattedString));

    // Convert the JSON object to a string.
    char *jsonString = cJSON_PrintUnformatted(root);
    if (jsonString == NULL) {
        cJSON_Delete(root); // Ensure memory is freed on failure.
        return;
    }

    // Transmit the JSON string over UART.
    HAL_UART_Transmit(&huart1, (uint8_t*)jsonString, strlen(jsonString), HAL_MAX_DELAY);

    // Free the JSON string and delete the cJSON object to free memory.
    cJSON_free(jsonString);
    cJSON_Delete(root);
}

*/
