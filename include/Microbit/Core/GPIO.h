#ifndef GPIO_H
#define GPIO_H

#include <nrf.h>

// Pin typedef enum
typedef enum
{
    p0 = 0,
    p1 = 1,
    p2 = 2,
    p3 = 3,
    p4 = 4,
    p5 = 5,
    p6 = 6,
    p7 = 7,
    p8 = 8,
    p9 = 9,
    p10 = 10,
    p11 = 11,
    p12 = 12,
    p13 = 13,
    p14 = 14,
    p15 = 15,
    p16 = 16,
    p17 = 17,
    p18 = 18,
    p19 = 19,
    p20 = 20,
    p21 = 21,
    p22 = 22,
    p23 = 23,
    p24 = 24,
    p25 = 25,
    p26 = 26,
    p27 = 27,
    p28 = 28,
    p29 = 29,
    p30 = 30,
    p31 = 31,
    p32 = 32,
    p33 = 33,
    p34 = 34,
    p35 = 35,
    p36 = 36,
    p37 = 37,
    p38 = 38,
    p39 = 39,
    p40 = 40,
    p41 = 41,
    p42 = 42,
    p43 = 43,
    p44 = 44,
    p45 = 45,
    p46 = 46,
    p47 = 47,

    P0_0 = p0,
    P0_1 = p1,
    P0_2 = p2,
    P0_3 = p3,
    P0_4 = p4,
    P0_5 = p5,
    P0_6 = p6,
    P0_7 = p7,

    P0_8 = p8,
    P0_9 = p9,
    P0_10 = p10,
    P0_11 = p11,
    P0_12 = p12,
    P0_13 = p13,
    P0_14 = p14,
    P0_15 = p15,

    P0_16 = p16,
    P0_17 = p17,
    P0_18 = p18,
    P0_19 = p19,
    P0_20 = p20,
    P0_21 = p21,
    P0_22 = p22,
    P0_23 = p23,

    P0_24 = p24,
    P0_25 = p25,
    P0_26 = p26,
    P0_27 = p27,
    P0_28 = p28,
    P0_29 = p29,
    P0_30 = p30,
    P0_31 = p31,

    P1_0 = p32,
    P1_1 = p33,
    P1_2 = p34,
    P1_3 = p35,
    P1_4 = p36,
    P1_5 = p37,
    P1_6 = p38,
    P1_7 = p39,

    P1_8 = p40,
    P1_9 = p41,
    P1_10 = p42,
    P1_11 = p43,
    P1_12 = p44,
    P1_13 = p45,
    P1_14 = p46,
    P1_15 = p47,

    // IDENTITY MAPPINGS
    P0_00 = P0_0,
    P0_01 = P0_1,
    P0_02 = P0_2,
    P0_03 = P0_3,
    P0_04 = P0_4,
    P0_05 = P0_5,
    P0_06 = P0_6,
    P0_07 = P0_7,
    P0_08 = P0_8,
    P0_09 = P0_9,
    P1_00 = P1_0,
    P1_01 = P1_1,
    P1_02 = P1_2,
    P1_03 = P1_3,
    P1_04 = P1_4,
    P1_05 = P1_5,
    P1_06 = P1_6,
    P1_07 = P1_7,
    P1_08 = P1_8,
    P1_09 = P1_9,

    // Buttons A and B
    BUTTONA = P0_14,
    BUTTONB = P0_23,

    // LED matrix
    ROW_1 = P0_21,
    ROW_2 = P0_22,
    ROW_3 = P0_15,
    ROW_4 = P0_24,
    ROW_5 = P0_19,
    COL_1 = P0_28,
    COL_2 = P0_11,
    COL_3 = P0_31,
    COL_4 = P1_5,
    COL_5 = P0_30,

    USB_UART_RX = p8,
    USB_UART_TX = p6,

    SPI_PSELMOSI0 = P1_13,
    SPI_PSELMISO0 = P1_14,
    SPI_PSELSS0 = P1_12,
    SPI_PSELSCK0 = P1_15,

    SPI_PSELMOSI1 = P1_2,
    SPI_PSELMISO1 = P1_3,
    SPI_PSELSS1 = P1_1,
    SPI_PSELSCK1 = P1_4,

    SPIS_PSELMOSI = P1_2,
    SPIS_PSELMISO = P1_3,
    SPIS_PSELSS = P1_1,
    SPIS_PSELSCK = P1_4,

    I2C_SDA0 = p26,
    I2C_SCL0 = p27,

    /**** QSPI pins ****/
    QSPI1_IO0 = P0_20,
    QSPI1_IO1 = P0_21,
    QSPI1_IO2 = P0_22,
    QSPI1_IO3 = P0_23,
    QSPI1_SCK = P0_19,
    QSPI1_CSN = P0_17,

    /**** QSPI FLASH pins ****/
    QSPI_FLASH1_IO0 = QSPI1_IO0,
    QSPI_FLASH1_IO1 = QSPI1_IO1,
    QSPI_FLASH1_IO2 = QSPI1_IO2,
    QSPI_FLASH1_IO3 = QSPI1_IO3,
    QSPI_FLASH1_SCK = QSPI1_SCK,
    QSPI_FLASH1_CSN = QSPI1_CSN,

    // Not connected
    NC = (int)0xFFFFFFFF
} MicrobitPin;

// MACROS
#define GPIO_MIC_PIN P0_20
#define GPIO_RING0_PIN P0_02
#define GPIO_RING1_PIN P0_03
#define GPIO_RING2_PIN P0_04
#define MICROBIT_PIN_INT_SCL P0_08
#define MICROBIT_PIN_INT_SDA P0_16
#define MICROBIT_PIN_EXT_SCL P0_26
#define MICROBIT_PIN_EXT_SDA P1_01
#define MICROBIT_PIN_TX P0_06
#define MICROBIT_PIN_RX P1_08

// Function Prototypes
void setPin(MicrobitPin pin, bool output, bool pullup);
void digitalWrite(MicrobitPin pin, int value);
bool digitalRead(MicrobitPin pin);

#endif