#include <Microbit/I2C.h>

// Initialises the external I2C peripheral at the given address
void initialiseI2C(uint32_t address)
{
    NRF_P0->PIN_CNF[MICROBIT_PIN_EXT_SCL] = 0;
    NRF_P0->PIN_CNF[MICROBIT_PIN_EXT_SDA] = 0;

    NRF_TWI0->PSEL.SDA = MICROBIT_PIN_EXT_SDA;
    NRF_TWI0->PSEL.SCL = MICROBIT_PIN_EXT_SCL;
    NRF_TWI0->ADDRESS = address;
    NRF_TWI0->ENABLE = TWI_ENABLE_ENABLE_Enabled;
}

// Writes a byte to the given register on the I2C device
void writeI2C(uint8_t reg, uint8_t data)
{
    // CleaR Events
    NRF_TWI0->EVENTS_STOPPED = 0;
    NRF_TWI0->EVENTS_TXDSENT = 0;
    NRF_TWI0->EVENTS_ERROR = 0;
    NRF_TWI0->EVENTS_RXDREADY = 0;

    // Write register
    NRF_TWI0->TXD = reg;
    NRF_TWI0->TASKS_STARTTX = 1;
    while (!NRF_TWI0->EVENTS_TXDSENT)
        ;
    // Write data
    NRF_TWI0->EVENTS_TXDSENT = 0;
    NRF_TWI0->TXD = data;
    while (!NRF_TWI0->EVENTS_TXDSENT)
        ;
    // Stop
    NRF_TWI0->EVENTS_TXDSENT = 0;
    NRF_TWI0->TASKS_STOP = 1;
    while (!NRF_TWI0->EVENTS_STOPPED)
        ;
    // Clear events
    NRF_TWI0->EVENTS_STOPPED = 0;
}

// Reads a byte from the given register on the I2C device
uint8_t readTWI(uint8_t reg)
{
    // Clear events
    NRF_TWI0->EVENTS_RXDREADY = 0;
    NRF_TWI0->EVENTS_TXDSENT = 0;
    NRF_TWI0->EVENTS_STOPPED = 0;

    // Write register
    NRF_TWI0->TXD = reg;
    NRF_TWI0->TASKS_STARTTX = 1;
    while (!NRF_TWI0->EVENTS_TXDSENT)
        ;
    // Read data
    NRF_TWI0->EVENTS_TXDSENT = 0;
    NRF_TWI0->TASKS_STARTRX = 1;
    while (!NRF_TWI0->EVENTS_RXDREADY)
        ;
    // Stop
    NRF_TWI0->TASKS_STOP = 1;
    while (!NRF_TWI0->EVENTS_STOPPED)
        ;
    // Clear events
    NRF_TWI0->EVENTS_STOPPED = 0;
    // Return data
    uint8_t data = NRF_TWI0->RXD;
    return data;
}