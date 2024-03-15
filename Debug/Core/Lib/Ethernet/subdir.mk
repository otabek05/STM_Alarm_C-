################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/Ethernet/ethertnet.c \
../Core/Lib/Ethernet/socket.c \
../Core/Lib/Ethernet/wizchip_conf.c 

C_DEPS += \
./Core/Lib/Ethernet/ethertnet.d \
./Core/Lib/Ethernet/socket.d \
./Core/Lib/Ethernet/wizchip_conf.d 

OBJS += \
./Core/Lib/Ethernet/ethertnet.o \
./Core/Lib/Ethernet/socket.o \
./Core/Lib/Ethernet/wizchip_conf.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/Ethernet/%.o Core/Lib/Ethernet/%.su Core/Lib/Ethernet/%.cyclo: ../Core/Lib/Ethernet/%.c Core/Lib/Ethernet/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Lib/DHCP -I../Core/Lib/DNS -I../Core/Lib/JSON -I../Core/Lib/MQTT/MQTTPackage/src -I../Core/Lib/MQTT -I../Core/Lib/Ethernet/W5500 -I../Core/Lib/Ethernet -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-Ethernet

clean-Core-2f-Lib-2f-Ethernet:
	-$(RM) ./Core/Lib/Ethernet/ethertnet.cyclo ./Core/Lib/Ethernet/ethertnet.d ./Core/Lib/Ethernet/ethertnet.o ./Core/Lib/Ethernet/ethertnet.su ./Core/Lib/Ethernet/socket.cyclo ./Core/Lib/Ethernet/socket.d ./Core/Lib/Ethernet/socket.o ./Core/Lib/Ethernet/socket.su ./Core/Lib/Ethernet/wizchip_conf.cyclo ./Core/Lib/Ethernet/wizchip_conf.d ./Core/Lib/Ethernet/wizchip_conf.o ./Core/Lib/Ethernet/wizchip_conf.su

.PHONY: clean-Core-2f-Lib-2f-Ethernet

