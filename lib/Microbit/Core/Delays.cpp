#include <Microbit/Core/Delays.h>

bool isDelayTimerInitialised = false;
volatile bool isDelay = false;

// Internal function for initialising the timer
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
        isDelay = false;
    }
}

// Delay function in microseconds
void delayU(uint32_t us)
{
    // Add current timer delay and position to buffer
    // Configure timer if not initialised
    if (!isDelayTimerInitialised)
        initialiseDelayTimer();
    // Set compare register
    DELAY_TIMER->TASKS_STOP = 1;
    DELAY_TIMER->TASKS_CLEAR = 1;
    DELAY_TIMER->CC[0] = us;

    NVIC_ClearPendingIRQ(TIMER3_IRQn);

    // Start timer
    isDelay = true;
    DELAY_TIMER->TASKS_START = 1;

    while (isDelay)
    {
        __WFI();
    }
}
