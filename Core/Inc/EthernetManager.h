#ifndef ETHERNETMANAGER_H
#define ETHERNETMANAGER_H
#include "main.h"
#include "CplusUtils.h"
#include <cstdint>
#include <array>
#include "config.h"


extern "C" {
#include "stm32f4xx_hal.h"
#include "dhcp.h"
#include "dns.h"
#include "wizchip_conf.h" // Assuming this is a C library for W5500 Ethernet chip
#include "socket.h" // Include other necessary C headers here
// Include additional C headers as required


extern SPI_HandleTypeDef hspi2;
}
class Utils;

class EthernetManager {
public:
    EthernetManager();
    ~EthernetManager();


    void initialize( Config *conf , Utils *UtilClass );
    bool performPingTest();
    void reconnect();

    bool isIpAssigned();
    void setIPAssiged(bool val);

    Utils* utils;
private:

    static bool ip_assigned;
    void resetAssert();
    void resetDeassert();
    void selectW5500();
    void unselectW5500();
    void readBuffer(uint8_t* buff, uint16_t len);
    void writeBuffer( uint8_t* buff, uint16_t len);
    uint8_t readByte();
    void writeByte(uint8_t byte);
    void callbackIPAssigned();
    void callbackIPConflict();
    void initWIZCHIP();
    void configureNetwork( Config *conf);


    static void W5500_Select();
    static void W5500_Unselect();
    static void W5500_ReadBuff(uint8_t* buff, uint16_t len);
    static void W5500_WriteBuff( uint8_t* buff, uint16_t len);
    static uint8_t W5500_ReadByte();
    static void W5500_WriteByte(uint8_t byte);
    static void Callback_IPAssigned();
    static void Callback_IPConflict();
    // Buffers
    static uint8_t dhcp_buffer[2048];
    static uint8_t dns_buffer[2048];
    static uint8_t DHCP_SOCKET;
    static uint8_t DNS_SOCKET;

    // Add other member variables as needed
};



#define W5x00_RESET_PIN     W5500_RESET_Pin
#define W5x00_RESET_PORT   GPIOC

#endif // ETHERNETMANAGER_H
