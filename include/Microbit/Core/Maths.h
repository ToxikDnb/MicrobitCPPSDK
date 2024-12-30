#ifndef MATHS_H
#define MATHS_H

#include <stdlib.h>
#include <nrf.h>
#include <string.h>

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