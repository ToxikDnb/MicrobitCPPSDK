#include <Microbit/MicrobitLite.h>

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