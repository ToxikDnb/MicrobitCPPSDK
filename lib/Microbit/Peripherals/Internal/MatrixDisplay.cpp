#include <Microbit/Peripherals/Internal/MatrixDisplay.h>

// Linked lists setup.
// Display
buffer displayBuffer = {0};
MicrobitDisplay display = {{0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0}};
const MicrobitMatrixPins MICROBIT_PINS;

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
    // Map the timer to the interrupt function and start the timer
    NVIC_DisableIRQ(TIMER2_IRQn);
    NVIC_ClearPendingIRQ(TIMER2_IRQn);
    NVIC_SetPriority(TIMER2_IRQn, 4);
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