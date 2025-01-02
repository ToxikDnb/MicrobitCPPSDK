#ifndef I2C_H
#define I2C_H

/**
 * @file I2C.h
 * @author Mackenzie Blackaby (mackenzie@blackaby.uk)
 * @brief This module contains basic functions for writing and reading from internal and external 
 * I2C devices. This is fairly minimal and designed for advanced users and SDK developers
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// Includes
#include <Microbit/Core/Defs.h>
#include <Microbit/Core/GPIO.h>
#include <nrf.h>

// Macros
#define FREQUENCY TWI_FREQUENCY_FREQUENCY_K400

// Function Prototypes
void initialiseExternalI2C(uint32_t address);
void writeExternalI2C(uint8_t reg, uint8_t data);
uint8_t readExternalI2C(uint8_t reg);
void initialiseInternalI2C(uint32_t address);
void writeInternalI2C(uint8_t reg, uint8_t data);
uint8_t readInternalI2C(uint8_t reg);

#endif