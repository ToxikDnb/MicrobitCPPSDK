#ifndef MATRIX_DISPLAY_H
#define MATRIX_DISPLAY_H

#include <Microbit/Core/GPIO.h>
#include <Microbit/Core/Serial.h>
#include <Microbit/Core/Defs.h>
#include <Microbit/Core/Delays.h>
#include <stdlib.h>

// MACROS
#define DISPLAY_WIDTH 5
#define DISPLAY_HEIGHT 5
#define SERIAL_SPEED UART_BAUDRATE_BAUDRATE_Baud115200
#define REFRESH_RATE 60
#define REFRESH_INTERVAL_MS 1000 / REFRESH_RATE
#define REFRESH_INTERVAL_US 1000000 / REFRESH_RATE
#define MICROBIT_DISPLAY_TIMER ((NRF_TIMER_Type *)0x4000A000UL) // Timer 2

// typedefs
typedef struct
{
    MicrobitPin col1 = P0_28;
    MicrobitPin col2 = P0_11;
    MicrobitPin col3 = P0_31;
    MicrobitPin col4 = P1_5;
    MicrobitPin col5 = P0_30;

    MicrobitPin row1 = P0_21;
    MicrobitPin row2 = P0_22;
    MicrobitPin row3 = P0_15;
    MicrobitPin row4 = P0_24;
    MicrobitPin row5 = P0_19;

    MicrobitPin pins[10] = {col1, col2, col3, col4, col5, row1, row2, row3, row4, row5};

} MicrobitMatrixPins;

// Custom data types
typedef uint8_t MicrobitDisplay[DISPLAY_HEIGHT][DISPLAY_WIDTH];
typedef uint8_t MicrobitImage[DISPLAY_HEIGHT][DISPLAY_WIDTH];

// Linked list for buffer for microbit display
typedef struct bufferNode
{
    MicrobitImage *image;
    int usToDisplay;
    struct bufferNode *next;
} bufferNode;

typedef struct buffer
{
    bufferNode *head;
} buffer;

// Function Prototypes
void initialiseDisplay();
void clearDisplay();
void pushImageToBuffer(MicrobitImage *image, int msToDisplay);
void displayImage(MicrobitImage *image);
void setPixel(int x, int y, int value);

// Serial functionss
void serialPrintImage(MicrobitImage *image);

#endif