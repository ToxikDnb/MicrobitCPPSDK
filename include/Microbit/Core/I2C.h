#ifndef I2C_H
#define I2C_H

#include <Microbit/Core/Defs.h>
#include <Microbit/Core/GPIO.h>
#include <nrf.h>

#define FREQUENCY TWI_FREQUENCY_FREQUENCY_K400

void initialiseExternalI2C(uint32_t address);
void writeExternalI2C(uint8_t reg, uint8_t data);
uint8_t readExternalI2C(uint8_t reg);
void initialiseInternalI2C(uint32_t address);
void writeInternalI2C(uint8_t reg, uint8_t data);
uint8_t readInternalI2C(uint8_t reg);

#endif