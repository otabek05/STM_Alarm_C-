################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/Ethernet/W5500/w5500.c 

C_DEPS += \
./Core/Lib/Ethernet/W5500/w5500.d 

OBJS += \
./Core/Lib/Ethernet/W5500/w5500.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/Ethernet/W5500/%.o Core/Lib/Ethernet/W5500/%.su Core/Lib/Ethernet/W5500/%.cyclo: ../Core/Lib/Ethernet/W5500/%.c Core/Lib/Ethernet/W5500/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Lib/DHCP -I../Core/Lib/DNS -I../Core/Lib/JSON -I../Core/Lib/MQTT/MQTTPackage/src -I../Core/Lib/MQTT -I../Core/Lib/Ethernet/W5500 -I../Core/Lib/Ethernet -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-Ethernet-2f-W5500

clean-Core-2f-Lib-2f-Ethernet-2f-W5500:
	-$(RM) ./Core/Lib/Ethernet/W5500/w5500.cyclo ./Core/Lib/Ethernet/W5500/w5500.d ./Core/Lib/Ethernet/W5500/w5500.o ./Core/Lib/Ethernet/W5500/w5500.su

.PHONY: clean-Core-2f-Lib-2f-Ethernet-2f-W5500

