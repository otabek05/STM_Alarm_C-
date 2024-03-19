################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/MQTT/MQTTPacket/src/MQTTConnectClient.c \
../Core/Lib/MQTT/MQTTPacket/src/MQTTConnectServer.c \
../Core/Lib/MQTT/MQTTPacket/src/MQTTDeserializePublish.c \
../Core/Lib/MQTT/MQTTPacket/src/MQTTFormat.c \
../Core/Lib/MQTT/MQTTPacket/src/MQTTPacket.c \
../Core/Lib/MQTT/MQTTPacket/src/MQTTSerializePublish.c \
../Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeClient.c \
../Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeServer.c \
../Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c \
../Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c 

C_DEPS += \
./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectClient.d \
./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectServer.d \
./Core/Lib/MQTT/MQTTPacket/src/MQTTDeserializePublish.d \
./Core/Lib/MQTT/MQTTPacket/src/MQTTFormat.d \
./Core/Lib/MQTT/MQTTPacket/src/MQTTPacket.d \
./Core/Lib/MQTT/MQTTPacket/src/MQTTSerializePublish.d \
./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeClient.d \
./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeServer.d \
./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d \
./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d 

OBJS += \
./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectClient.o \
./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectServer.o \
./Core/Lib/MQTT/MQTTPacket/src/MQTTDeserializePublish.o \
./Core/Lib/MQTT/MQTTPacket/src/MQTTFormat.o \
./Core/Lib/MQTT/MQTTPacket/src/MQTTPacket.o \
./Core/Lib/MQTT/MQTTPacket/src/MQTTSerializePublish.o \
./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeClient.o \
./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeServer.o \
./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o \
./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/MQTT/MQTTPacket/src/%.o Core/Lib/MQTT/MQTTPacket/src/%.su Core/Lib/MQTT/MQTTPacket/src/%.cyclo: ../Core/Lib/MQTT/MQTTPacket/src/%.c Core/Lib/MQTT/MQTTPacket/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Lib/DHCP -I../Core/Lib/DNS -I../Core/Lib/JSON -I../Core/Lib/MQTT/MQTTPackage/src -I../Core/Lib/MQTT -I../Core/Lib/Ethernet/W5500 -I../Core/Lib/Ethernet -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-MQTT-2f-MQTTPacket-2f-src

clean-Core-2f-Lib-2f-MQTT-2f-MQTTPacket-2f-src:
	-$(RM) ./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectClient.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectClient.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectClient.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectClient.su ./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectServer.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectServer.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectServer.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTConnectServer.su ./Core/Lib/MQTT/MQTTPacket/src/MQTTDeserializePublish.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTDeserializePublish.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTDeserializePublish.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTDeserializePublish.su ./Core/Lib/MQTT/MQTTPacket/src/MQTTFormat.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTFormat.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTFormat.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTFormat.su ./Core/Lib/MQTT/MQTTPacket/src/MQTTPacket.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTPacket.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTPacket.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTPacket.su ./Core/Lib/MQTT/MQTTPacket/src/MQTTSerializePublish.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTSerializePublish.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTSerializePublish.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTSerializePublish.su ./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeClient.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeClient.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeClient.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeClient.su ./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeServer.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeServer.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeServer.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTSubscribeServer.su ./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.su ./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.cyclo ./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d ./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o ./Core/Lib/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.su

.PHONY: clean-Core-2f-Lib-2f-MQTT-2f-MQTTPacket-2f-src

