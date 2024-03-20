
#ifndef INC_MUXSELECT_H_
#define INC_MUXSELECT_H_


extern "C" {
#include "stm32f4xx_hal.h"


}

#include "utils.h"
#include <string.h>
#include "config.h"
#include <string>
#include <cstdio>


class Mux {
public:
    GPIO_TypeDef* port;
    uint16_t pin;
};


class AnalogCase {
public:
	GPIO_PinState S2;
	GPIO_PinState S1;
	GPIO_PinState S0;

};

struct AnalogReadings {
    float values[8];
};

class MuxSelect{
public:
	MuxSelect();
	void init(ADC_HandleTypeDef* hadc1Instance);
	float read();
	AnalogReadings SwitchAnalog();
	Mux muxSelect[3];

	AnalogCase analogCase[8];



private:
	float adcValueToVoltage(uint32_t adcValue, uint8_t resolution, float referenceVoltage);
	ADC_HandleTypeDef* hadc1;
};


#endif /* INC_MUXSELECT_H_ */
