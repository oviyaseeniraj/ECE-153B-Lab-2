/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 2C
 */
 
#include "stm32l476xx.h"

#include "LED.h"
#include "RTC.h"
#include "SysClock.h"

char strTime[12] = {0};
char strDate[12] = {0};

void RTC_Set_Alarm(void) {
	RTC->CR &= ~(RTC_CR_ALRAE | RTC_CR_ALRBE | RTC_CR_ALRAIE | RTC_CR_ALRBIE);
	
	RTC_Disable_Write_Protection();
	
	while (!(RTC_ISR_ALRAWF && RTC_ISR_ALRBWF)){}//wait till alarm registers can be written to
	
	//alarm A when time is 30 seconds
		
	RTC->ALRMAR |=	(RTC_ALRMAR_ST_0 | RTC_ALRMAR_ST_1); // set tens digit of alarm to 11 (3)
	RTC->ALRMAR &= ~(RTC_ALRMAR_ST_2);
	RTC->ALRMAR &= ~(RTC_ALRMAR_SU_0 | RTC_ALRMAR_SU_1 | RTC_ALRMAR_SU_2 | RTC_ALRMAR_SU_3); // set seconds units digit to zero
	RTC->ALRMAR |= (RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2); //other values always true use as don't care
	
	//alarm B every second
	RTC->ALRMBR |= (RTC_ALRMBR_MSK4 | RTC_ALRMBR_MSK3 | RTC_ALRMBR_MSK2 | RTC_ALRMBR_MSK1); // everything except for second don't care
	
	RTC->CR |= (RTC_CR_ALRAE | RTC_CR_ALRBE | RTC_CR_ALRAIE | RTC_CR_ALRBIE);
	
	RTC_Enable_Write_Protection();
	
}

void RTC_Alarm_Enable(void) {
	EXTI->RTSR1 |= EXTI_RTSR1_RT18; // Configure the interrupt to trigger on the rising edge in EXTI RTSRx
	EXTI->IMR1 |= EXTI_IMR1_IM18; //set the interrupt mask in EXTI IMRx.
	EXTI->EMR1 |= EXTI_EMR1_EM18; //set the event mask in EXTI EMRx.
	EXTI->PR1 |= EXTI_PR1_PIF18; // Clear the pending interrupt in EXTI PRx by writing a 1 to the bit that corresponds to the target EXTI line.
	NVIC_EnableIRQ(RTC_Alarm_IRQn); //Enable the interrupt in the NVIC 
	NVIC_SetPriority(RTC_Alarm_IRQn, 0); //set it to have the highest priority.
}

void RTC_Alarm_IRQHandler(void) {
	EXTI->PR1 |= EXTI_PR1_PIF18; // clear necessary flags (pending bit)
	RTC->ISR &= ~(RTC_ISR_ALRAF | RTC_ISR_ALRBF); // clear necessary flags (alarm event flag)
	
	//ENABLE A, DISABLE B AND VICE VERSA WHEN CHECKOFF
	//RTC->CR |= (RTC_CR_ALRAE | RTC_CR_ALRAIE);
	//RTC->CR &= ~(RTC_CR_ALRBE | RTC_CR_ALRBIE);
	
	Green_LED_Toggle();
}

int main(void) {	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	LED_Init();
	
	RTC_Init();
	RTC_Alarm_Enable();
	RTC_Set_Alarm();
	
	while(1) {
		// [TODO]
		Get_RTC_Calendar(strTime, strDate);
	}
}
