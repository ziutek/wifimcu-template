#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <stdbool.h>

#include "stm32f4xx.h"

#if defined(STM32F407xx)
#define NumberOfInterruptTableEntries 98
#elif defined(STM32F411xE)
#define NumberOfInterruptTableEntries 102
#elif defined(STM32F429xx)
#define NumberOfInterruptTableEntries 107
#elif defined(STM32F446xx)
#define NumberOfInterruptTableEntries 113
#else
#error This MCU is not supported.
#endif

typedef void InterruptHandler();

void InitialiseSystem();

void InstallInterruptHandler(IRQn_Type interrupt,InterruptHandler handler);
void RemoveInterruptHandler(IRQn_Type interrupt,InterruptHandler handler);

static inline void EnableInterrupt(IRQn_Type interrupt)
{
	int regindex=interrupt>>5;
	int shift=interrupt&0x1f;
	NVIC->ISER[regindex]|=1<<shift;
}

static inline void DisableInterrupt(IRQn_Type interrupt)
{
	int regindex=interrupt>>5;
	int shift=interrupt&0x1f;
	NVIC->ISER[regindex]&=~(1<<shift);
}

static inline bool IsInterruptEnabled(IRQn_Type interrupt)
{
	int regindex=interrupt>>5;
	int shift=interrupt&0x1f;
	if(NVIC->ISER[regindex]&(1<<shift)) return true;
	else return false;
}

static inline void SetInterruptPriority(IRQn_Type interrupt,int priority)
{
	NVIC->IP[interrupt]=priority<<4;
}

#endif
