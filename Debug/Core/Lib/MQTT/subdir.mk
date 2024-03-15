################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/MQTT/MQTTClient.c \
../Core/Lib/MQTT/mqtt_interface.c 

C_DEPS += \
./Core/Lib/MQTT/MQTTClient.d \
./Core/Lib/MQTT/mqtt_interface.d 

OBJS += \
./Core/Lib/MQTT/MQTTClient.o \
./Core/Lib/MQTT/mqtt_interface.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/MQTT/%.o Core/Lib/MQTT/%.su Core/Lib/MQTT/%.cyclo: ../Core/Lib/MQTT/%.c Core/Lib/MQTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Lib/DHCP -I../Core/Lib/DNS -I../Core/Lib/JSON -I../Core/Lib/MQTT/MQTTPackage/src -I../Core/Lib/MQTT -I../Core/Lib/Ethernet/W5500 -I../Core/Lib/Ethernet -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-MQTT

clean-Core-2f-Lib-2f-MQTT:
	-$(RM) ./Core/Lib/MQTT/MQTTClient.cyclo ./Core/Lib/MQTT/MQTTClient.d ./Core/Lib/MQTT/MQTTClient.o ./Core/Lib/MQTT/MQTTClient.su ./Core/Lib/MQTT/mqtt_interface.cyclo ./Core/Lib/MQTT/mqtt_interface.d ./Core/Lib/MQTT/mqtt_interface.o ./Core/Lib/MQTT/mqtt_interface.su

.PHONY: clean-Core-2f-Lib-2f-MQTT

