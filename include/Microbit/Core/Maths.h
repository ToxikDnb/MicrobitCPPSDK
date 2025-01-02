#ifndef MATHS_H
#define MATHS_H

/**
 * @file Maths.h
 * @author Mackenzie Blackaby (mackenzie@blackaby.uk)
 * @brief This module contains common math or utility functions that are used across multiple
 * modules and are also useful for user development
 * @version 0.1
 * @date 2025-01-02
 *
 * @copyright Copyright (c) 2025
 *
 */

// Includes
#include <stdlib.h>
#include <nrf.h>
#include <string.h>

// Function Prototypes
char *itoa(int value, char *str, int base);
char *utoa(unsigned int value, char *str, int base);
char *ltoa(long value, char *str, int base);
char *ultoa(unsigned long value, char *str, int base);
int randint(int32_t min, int32_t max);
char *constToChars(const char *string);
char capitalise(char c);
int clamp(int x, int min, int max);
int map(int x, int inMin, int inMax, int outMin, int outMax);

#endif