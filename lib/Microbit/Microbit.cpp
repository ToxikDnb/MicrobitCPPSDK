#include <Microbit/Microbit.h>

/*
Microbit API for the nRF52 microcontroller
Author: Mackenzie Blackaby

This file contains a multi-platform API for the Microbit
This can be used in platforms such as PlatformIO, or directly by configuring CMake
It contains a bunch of functions, written in low-level C, that can be used to interact with the microbit

This library will conflict with the Arduino library, so it is recommended to use this library in a standalone project
As much as possible, general purpose Arduino functions will be implemented here to make things easy for devs

Please see the Readme or the github markdown for instructions on how to use this API

*/

extern void setup(); // Implement this function in your main file for setup
extern void loop();  // Implement this function in your main file for the main loop

// Main function
int main()
{
    setup();
    while (true)
    {
        loop();
    }
}