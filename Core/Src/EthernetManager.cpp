
#include "EthernetManager.h"

#include <cstring>



// Assuming extern declaration of hspi2, W5500_CS_GPIO_Port, and W5x00_RESET_PORT are done correctly elsewhere
extern SPI_HandleTypeDef hspi2;

// Static buffer definitions
uint8_t EthernetManager::dhcp_buffer[2048];
uint8_t EthernetManager::dns_buffer[2048];
uint8_t EthernetManager::DHCP_SOCKET = 1;
uint8_t EthernetManager::DNS_SOCKET = 1;

EthernetManager* EthernetManager::instance = nullptr;

EthernetManager::~EthernetManager() {

}

EthernetManager::EthernetManager() {
	instance = this;
}

void EthernetManager::init( Config *conf, Utils *utilClass) {
    utils = utilClass;
    config = conf;
    utils->playSound();
    utils->print("Initializing Internet \r\n");

}

bool EthernetManager::connect() {

    resetAssert();
    HAL_Delay(100); // Delay for the reset
    resetDeassert();
    HAL_Delay(300);
    if (!initWIZCHIP()) {
    	return false;
    }

    if (! configureNetwork()) {
    	return false;
    }

     return true;

}

bool EthernetManager::performPingTest() {

    return false;
}

void EthernetManager::reconnect() {
    resetAssert();
    HAL_Delay(100);
    resetDeassert();

    initWIZCHIP();

}



void EthernetManager::resetAssert() {

    HAL_GPIO_WritePin(W5x00_RESET_PORT, W5x00_RESET_PIN, GPIO_PIN_RESET);
}

void EthernetManager::resetDeassert() {

    HAL_GPIO_WritePin(W5x00_RESET_PORT, W5x00_RESET_PIN, GPIO_PIN_SET);
}


void EthernetManager::W5500_Select() {
	HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_RESET);
}


void EthernetManager::W5500_Unselect() {
	 HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_SET);
}


void EthernetManager::W5500_ReadBuff(uint8_t* buff, uint16_t len) {
    HAL_SPI_Receive(&hspi2, buff, len, HAL_MAX_DELAY);
}

void EthernetManager::W5500_WriteBuff( uint8_t* buff, uint16_t len) {
    HAL_SPI_Transmit(&hspi2, buff, len, HAL_MAX_DELAY);
}

uint8_t EthernetManager::W5500_ReadByte() {
    uint8_t byte;
    W5500_ReadBuff(&byte, 1);
    return byte;
}

void EthernetManager::W5500_WriteByte(uint8_t byte) {
	W5500_WriteBuff(&byte, 1);
}

void EthernetManager::Callback_IPAssigned() {
    	if (instance) {
    		instance->config->setIpAssigned(true);
    	}
}

void EthernetManager::Callback_IPConflict() {
}


bool EthernetManager::initWIZCHIP() {
    utils->print("\r\nWIZCHIP Initialization called!\r\n");
    W5500_Unselect();
    reg_wizchip_cs_cbfunc(W5500_Select, W5500_Unselect);
    reg_wizchip_spi_cbfunc(W5500_ReadByte, W5500_WriteByte);
    reg_wizchip_spiburst_cbfunc(W5500_ReadBuff, W5500_WriteBuff);

    uint8_t memsize[2][8] = {{2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2}};
    if (ctlwizchip(CW_INIT_WIZCHIP, (void*)memsize) == -1) {
        return false;
    }
    uint8_t tmp;
    uint8_t attempt = 0;
    do {
        if (ctlwizchip(CW_GET_PHYLINK, (void*)&tmp) == -1) {
         //  Print("UNKNOWN PHY LINK STATUS.\r\n");
        	return false;

        }
    }  while (tmp == PHY_LINK_OFF );

    if (tmp == PHY_LINK_OFF ) return false;
    else return true;
    utils->print("WIZCHIP Initialized successfully.\r\n");
}


bool EthernetManager::configureNetwork() {
	utils->print("Initializing Netwok Configuration!!! \r\n");
       uint8_t mac[6];
       getSHAR(mac); // Assuming you have a function getSHAR to get MAC address
       HAL_Delay(300);

       wiz_NetInfo net_info = {
           {mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]}, // MAC address
           {0,}, // IP address (will be set by DHCP or static config)
           {0,}, // Gateway (will be set by DHCP or static config)
           {0,}, // Subnet Mask (will be set by DHCP or static config)
           {0,}, // DNS server (will be set by DHCP or static config)
           NETINFO_DHCP // Default to DHCP
       };

       setSHAR(net_info.mac); // Apply MAC address

       utils->print("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

       if (config->getDHCPEnabled()) {
           // DHCP mode
    	   utils->print("DHCP mode has been enabled@ \r\n");
           DHCP_init(DHCP_SOCKET, dhcp_buffer);
           reg_dhcp_cbfunc(Callback_IPAssigned, Callback_IPAssigned, Callback_IPConflict);

           uint8_t attempt = 0;
           utils->print("Attempting DHCP lease...\r\n");
           while (!config->getIpAssigned()) {

        	   DHCP_run();
        	   HAL_Delay(100);
        	   attempt ++;
        	   if(attempt == 10) break;

           }
           if (!config->getIpAssigned()) return false;
           // Get network configuration from DHCP
           getIPfromDHCP(net_info.ip);
           getGWfromDHCP(net_info.gw);
           getSNfromDHCP(net_info.sn);
           getDNSfromDHCP(net_info.dns);

           config->setDHCPNetworkConfig(&net_info);
       } else {
    	   utils->print("STATIC mode has been enabled@ \r\n");
           // Static IP mode
    	   std::memcpy(net_info.ip, config->getIP().data(), 4); // For std::array
    	   std::memcpy(net_info.gw, config->getGateway().data(), 4); // For std::array
    	   std::memcpy(net_info.sn, config->getSubnet().data(), 4); // For std::array
    	   std::memcpy(net_info.dns, config->getDNS().data(), 4); // For std::array
           net_info.dhcp = NETINFO_STATIC;
       }
       // Apply network settings to WIZnet chip
       wizchip_setnetinfo(&net_info);

       // Print network information
       utils->print("IP: %d.%d.%d.%d\r\nGW: %d.%d.%d.%d\r\nNet: %d.%d.%d.%d\r\nDNS: %d.%d.%d.%d\r\n",
                   net_info.ip[0], net_info.ip[1], net_info.ip[2], net_info.ip[3],
                   net_info.gw[0], net_info.gw[1], net_info.gw[2], net_info.gw[3],
                   net_info.sn[0], net_info.sn[1], net_info.sn[2], net_info.sn[3],
                   net_info.dns[0], net_info.dns[1], net_info.dns[2], net_info.dns[3]);

       // Initializing DNS if necessary
       DNS_init(DNS_SOCKET, dns_buffer);

       return true;
}
