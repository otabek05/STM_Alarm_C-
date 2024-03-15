################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/DNS/dns.c 

C_DEPS += \
./Core/Lib/DNS/dns.d 

OBJS += \
./Core/Lib/DNS/dns.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/DNS/%.o Core/Lib/DNS/%.su Core/Lib/DNS/%.cyclo: ../Core/Lib/DNS/%.c Core/Lib/DNS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Lib/DHCP -I../Core/Lib/DNS -I../Core/Lib/JSON -I../Core/Lib/MQTT/MQTTPackage/src -I../Core/Lib/MQTT -I../Core/Lib/Ethernet/W5500 -I../Core/Lib/Ethernet -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-DNS

clean-Core-2f-Lib-2f-DNS:
	-$(RM) ./Core/Lib/DNS/dns.cyclo ./Core/Lib/DNS/dns.d ./Core/Lib/DNS/dns.o ./Core/Lib/DNS/dns.su

.PHONY: clean-Core-2f-Lib-2f-DNS

