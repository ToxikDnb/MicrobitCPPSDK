#include <Microbit/Peripherals/Internal/Accelerometer.h>

bool isAccelerometerInitialised = false;

void initialiseAccelerometer()
{
    if (isAccelerometerInitialised)
        return;
    isAccelerometerInitialised = true;
    initialiseInternalI2C(ACCELEROMETER_ADDRESS);
    writeInternalI2C(ACCELEROMETER_REG_CTRL_REG1, ACCELEROMETER_MODE_BASIC);
}

// Function to get the accelerometer reading in raw values
int16_t getAccelerometerRaw(char axis)
{
    initialiseAccelerometer();
    axis = capitalise(axis);
    if (axis != 'X' && axis != 'Y' && axis != 'Z')
        return 0;
    // calculate and read registers
    uint8_t reg_low = ACCELEROMETER_REG_OUTPUT_X_L + (2 * (axis - 'X')), reg_high = reg_low + 1;
    uint8_t low = readInternalI2C(reg_low);
    uint8_t high = readInternalI2C(reg_high);
    int16_t value = (high << 8) | low;

    // Bit shift due to 10-bit resolution and 2's complement
    value = value >> 5;

    // If value is greater than 512, subtract 1024 due to 2's complement
    if (value > 512)
        value -= 1024;

    return value;
}

// Function to get the accelerometer reading in degrees
int16_t getAccelerometerDegrees(char axis)
{
    int16_t reading = getAccelerometerRaw(axis);
    reading = clamp(reading, ACCELEROMETER_MIN, ACCELEROMETER_MAX);
    return map(reading, ACCELEROMETER_MIN, ACCELEROMETER_MAX, 0, 360);
}