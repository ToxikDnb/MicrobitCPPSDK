#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

/**
 * @file Accelerometer.h
 * @author Mackenzie Blackaby (mackenzie@blackaby.uk)
 * @brief Provides a series of functions to access the internal accelerometer on the Microbit
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// Includes
#include <Microbit/Core/I2C.h>
#include <Microbit/Core/Maths.h>

// Macros
#define ACCELEROMETER_MIN -512
#define ACCELEROMETER_MAX 512
#define ACCELEROMETER_ADDRESS 0x19
#define ACCELEROMETER_REG_CTRL_REG1 0x20
#define ACCELEROMETER_REG_OUTPUT_X_L 0x28
#define ACCELEROMETER_MODE_BASIC 0x57

// Function Prototypes
int16_t getAccelerometerDegrees(char axis);
int16_t getAccelerometerRaw(char axis);

#endif