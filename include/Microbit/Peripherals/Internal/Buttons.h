#ifndef BUTTONS_H
#define BUTTONS_H

/**
 * @file Buttons.h
 * @author Mackenzie Blackaby
 * @brief Provides functionality to access the in-built buttons and touch-capacitive rings on the Microbit
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// Includes
#include <Microbit/Core/GPIO.h>
#include <Microbit/Core/Defs.h>

// Function Prototypes
bool getButtonA();
bool getButtonB();
bool getRing(uint8_t ringNum);

#endif