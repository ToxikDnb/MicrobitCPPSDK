#ifndef SERIAL_H
#define SERIAL_H

/**
 * @file Serial.h
 * @author Mackenzie Blackaby (mackenzie@blackaby.uk)
 * @brief This module contains functions for USB serial communication. Currently only output, Input is coming soon :)
 * @version 0.1
 * @date 2025-01-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <Microbit/Core/GPIO.h>
#include <Microbit/Core/Maths.h>

#define SERIAL_SPEED UART_BAUDRATE_BAUDRATE_Baud115200

// Serial print functions
void serialPrint(char c);
void serialPrint(char *string);
void serialPrint(const char *string);
void serialPrint(int x);

#endif