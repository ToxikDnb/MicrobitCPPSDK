#include <Microbit/Core/Maths.h>

/*
Converts an integer to a string, with a given base.
This function is based on the itoa function in the C standard library,
*/
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

/*
Converts an unsigned integer to a string with a given base.
This function is based on the utoa function in the C standard library.
*/
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

/*
Converts a long to a string with a given base.
This function is based on the ltoa function in the C standard library.
*/
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

/*
Converts an unsigned long to a string with a given base.
This function is based on the ultoa function in the C standard library.
*/
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

// Capitalises a character. Returns the character if it is not a lowercase letter
char capitalise(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

// Clamps an integer value between a given min and max
int clamp(int x, int min, int max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

// Maps a given integer value from one range to another
int map(int x, int minIn, int maxIn, int minOut, int maxOut)
{
    return (x - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

// Generates a random number between min (inclusive) and max (inclusive)
int randint(int32_t min, int32_t max)
{
    return rand() % (max - min + 1) + min;
}

/*
Converts a const char array to a char array.
WARNING: This function uses malloc, so remember to free the buffer
*/
char *constToChars(const char *string)
{
    char *buffer = (char *)malloc(strlen(string) + 1);
    strcpy(buffer, string);
    return buffer;
}
