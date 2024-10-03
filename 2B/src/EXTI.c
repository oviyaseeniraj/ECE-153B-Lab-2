/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 2B
 */

#include "EXTI.h"
#include "LED.h"

void EXTI_Init(void) {
	// Initialize User Button
	 GPIOC->MODER &= ~(GPIO_MODER_MODE13); // Clear MODER13[1:0] for PC13 to set as input
   GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13); // No pull-up, no pull-down for PC13
	
	// Configure SYSCFG EXTI
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	
	// Configure EXTI Trigger
	EXTI->FTSR1 |= EXTI_FTSR1_FT13;
	
	// Enable EXTI
	EXTI->IMR1 |= EXTI_IMR1_IM13;
	
	// Configure and Enable in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn, 0);
}

// [TODO] Write Interrupt Handlers (look in startup_stm32l476xx.s to find the 
// interrupt handler names that you should use)

void EXTI15_10_IRQHandler(void) {
	// Clear interrupt pending bit
		//EXTI->PR1 &= ~EXTI_PR1_PIF13;
	
		if ((EXTI->PR1 & EXTI_PR1_PIF13) != 0)
		{
			Green_LED_Toggle();
			EXTI->PR1 |= EXTI_PR1_PIF13;
		}
	
	// Define behavior that occurs when interrupt occurs
}