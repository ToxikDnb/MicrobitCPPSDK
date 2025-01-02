#ifndef DELAYS_H
#define DELAYS_H

/**
 * @file Delays.h
 * @author Mackenzie Blackaby (mackenzie@blackaby.uk)
 * @brief This module contains functions to perform delays of multiple different timescales
 * and makes use of the in-built timer hardware
 * @version 0.2
 * @date 2025-01-02
 *
 * @copyright Copyright (c) 2025
 *
 * NOTE: This module is designed to use Timer 3 to perform delays, which will not be used
 * for any other module
 * IF YOU ARE BUILDING YOUR OWN MODULES, DO NOT USE TIMER 3. This will interfere with these delay
 * functions and cause issues. A fix for this issue is planned with a "Timers.h" module, intended for
 * ease of SDK development
 */

// Includes
#include <nrf.h>

// Macros
#define DELAY_TIMER ((NRF_TIMER_Type *)0x4001A000UL) // Nordic Timer 3
#define MAX_SAFE_SECONDS 4294
#define MAX_SAFE_MILLISECONDS 4294967

// Function Prototypes
void delayS(uint32_t s);
void delayM(uint32_t ms);
void delayU(uint32_t us);
extern "C" void TIMER3_IRQHandler();

#endif