#include <Microbit/Microbit.h>
#include <stdlib.h>
#include <nrf.h>

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

// Variables
// ####################################################################
// Constant variables or external volatile variables
MicrobitDisplay display = {{0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0}};
const MicrobitMatrixPins MICROBIT_PINS;
volatile uint32_t *GPIO_0 = (uint32_t *)0x50000000;
volatile uint32_t *GPIO_1 = (uint32_t *)0x50000300;

// Linked lists setup.
// Display
buffer displayBuffer = {0};

// Delays
volatile delayBuffer dBuffer = {0};
volatile bool isDelay = false;
// ####################################################################

// UTILITY FUNCTIONS
// ####################################################################

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

// Generates a random number between min and max
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

// Adds a delay to the delay buffer
void addDelayToBuffer(uint32_t us)
{
    delayNode *newNode = (delayNode *)malloc(sizeof(delayNode));
    newNode->usToDelay = us;
    newNode->next = NULL;

    if (dBuffer.head == NULL)
    {
        dBuffer.head = newNode;
    }
    else
    {
        delayNode *current = dBuffer.head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Pops a delay from the delay buffer
uint32_t getDelayFromBuffer()
{
    if (dBuffer.head == NULL)
    {
        return 0;
    }
    delayNode *temp = dBuffer.head;
    dBuffer.head = dBuffer.head->next;
    uint32_t delay = temp->usToDelay;
    free(temp);
    return delay;
}

// Pushes an image to the display buffer
void pushImageToBuffer(MicrobitImage *image, int msToDisplay)
{
    bufferNode *newNode = (bufferNode *)malloc(sizeof(bufferNode));
    newNode->image = image;
    newNode->usToDisplay = msToDisplay * 1000;
    newNode->next = NULL;

    if (displayBuffer.head == NULL)
    {
        displayBuffer.head = newNode;
    }
    else
    {
        bufferNode *current = displayBuffer.head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Removes the head of the display buffer and displays the image
bufferNode *popImageFromBuffer()
{
    if (displayBuffer.head == NULL)
    {
        return NULL;
    }
    bufferNode *temp = displayBuffer.head;
    displayBuffer.head = displayBuffer.head->next;
    return temp;
}
// ####################################################################

// DELAYS
// ####################################################################
// Delay function in seconds
void delayS(uint32_t s)
{
    delayU(s * 1000000);
}

// Delay function in milliseconds
void delayM(uint32_t ms)
{
    delayU(ms * 1000);
}

// Timer interrupt handler
extern "C" void TIMER3_IRQHandler()
{
    if (DELAY_TIMER->EVENTS_COMPARE[0] != 0)
    {
        DELAY_TIMER->EVENTS_COMPARE[0] = 0;
        DELAY_TIMER->TASKS_STOP = 1;
        DELAY_TIMER->EVENTS_COMPARE[0] = 0;
        isDelay = false;
    }
}

// Delay function in microseconds
void delayU(uint32_t us)
{
    // Add current timer delay and position to buffer
    if (DELAY_TIMER->TASKS_START == 1)
    {
        addDelayToBuffer(DELAY_TIMER->CC[0]);
        DELAY_TIMER->TASKS_STOP = 1;
    }
    // Configure timer
    DELAY_TIMER->BITMODE = TIMER_BITMODE_BITMODE_32Bit;
    DELAY_TIMER->PRESCALER = 4;
    DELAY_TIMER->TASKS_CLEAR = 1;
    // Set compare register
    DELAY_TIMER->CC[0] = us;
    // Enable and configure interrupts
    DELAY_TIMER->INTENSET = TIMER_INTENSET_COMPARE0_Msk;
    NVIC_DisableIRQ(TIMER3_IRQn);
    NVIC_ClearPendingIRQ(TIMER3_IRQn);
    NVIC_SetPriority(TIMER3_IRQn, 3);
    NVIC_EnableIRQ(TIMER3_IRQn);
    // Start timer
    isDelay = true;
    DELAY_TIMER->TASKS_START = 1;
    while (isDelay)
        ;
    // Get next delay from buffer
    uint32_t nextDelay = getDelayFromBuffer();
    if (nextDelay != 0)
    {
        delayU(nextDelay);
    }
}
// ####################################################################

// GPIO PIN FUNCTIONS
// ####################################################################
// Sets the Pin Direction to either INPUT or OUTPUT for the given port and pin
void setPin(MicrobitPin pin, bool output, bool pullup)
{
    NRF_GPIO_Type *port = (pin >= P1_0) ? NRF_P1 : NRF_P0;
    int pinNumber = (pin >= P1_0) ? (pin - P1_0) : pin;

    port->PIN_CNF[pinNumber] = (output ? GPIO_PIN_CNF_DIR_Output : GPIO_PIN_CNF_DIR_Input)
                                   << GPIO_PIN_CNF_DIR_Pos |
                               (pullup ? GPIO_PIN_CNF_PULL_Pullup : GPIO_PIN_CNF_PULL_Disabled)
                                   << GPIO_PIN_CNF_PULL_Pos |
                               (output ? GPIO_PIN_CNF_INPUT_Disconnect : GPIO_PIN_CNF_INPUT_Connect)
                                   << GPIO_PIN_CNF_INPUT_Pos;
}

// Sets the value of the given port and pin to either HIGH or LOW

void digitalWrite(MicrobitPin pin, int value)
{
    NRF_GPIO_Type *port = (pin >= P1_0) ? NRF_P1 : NRF_P0;
    int pinNumber = (pin >= P1_0) ? (pin - P1_0) : pin;

    if (value)
        port->OUT |= (1 << pinNumber);
    else
        port->OUT &= ~(1 << pinNumber);
}
// ####################################################################

// SERIAL FUNCTIONS
// ####################################################################
// Print to serial
void serialPrint(char *string)
{
    setPin(TX_PIN, true, false);
    while (*string != '\0')
    {
        char current = *string++;
        // Start bit
        digitalWrite(TX_PIN, 0);
        delayU(SERIAL_INTERVAL);

        // Data bits (8 bits, LSB first)
        for (int i = 0; i < 8; i++)
        {
            digitalWrite(TX_PIN, current & 1);
            current >>= 1;
            delayU(SERIAL_INTERVAL);
        }

        // Stop bit
        digitalWrite(TX_PIN, 1);
        delayU(SERIAL_INTERVAL);
    }
}

// Same function but for a constant string
void serialPrint(const char *string)
{
    char *buffer = constToChars(string);
    serialPrint(buffer);
    free(buffer);
}

// Same function but for an integer
void serialPrint(int x)
{
    char buffer[32];
    itoa(x, buffer, 10);
    serialPrint(buffer);
}

// Print a microbitimage to the screen
void serialPrintImage(MicrobitImage *image)
{
    serialPrint("{\n");
    char buffer[2];
    for (int i = 0; i < DISPLAY_HEIGHT; i++)
    {
        serialPrint("\t");
        for (int j = 0; j < DISPLAY_WIDTH; j++)
        {
            uint8_t pixel = (*image)[i][j];
            itoa(pixel, buffer, 2);
            serialPrint(buffer);
        }
        serialPrint("\n");
    }
    serialPrint("}\n");
}
// ####################################################################

// MICROBIT 5x5 MATRIX DISPLAY FUNCTIONS
// ####################################################################
// Function to display a string on the microbit
void displayRefresh()
{
    if (displayBuffer.head != NULL)
    {
        bufferNode *currentNode = popImageFromBuffer();
        displayImage(currentNode->image);
        free(currentNode);
    }
    for (int row = 0; row < DISPLAY_HEIGHT; row++)
    {
        // Set all column pins to HIGH to prevent ghosting
        for (int col = 0; col < DISPLAY_WIDTH; col++)
        {
            digitalWrite(MICROBIT_PINS.pins[col], HIGH);
        }

        // Set the current row pin to high
        digitalWrite(MICROBIT_PINS.pins[row + DISPLAY_WIDTH],
                     HIGH);

        // Scan through available cols
        for (int col = 0; col < DISPLAY_WIDTH; col++)
        {
            // Get the pixel value
            int value = display[row][col] == 1 ? LOW : HIGH;
            // Set the col pin to the pixel value
            digitalWrite(MICROBIT_PINS.pins[col],
                         value);
        }

        // Delay a small amount to allow changes to display
        delayM(1);
        // Set the current row pin back to low
        digitalWrite(MICROBIT_PINS.pins[row + DISPLAY_WIDTH],
                     LOW);
    }
}

// Interrupt handler for the display refresh timer
void displayRefreshInterruptHandler()
{
    // If timer0 is completed
    if (MICROBIT_DISPLAY_TIMER->EVENTS_COMPARE[0] != 0)
    {
        // Clear and stop the timer
        MICROBIT_DISPLAY_TIMER->TASKS_CLEAR = 1;
        MICROBIT_DISPLAY_TIMER->TASKS_STOP = 1;
        MICROBIT_DISPLAY_TIMER->EVENTS_COMPARE[0] = 0;
        // Refresh the display
        displayRefresh();
        // Restart the timer
        MICROBIT_DISPLAY_TIMER->TASKS_START = 1;
    }
}

// Interrupt handler for the display refresh timer
extern "C" void TIMER2_IRQHandler()
{
    displayRefreshInterruptHandler();
}

// Initialises the display and clears it
void initialiseDisplay()
{
    for (int i = 0; i < 10; i++)
    {
        setPin(MICROBIT_PINS.pins[i], OUTPUT, false);
    }
    clearDisplay();
    /// Configure the refresh timer
    MICROBIT_DISPLAY_TIMER->MODE = TIMER_MODE_MODE_Timer;
    MICROBIT_DISPLAY_TIMER->BITMODE = TIMER_BITMODE_BITMODE_16Bit;
    MICROBIT_DISPLAY_TIMER->PRESCALER = 4;
    MICROBIT_DISPLAY_TIMER->CC[0] = REFRESH_INTERVAL_US;
    MICROBIT_DISPLAY_TIMER->INTENSET = TIMER_INTENSET_COMPARE0_Msk;
    MICROBIT_DISPLAY_TIMER->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Msk;
    // Map the timer to the interrupt function and start the timer
    NVIC_DisableIRQ(TIMER2_IRQn);
    NVIC_ClearPendingIRQ(TIMER2_IRQn);
    NVIC_SetPriority(TIMER2_IRQn, 100);
    NVIC_EnableIRQ(TIMER2_IRQn);
    MICROBIT_DISPLAY_TIMER->TASKS_START = 1;
}

// Clears the display
void clearDisplay()
{
    for (int i = 0; i < DISPLAY_WIDTH; i++)
    {
        for (int j = 0; j < DISPLAY_HEIGHT; j++)
        {
            display[i][j] = 0;
        }
    }
}

// Displays an image
void displayImage(MicrobitImage *image)
{
    for (int col = 0; col < DISPLAY_WIDTH; col++)
    {
        for (int row = 0; row < DISPLAY_HEIGHT; row++)
        {
            display[row][col] = (*image)[row][col];
        }
    }
}

// Sets the value of the pixel at the given x and y coordinates
void setPixel(int x, int y, int value) { display[x][y] = value; }
// ####################################################################

// MAIN FUNCTIONS
// ####################################################################
extern void setup(); // Override this function in your main file for setup
extern void loop();  // Override this function in your main file for the main loop

// Main function
int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
// ####################################################################