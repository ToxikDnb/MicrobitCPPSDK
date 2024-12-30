#ifndef DELAYS_H
#define DELAYS_H

#include <nrf.h>

#define DELAY_TIMER ((NRF_TIMER_Type *)0x4001A000UL) // Timer 3

void delayS(uint32_t s);
void delayM(uint32_t ms);
void delayU(uint32_t us);
extern "C" void TIMER3_IRQHandler();

#endif