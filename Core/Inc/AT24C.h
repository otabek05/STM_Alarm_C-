#ifndef AT24C_H
#define AT24C_H

#include "stm32f4xx_hal.h"
#include <string>
#include <array>

class AT24C {
public:
    explicit AT24C(I2C_HandleTypeDef *hi2c);

    bool WriteString(uint16_t key, const std::string &value);
    std::string ReadString(uint16_t key);

    bool WriteIP(uint16_t key, const std::array<uint8_t, 4>& ip);
    bool ReadIP(uint16_t key, std::array<uint8_t, 4>& ip);

    bool WriteInt(uint16_t key, int value);
    int ReadInt(uint16_t key);

    bool WriteArrayString(uint16_t key, const std::array<std::string, 8>& strings);
    bool ReadArrayString(uint16_t key, std::array<std::string, 8>& strings);

    bool WriteDigitalInput(uint16_t key, const std::array<std::string, 16>& strings);
    bool ReadDigitalInput(uint16_t key, std::array<std::string, 16>& strings);

private:
    I2C_HandleTypeDef *_hi2c;

    HAL_StatusTypeDef WriteBytes(size_t address, const uint8_t *data, size_t length);
    HAL_StatusTypeDef ReadBytes(size_t address, uint8_t *data, size_t length);
    size_t CalculateAddress(uint16_t key);
};

#endif // AT24C_H



