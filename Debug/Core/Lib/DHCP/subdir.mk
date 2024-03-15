################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/DHCP/dhcp.c 

C_DEPS += \
./Core/Lib/DHCP/dhcp.d 

OBJS += \
./Core/Lib/DHCP/dhcp.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/DHCP/%.o Core/Lib/DHCP/%.su Core/Lib/DHCP/%.cyclo: ../Core/Lib/DHCP/%.c Core/Lib/DHCP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Lib/DHCP -I../Core/Lib/DNS -I../Core/Lib/JSON -I../Core/Lib/MQTT/MQTTPackage/src -I../Core/Lib/MQTT -I../Core/Lib/Ethernet/W5500 -I../Core/Lib/Ethernet -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-DHCP

clean-Core-2f-Lib-2f-DHCP:
	-$(RM) ./Core/Lib/DHCP/dhcp.cyclo ./Core/Lib/DHCP/dhcp.d ./Core/Lib/DHCP/dhcp.o ./Core/Lib/DHCP/dhcp.su

.PHONY: clean-Core-2f-Lib-2f-DHCP

