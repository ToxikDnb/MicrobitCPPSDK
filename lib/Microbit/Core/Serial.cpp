#include <Microbit/Core/Serial.h>

bool isSerialInitialised = false;

// Internal function to initialise the serial
void initialiseSerial()
{
    setPin(MICROBIT_PIN_TX, true, false);
    setPin(MICROBIT_PIN_RX, false, false);

    NRF_UART0->PSEL.TXD = MICROBIT_PIN_TX;
    NRF_UART0->PSEL.RXD = MICROBIT_PIN_RX;
    NRF_UART0->BAUDRATE = SERIAL_SPEED;
    NRF_UART0->CONFIG = (UART_CONFIG_HWFC_Disabled << UART_CONFIG_HWFC_Pos) |
                        (UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos);
    NRF_UART0->ENABLE = UART_ENABLE_ENABLE_Enabled;

    NRF_UART0->TASKS_STARTTX = 1;
    NRF_UART0->TASKS_STARTRX = 1;

    isSerialInitialised = true;
}

// Printing

// Serial print a single character
void serialPrint(char c)
{
    if (!isSerialInitialised)
        initialiseSerial();
    NRF_UART0->TXD = c;
    while (NRF_UART0->EVENTS_TXDRDY != 1)
        ;
    NRF_UART0->EVENTS_TXDRDY = 0;
}

// Serial print a string
void serialPrint(char *string)
{
    while (*string)
    {
        serialPrint(*string++);
    }
}

// Same function but for a constant string
void serialPrint(const char *string)
{
    char *buffer = constToChars(string);
    serialPrint(buffer);
    free(buffer);
}

// Same function but for an integer
void serialPrint(int x)
{
    char buffer[32];
    itoa(x, buffer, 10);
    serialPrint(buffer);
}
