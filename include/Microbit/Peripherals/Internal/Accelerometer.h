#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Microbit/Core/I2C.h>
#include <Microbit/Core/Maths.h>

#define ACCELEROMETER_MIN -512
#define ACCELEROMETER_MAX 512
#define ACCELEROMETER_ADDRESS 0x19
#define ACCELEROMETER_REG_CTRL_REG1 0x20
#define ACCELEROMETER_REG_OUTPUT_X_L 0x28
#define ACCELEROMETER_MODE_BASIC 0x57

int16_t getAccelerometerDegrees(char axis);
int16_t getAccelerometerRaw(char axis);

#endif