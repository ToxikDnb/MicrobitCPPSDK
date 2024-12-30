# MicroBit C++ SDK

## Introduction

This C++ SDK is designed specifically with the BBC MicroBit in mind. It acts as an alternative to both the Arduino development package, which is not designed with the BBC MicroBit in mind rather as a highly functional general-purpose microcontroller development kit, and the Lancaster University SDK which, while having laser focus on the MicroBit, is not as user-friendly or intuitive as the Arduino package, and is not as compatible with development styles either.

## Features

Implemented/Implementing:

- GPIO Control
- Display Management
- Timing Functions
- Input Handling
- Communication
- Display Abstraction
- Sprite System
- Input System

Planned:

- Animation System
- Game State Management
- Sensor Integration
- Sound System

## Installation

### Prerequisites

The following libraries are needed for each file:

#### Microbit.h

- C++ standard library
- `nrf.h`: Nordic Semiconductor nRF5 SDK.

### Steps

#### Installation for PlatformIO

1. Create a new project for the "BBC Microbit V2.2" with the framework "Arduino"
2. Decompress the release files
3. Copy the contents of the "lib" folder into the "lib" in your PlatformIO project
4. Repeat the same for the "include" folder
5. Delete the following from your main.cpp file: `#include <"Arduino.h">`
6. Include the core library `<"Microbit.h">` instead
7. Good luck! :)

## Usage

### Basic Example

Here is a simple example of programming a screen wipe to display the functionality of the SDK

```cpp
#include <Microbit/Microbit.h>

#define ANIMATION_RATE 150
#define ANIMATION_INTERVAL_US 1000000 / ANIMATION_RATE

bool isWipeHorizontal = true; // if true, i represents columns and j represents rows; vice versa
bool isDown = true;           // if true, screen wipes positively, otherwise wipes negatively
uint8_t counter = 0;          // Counts for 4 iterations of the loop
uint8_t counterMax = 8;       // Maximum for counter
uint8_t animationStates = 4;
uint8_t isOn = HIGH;            // if true, turn on the pixel; vice versa
uint16_t currentOuterDimension; // Current dimension to scroll
uint16_t currentInnerDimension; // Current dimension to toggle

// Initialise the display
void setup()
{
    initialiseDisplay();
}

// Main loop
void loop()
{
    // Play and calculate the animation
    currentOuterDimension = isWipeHorizontal ? DISPLAY_WIDTH : DISPLAY_HEIGHT;
    for (int i = isDown ? 0 : currentOuterDimension - 1; (isDown ? (i < currentOuterDimension) : (i >= 0)); i += isDown ? 1 : -1)
    {
        currentInnerDimension = isWipeHorizontal ? DISPLAY_HEIGHT : DISPLAY_WIDTH;
        for (int j = isDown ? 0 : currentInnerDimension - 1; (isDown ? (j < currentInnerDimension) : (j >= 0)); j += isDown ? 1 : -1)
        {
            setPixel(isWipeHorizontal ? i : j, isWipeHorizontal ? j : i, isOn);
            delayU(ANIMATION_INTERVAL_US);
        }
    }
    counter++;
    // Handle on/off of LEDs
    isOn = !isOn;
    // Handle direction
    if (counter % (counterMax / 4) == 0)
        isWipeHorizontal = !isWipeHorizontal;
    // Handle counting the other way
    if (counter % (counterMax / 2) == 0)
        isDown = !isDown;
    if (counter >= counterMax)
        counter = 0;
}
```

### Advanced Examples

Please find the "Examples" folder which contains a variety of example projects, displaying the functionality of the SDK

The current example projects available are:

- Nom Nom

#### Nom Nom

This game is a simple game where the player has to eat the food particles that appears on the screen
The player controls their character via the integrated accelerometer
Once the player has eaten a piece of food, the food will disappear and reappear in a new location
After eating ten pieces of food, the player wins and a victory screen is displayed!
This game only uses 236 bytes of RAM and 3.4KB of rom, designed to show how both lightweight, readable and powerful the base SDK is

## API Reference

### Microbit.h

- Contains the basic functionality of the MicroBit, allowing for interaction with all of its internal peripherals and functions

### UGame.h

- Contains the game development engine and support for custom IO systems.

### I2C.h

- Contains logic for communicating over I2C

## License

This SDK is under an MIT licence. Full licence details can be found in the LICENCE file

## Contact

For questions or contact, please email [mackenzieblackaby@outlook.com](mailto:mackenzieblackaby@outlook.com), or [mackenzie@blackaby.uk](mailto:mackenzie@blackaby.uk)
