#include <Microbit/Microbit.h>

/**
 * @details This game is a simple game where the player has to eat the food that appears on the screen
 * The player controls their character with the accelerometer on the microbit
 * Once the player has eaten a piece of food, the food will disappear and reappear in a new location
 * After eating ten food, the player wins and a victory screen is displayed!
 *
 * This game only uses 236 bytes of RAM and 3.4KB of rom, designed to show how both lightweight, readable and powerful the base SDK is
 *
 * @author Mackenzie Blackaby
 */

#define MIDPOINT 180
#define DEADZONE 20
#define LOWER_ANGLE_LIMIT MIDPOINT - DEADZONE
#define UPPER_ANGLE_LIMIT MIDPOINT + DEADZONE
#define COUNTER_LIMIT 50 // How many MS to wait before moving the character. Could use speed and calculate this dynamically

MicrobitImage victoryImage = {
    {0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0}};

// Accelerometer angle for X and Y
int16_t angle[2] = {0, 0};
// Positioning variables
uint8_t characterPosition[2] = {2, 2};
uint8_t characterPositionPrevious[2] = {2, 2};
uint8_t foodPosition[2] = {0, 0};
// Movement variables
bool isMovingHorizontal = false;
bool isMovingVertical = false;
uint16_t horizontalCounter = 0;
uint16_t verticalCounter = 0;
// Game variables
uint8_t foodCount = 0;

// Function prototypes
void deployFood();
bool calculateNewPosition();

void setup()
{
    initialiseDisplay();
    setPixel(characterPosition[0], characterPosition[1], 1);
    setPixel(foodPosition[0], foodPosition[1], 1);
}

void loop()
{
    // Keep track of the accelerometer readings
    angle[0] = getAccelerometerDegrees('X');
    angle[1] = getAccelerometerDegrees('Y');

    // Check if the character has moved
    if (calculateNewPosition())
    {
        // Clear the previous position of the character
        setPixel(characterPositionPrevious[0], characterPositionPrevious[1], 0);

        // Set the new position of the character
        setPixel(characterPosition[0], characterPosition[1], 1);

        // Update the previous position of the character
        characterPositionPrevious[0] = characterPosition[0];
        characterPositionPrevious[1] = characterPosition[1];
    }

    // Check if the character has eaten the food
    if (characterPosition[0] == foodPosition[0] && characterPosition[1] == foodPosition[1])
    {
        foodCount++;
        deployFood();
    }

    // Check if the player has won
    if (foodCount >= 10)
    {
        clearDisplay();
        displayImage(&victoryImage);
    }

    // Delay for a short period to control movement speed
    delayM(1);
}

// Function to deploy the food on the screen
void deployFood()
{
    // Generate a new position for the food, ensuring it is not on the character
    while (foodPosition[0] == characterPosition[0] && foodPosition[1] == characterPosition[1])
    {
        foodPosition[0] = randint(0, DISPLAY_WIDTH - 1);
        foodPosition[1] = randint(0, DISPLAY_HEIGHT - 1);
    }
    // Show the food at the given position
    setPixel(foodPosition[0], foodPosition[1], 1);
}

// Function to calculate the new position of the character, returns true if the character has moved
bool calculateNewPosition()
{
    // Init return variable
    bool hasMoved = false;
    // If angle outside of deadzone
    if (angle[0] < LOWER_ANGLE_LIMIT || angle[0] > UPPER_ANGLE_LIMIT)
    {
        // Character is moving horizontally
        isMovingHorizontal = true;
        // If horizontal counter reaches the limit
        if (horizontalCounter == COUNTER_LIMIT)
        {
            // Calculate the direction of the angle tilt and adjust the position by this, then reset the counter
            int8_t dir = angle[0] < LOWER_ANGLE_LIMIT ? -1 : 1;
            characterPosition[1] = clamp(characterPosition[1] + dir, 0, DISPLAY_WIDTH - 1);
            horizontalCounter = 0;
            hasMoved = true;
        }
        else
            // Increment
            horizontalCounter += 1;
    }
    else
    {
        // Otherwise the character is not moving horizontally so reset everything
        isMovingHorizontal = false;
        horizontalCounter = 0;
    }

    // Repeat for vertical movement
    // Could reduce code redundancy by creating a for system with pointers, but this is more readable
    if (angle[1] < LOWER_ANGLE_LIMIT || angle[1] > UPPER_ANGLE_LIMIT)
    {
        isMovingVertical = true;
        if (verticalCounter == COUNTER_LIMIT)
        {
            int8_t dir = angle[1] < LOWER_ANGLE_LIMIT ? 1 : -1;
            characterPosition[0] = clamp(characterPosition[0] + dir, 0, DISPLAY_HEIGHT - 1);
            verticalCounter = 0;
            hasMoved = true;
        }
        else
            verticalCounter += 1;
    }
    else
    {
        isMovingVertical = false;
        verticalCounter = 0;
    }

    // Return if the character has moved
    return hasMoved;
}