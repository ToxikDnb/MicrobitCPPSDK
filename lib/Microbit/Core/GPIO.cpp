#include <Microbit/Core/GPIO.h>

// Sets the Pin Direction to either INPUT or OUTPUT for the given port and pin
void setPin(MicrobitPin pin, bool output, bool pullup)
{
    NRF_GPIO_Type *port = (pin >= P1_0) ? NRF_P1 : NRF_P0;
    int pinNumber = (pin >= P1_0) ? (pin - P1_0) : pin;

    port->PIN_CNF[pinNumber] = (output ? GPIO_PIN_CNF_DIR_Output : GPIO_PIN_CNF_DIR_Input)
                                   << GPIO_PIN_CNF_DIR_Pos |
                               (pullup ? GPIO_PIN_CNF_PULL_Pullup : GPIO_PIN_CNF_PULL_Disabled)
                                   << GPIO_PIN_CNF_PULL_Pos |
                               (output ? GPIO_PIN_CNF_INPUT_Disconnect : GPIO_PIN_CNF_INPUT_Connect)
                                   << GPIO_PIN_CNF_INPUT_Pos;
}

// Sets the value of the given port and pin to either HIGH or LOW
void digitalWrite(MicrobitPin pin, int value)
{
    NRF_GPIO_Type *port = (pin >= P1_0) ? NRF_P1 : NRF_P0;
    int pinNumber = (pin >= P1_0) ? (pin - P1_0) : pin;

    if (value)
        port->OUT |= (1 << pinNumber);
    else
        port->OUT &= ~(1 << pinNumber);
}

// Reads the value of the given pin
bool digitalRead(MicrobitPin pin)
{
    NRF_GPIO_Type *port = (pin >= P1_0) ? NRF_P1 : NRF_P0;
    int pinNumber = (pin >= P1_0) ? (pin - P1_0) : pin;

    return (port->IN >> pinNumber) & 1;
}