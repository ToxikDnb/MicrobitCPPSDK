#ifndef SERIAL_H
#define SERIAL_H

#include <Microbit/Core/GPIO.h>
#include <Microbit/Core/Maths.h>

#define SERIAL_SPEED UART_BAUDRATE_BAUDRATE_Baud115200

// Serial print functions
void serialPrint(char c);
void serialPrint(char *string);
void serialPrint(const char *string);
void serialPrint(int x);

#endif