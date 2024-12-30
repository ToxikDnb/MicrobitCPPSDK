#include <Microbit/Core/Maths.h>

// Helper functions for number to string conversion
char *itoa(int value, char *str, int base)
{
    if (base < 2 || base > 36)
    {
        *str = '\0';
        return str;
    }
    char *rc = str;
    char *ptr = str;
    char *low;
    if (value < 0 && base == 10)
    {
        *ptr++ = '-';
    }
    low = ptr;
    do
    {
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[abs(value % base)];
        value /= base;
    } while (value);
    *ptr-- = '\0';
    while (low < ptr)
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

char *utoa(unsigned int value, char *str, int base)
{
    if (base < 2 || base > 36)
    {
        *str = '\0';
        return str;
    }
    char *rc = str;
    char *ptr = str;
    char *low;
    low = ptr;
    do
    {
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base];
        value /= base;
    } while (value);
    *ptr-- = '\0';
    while (low < ptr)
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

char *ltoa(long value, char *str, int base)
{
    if (base < 2 || base > 36)
    {
        *str = '\0';
        return str;
    }
    char *rc = str;
    char *ptr = str;
    char *low;
    if (value < 0 && base == 10)
    {
        *ptr++ = '-';
    }
    low = ptr;
    do
    {
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[labs(value % base)];
        value /= base;
    } while (value);
    *ptr-- = '\0';
    while (low < ptr)
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

char *ultoa(unsigned long value, char *str, int base)
{
    if (base < 2 || base > 36)
    {
        *str = '\0';
        return str;
    }
    char *rc = str;
    char *ptr = str;
    char *low;
    low = ptr;
    do
    {
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base];
        value /= base;
    } while (value);
    *ptr-- = '\0';
    while (low < ptr)
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

// Capitalises a character
char capitalise(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

// Clamps a value between a min and max
int clamp(int x, int min, int max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

// Maps a value from one range to another
int map(int x, int minIn, int maxIn, int minOut, int maxOut)
{
    return (x - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

// Generates a random number between min (inclusive) and max (inclusive)
int randint(int32_t min, int32_t max)
{
    return rand() % (max - min + 1) + min;
}

// Converts a const char array to a char array. WARNING: This function uses malloc, so remember to free the buffer
char *constToChars(const char *string)
{
    char *buffer = (char *)malloc(strlen(string) + 1);
    strcpy(buffer, string);
    return buffer;
}
