
#include "MuxSelect.h"


MuxSelect::MuxSelect() {
	muxSelect[0] = {GPIOE,  GPIO_PIN_4};
	muxSelect[1] = {GPIOE,  GPIO_PIN_5};
	muxSelect[2]  =  {GPIOE,  GPIO_PIN_6};


	analogCase[7] = {GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET};
	analogCase[6] = {GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET};
	analogCase[5] = {GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET};
	analogCase[4] = {GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET};
	analogCase[3] = {GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET};
	analogCase[2] = {GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET};
	analogCase[1] = {GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET};
	analogCase[0] = {GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET};

}

void MuxSelect::init(ADC_HandleTypeDef* hadc1Instance){
	hadc1 = hadc1Instance;
}


float MuxSelect::read() {
    float voltage = 0.0f;
    uint32_t adcValue;

    HAL_ADC_Start(hadc1);
    if (HAL_ADC_PollForConversion(hadc1, 100) == HAL_OK) {
        adcValue = HAL_ADC_GetValue(hadc1);
    }
    HAL_ADC_Stop(hadc1);
    voltage = adcValueToVoltage(adcValue, 12, 3.3f);

    return voltage;
}

float MuxSelect::adcValueToVoltage(uint32_t adcValue, uint8_t resolution, float referenceVoltage) {
    float measuredVoltage = (adcValue * referenceVoltage) / (1 << resolution);
    float scalingFactor = 10.0; // Adjusted based on the voltage divider calculation
    return measuredVoltage * scalingFactor;

}


AnalogReadings MuxSelect::SwitchAnalog() {
    static AnalogReadings readings; // Static to maintain lifetime beyond the function call

    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(muxSelect[0].port, muxSelect[0].pin, analogCase[i].S0);
        HAL_GPIO_WritePin(muxSelect[1].port, muxSelect[1].pin, analogCase[i].S1);
        HAL_GPIO_WritePin(muxSelect[2].port, muxSelect[2].pin, analogCase[i].S2);

        readings.values[i] = read();
      //  HAL_Delay(100);
    }

    return readings; // Return the struct containing the array
}
