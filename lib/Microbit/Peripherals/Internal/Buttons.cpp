#include <Microbit/Peripherals/Internal/Buttons.h>

// Function to check if button A is pressed
bool getButtonA()
{
    return digitalRead(BUTTONA) != HIGH;
}

// Function to check if button B is pressed
bool getButtonB()
{
    return digitalRead(BUTTONB) != HIGH;
}

// Function to check if a ring is pressed
bool getRing(uint8_t ringNum)
{
    MicrobitPin ringPin;
    switch (ringNum)
    {
    case 0:
        ringPin = GPIO_RING0_PIN;
        break;
    case 1:
        ringPin = GPIO_RING1_PIN;
        break;
    case 2:
        ringPin = GPIO_RING2_PIN;
        break;
    default:
        return false;
    }
    return digitalRead(ringPin) != HIGH;
}
// ####################################################################
