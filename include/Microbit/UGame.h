#ifndef UGAME
#define UGAME

#include <Microbit/Microbit.h>

// Defines

// Typedefs

// Enums
typedef enum displayType
{
    CUSTOM,
    MICROBIT_DISPLAY,
    ADAFRUIT_SSD1306_OLED
} displayType;

typedef struct vector2
{
    uint32_t x;
    uint32_t y;
} vector2;

typedef enum direction
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
} direction;

typedef enum cancelMode
{
    NEITHER_WIN,   // Default, Pressing opposite directions will cancel each other out
    POSITIVE_WINS, // Pressing opposite directions will result in the positive direction being chosen
    NEGATIVE_WINS, // Pressing opposite directions will result in the negative direction being chosen
    BOTH_WIN       // Pressing opposite directions will result in both directions being chosen
} cancelMode;

// Classes
// Hardware

// Inputs

class dPad
{
private:
    MicrobitPin upPin;
    MicrobitPin downPin;
    MicrobitPin leftPin;
    MicrobitPin rightPin;
    cancelMode mode;
public:
    dPad(MicrobitPin upPin, MicrobitPin downPin, MicrobitPin leftPin, MicrobitPin rightPin, cancelMode mode = NEITHER_WIN);
    ~dPad();

    direction getDirection();
    vector2 getDirectionVector();
    bool isPressed();
};

// Displays
class Display
{
public:
    ~Display();

    virtual void initialise();
};

class pinMatrixDisplay : public Display
{
protected:
    MicrobitPin *colPins;
    MicrobitPin *rowPins;
    uint8_t width;
    uint8_t height;

public:
    pinMatrixDisplay(MicrobitPin *colPins, MicrobitPin *rowPins, uint8_t width, uint8_t height);
    ~pinMatrixDisplay();

    void initialise() override;
};

class InternalMicrobitDisplay : public Display
{
public:
    InternalMicrobitDisplay();
    ~InternalMicrobitDisplay();

    void initialise() override;
};

class i2cDisplay : public Display
{
protected:
    uint32_t address;
    uint32_t width;
    uint32_t height;
    uint32_t speed;

public:
    i2cDisplay();
};

class AdafruitSSD1306OLED : public i2cDisplay
{
public:
    AdafruitSSD1306OLED();
    ~AdafruitSSD1306OLED();

    void initialise() override;
};

// Software

// Sprites
class Sprite
{
private:
    uint32_t x;
    uint32_t y;

public:
    Sprite();
    Sprite(uint32_t x, uint32_t y);
    Sprite(vector2 position);

    ~Sprite();

    void setPosition(uint32_t x, uint32_t y);
    void setPosition(vector2 position);
    void setX(uint32_t x);
    void setY(uint32_t y);

    uint32_t getX();
    uint32_t getY();
};

// Function prototypes
Display getDisplay(displayType type);
pinMatrixDisplay getPinMatrixDisplay(vector2 size, uint32_t *colPins, uint32_t *rowPins);
i2cDisplay getI2CDisplay(uint32_t address, vector2 size, uint32_t speed);
void addSprite(Sprite sprite);
void removeSprite(Sprite sprite);
void moveSprite(Sprite sprite, uint32_t x, uint32_t y);
void moveSprite(Sprite sprite, vector2 position);

#endif