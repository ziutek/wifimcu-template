#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx.h"

#if defined(STM32F407xx) // Assume this means STM32F4DISCOVERY

#define NumberOfLEDs 4
#define LEDGPIO GPIOD
#define FirstLEDPin 12
#define EnableLEDPeripheralClock() EnableAHB1PeripheralClock(RCC_AHB1ENR_GPIODEN)

#elif defined(STM32F429xx) // Assume this means 32F429DISCOVERY

#define LEDGPIO GPIOG
#define NumberOfLEDs 2
#define FirstLEDPin 13
#define EnableLEDPeripheralClock() EnableAHB1PeripheralClock(RCC_AHB1ENR_GPIOGEN)

#else

#error This board is not supported.

#endif

#define LEDMask ((1<<NumberOfLEDs)-1)

void InitializeLEDs();

static inline void SetLEDs(int leds)
{
	uint16_t val=LEDGPIO->ODR;
	val&=~(LEDMask<<FirstLEDPin);
	val|=leds<<FirstLEDPin;
	LEDGPIO->ODR=val;
}

static inline void ToggleLEDs(int leds)
{
	LEDGPIO->ODR^=(leds&LEDMask)<<FirstLEDPin;
}

static inline void TurnOnLEDs(int leds)
{
	LEDGPIO->BSRR=(leds&LEDMask)<<FirstLEDPin;
}

static inline void TurnOffLEDs(int leds)
{
	LEDGPIO->BSRR=(leds&LEDMask)<<(FirstLEDPin+16);
}

#endif

