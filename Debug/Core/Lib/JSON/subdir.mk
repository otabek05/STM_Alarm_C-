################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/JSON/cJSON.c 

C_DEPS += \
./Core/Lib/JSON/cJSON.d 

OBJS += \
./Core/Lib/JSON/cJSON.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/JSON/%.o Core/Lib/JSON/%.su Core/Lib/JSON/%.cyclo: ../Core/Lib/JSON/%.c Core/Lib/JSON/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Lib/DHCP -I../Core/Lib/DNS -I../Core/Lib/JSON -I../Core/Lib/MQTT/MQTTPackage/src -I../Core/Lib/MQTT -I../Core/Lib/Ethernet/W5500 -I../Core/Lib/Ethernet -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-JSON

clean-Core-2f-Lib-2f-JSON:
	-$(RM) ./Core/Lib/JSON/cJSON.cyclo ./Core/Lib/JSON/cJSON.d ./Core/Lib/JSON/cJSON.o ./Core/Lib/JSON/cJSON.su

.PHONY: clean-Core-2f-Lib-2f-JSON

