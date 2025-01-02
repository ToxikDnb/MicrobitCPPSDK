#include <Microbit/Core/Delays.h>

// Global Variables
bool isDelayTimerInitialised = false;
volatile bool isDelay = false;

// Internal function for initialising the timer. Not intended to be used by users
void initialiseDelayTimer()
{
    // Enable TIMER3 peripheral
    DELAY_TIMER->TASKS_STOP = 1;
    DELAY_TIMER->TASKS_CLEAR = 1;
    DELAY_TIMER->MODE = TIMER_MODE_MODE_Timer;
    DELAY_TIMER->BITMODE = TIMER_BITMODE_BITMODE_32Bit;
    DELAY_TIMER->INTENSET = TIMER_INTENSET_COMPARE0_Msk;
    DELAY_TIMER->PRESCALER = 4; // 16MHz/2^4 = 1MHz (1us resolution)

    // Configure interrupt
    NVIC_SetPriority(TIMER3_IRQn, 1);
    NVIC_EnableIRQ(TIMER3_IRQn);
    isDelayTimerInitialised = true;
}

// This function causes the MicroBit to pause for a specified amount of whole seconds.
// TODO: Improve function safety by using looping for longer delays
void delayS(uint32_t seconds)
{
    while(seconds > 0){
        if(seconds > MAX_SAFE_SECONDS){
            delayU(MAX_SAFE_SECONDS * 1000000);
            seconds -= MAX_SAFE_SECONDS;
        } else {
            delayU(seconds * 1000000);
            seconds = 0;
        }
    }
}

// This function causes the MicroBit to pause for a specified amount of whole milliseconds.
void delayM(uint32_t milliseconds)
{
    while(milliseconds > 0){
        if(milliseconds > MAX_SAFE_MILLISECONDS){
            delayU(MAX_SAFE_MILLISECONDS * 1000);
            milliseconds -= MAX_SAFE_MILLISECONDS;
        } else {
            delayU(milliseconds * 1000);
            milliseconds = 0;
        }
    }
}

// Timer interrupt handler. Again, not intended for users.
extern "C" void TIMER3_IRQHandler()
{
    if (DELAY_TIMER->EVENTS_COMPARE[0] != 0)
    {
        DELAY_TIMER->EVENTS_COMPARE[0] = 0;
        DELAY_TIMER->TASKS_STOP = 1;
        isDelay = false;
    }
}

/*
This function causes the MicroBit to pause for a specified amount of microseconds, and is the core of how the
SDK calculates delays.
*/
void delayU(uint32_t microseconds)
{
    // Add current timer delay and position to buffer
    // Configure timer if not initialised
    if (!isDelayTimerInitialised)
        initialiseDelayTimer();
    // Set compare register
    DELAY_TIMER->TASKS_STOP = 1;
    DELAY_TIMER->TASKS_CLEAR = 1;
    DELAY_TIMER->CC[0] = microseconds;

    NVIC_ClearPendingIRQ(TIMER3_IRQn);

    // Start timer
    isDelay = true;
    DELAY_TIMER->TASKS_START = 1;

    while (isDelay)
    {
        __WFI();
    }
}
