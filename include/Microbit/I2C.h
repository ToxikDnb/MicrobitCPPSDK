#ifndef I2C_H
#define I2C_H

#include <Microbit/Microbit.h>

#define FREQUENCY TWI_FREQUENCY_FREQUENCY_K400

void initialiseI2C(uint32_t address);
void writeI2C(uint8_t reg, uint8_t data);
uint8_t readI2C(uint8_t reg);

#endif