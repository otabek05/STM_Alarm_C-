#include "AT24C.h"
#include <cstring>

#define EEPROM_ID         0x50<<1
#define EEPROM_PAGE_SIZE  32

AT24C::AT24C(I2C_HandleTypeDef *hi2c) : _hi2c(hi2c) {}

#include <vector>
#include <algorithm>



bool AT24C::WriteString(uint16_t key, const std::string &value) {
    std::vector<uint8_t> data(value.begin(), value.end());
    data.push_back(';'); // End marker
    return WriteBytes(CalculateAddress(key), data.data(), data.size()) == HAL_OK;
}

std::string AT24C::ReadString(uint16_t key) {
    std::vector<uint8_t> data(128); // Assuming a maximum string length
    if (ReadBytes(CalculateAddress(key), data.data(), data.size()) == HAL_OK) {
        auto endPos = std::find(data.begin(), data.end(), ';');
        if (endPos != data.end()) {
            return std::string(data.begin(), endPos);
        }
    }
    return "";
}

bool AT24C::WriteIP(uint16_t key, const std::array<uint8_t, 4>& ip) {
    return WriteBytes(CalculateAddress(key), ip.data(), ip.size()) == HAL_OK;
}

std::array<uint8_t, 4> AT24C::ReadIP(uint16_t key) {
    std::array<uint8_t, 4> ip = {0};
    ReadBytes(CalculateAddress(key), ip.data(), ip.size());
    return ip;
}

bool AT24C::WriteInt(uint16_t key, int value) {
    uint8_t data[4];
    data[0] = (value >> 24) & 0xFF;
    data[1] = (value >> 16) & 0xFF;
    data[2] = (value >> 8) & 0xFF;
    data[3] = value & 0xFF;
    return WriteBytes(CalculateAddress(key), data, sizeof(data)) == HAL_OK;
}

int AT24C::ReadInt(uint16_t key) {
    uint8_t data[4];
    if (ReadBytes(CalculateAddress(key), data, sizeof(data)) == HAL_OK) {
        int value = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
        return value;
    }
    return -1; // Error or not found
}

size_t AT24C::CalculateAddress(uint16_t key) {
    // Example: Each key represents a new block of 100 bytes
    return static_cast<size_t>(key) * 100;
}



HAL_StatusTypeDef AT24C::WriteBytes(size_t address, const uint8_t *data, size_t length) {
    HAL_StatusTypeDef error = HAL_OK;
    size_t bytesLeft = length;
    size_t currentOffset = 0;

    while (bytesLeft > 0) {
        size_t currentPageStart = address + currentOffset;
        size_t currentPageEnd = ((currentPageStart / EEPROM_PAGE_SIZE) + 1) * EEPROM_PAGE_SIZE;
        size_t spaceInCurrentPage = currentPageEnd - currentPageStart;
        size_t bytesToWriteNow = (bytesLeft < spaceInCurrentPage) ? bytesLeft : spaceInCurrentPage;

        error = HAL_I2C_Mem_Write(_hi2c, EEPROM_ID, currentPageStart, I2C_MEMADD_SIZE_16BIT, const_cast<uint8_t*>(data + currentOffset), bytesToWriteNow, 1000);
        if (error != HAL_OK) {
            return error;
        }
        HAL_Delay(5); // EEPROM page write delay, adjust as necessary for your EEPROM

        currentOffset += bytesToWriteNow;
        bytesLeft -= bytesToWriteNow;
    }

    return error;
}

HAL_StatusTypeDef AT24C::ReadBytes(size_t address, uint8_t *data, size_t length) {
    return HAL_I2C_Mem_Read(_hi2c, EEPROM_ID, address, I2C_MEMADD_SIZE_16BIT, data, length, 1000);
}
