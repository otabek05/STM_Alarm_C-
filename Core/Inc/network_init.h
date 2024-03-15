/*
 * network_init.h
 *
 *  Created on: Mar 5, 2024
 *      Author: user
 */

#ifndef SRC_NETWORK_INIT_H_
#define SRC_NETWORK_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

// Include C libraries within extern "C" for C++ compatibility
#include "wizchip_conf.h" // C library
#include <stdbool.h> // C standard library, compatible with C++

#ifdef __cplusplus
} // end extern "C"
#endif

// Include C++ compatible headers outside extern "C"
#include "main.h"

#define DHCP_SOCKET     1
#define DNS_SOCKET      1
#define USE_DHCP 1 // 1 for DHCP, 0 for STATIC



#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // end extern "C"
#endif

#endif /* SRC_NETWORK_INIT_H_ */
