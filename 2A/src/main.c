/*
 * ECE 153B
 *
 * Name(s): Oviya Seeniraj, Lily Chen
 * Section: Tues 7 pm
 * Lab: 2A
 */

#include "stm32l476xx.h"

void GPIO_Init(void){	
	 // 1. Enable the clock for GPIO port C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // 2. Configure pins PC5, PC6, PC8, and PC9 as output
		//clear
    GPIOC->MODER &= ~(
        GPIO_MODER_MODE5 | GPIO_MODER_MODE6 | 
        GPIO_MODER_MODE8 | GPIO_MODER_MODE9);
		//set as output
		GPIOC->MODER |= GPIO_MODER_MODE5_0;
		GPIOC->MODER |= GPIO_MODER_MODE6_0;
		GPIOC->MODER |= GPIO_MODER_MODE8_0;
		GPIOC->MODER |= GPIO_MODER_MODE9_0;

    // 3. Set the output speed of the pins to fast
    GPIOC->OSPEEDR &= ~(
        GPIO_OSPEEDR_OSPEED5 | GPIO_OSPEEDR_OSPEED6 | 
        GPIO_OSPEEDR_OSPEED8 | GPIO_OSPEEDR_OSPEED9);
    GPIOC->OSPEEDR |= (
        (GPIO_OSPEEDR_OSPEED5_1) | (GPIO_OSPEEDR_OSPEED6_1) | 
        (GPIO_OSPEEDR_OSPEED8_1) | (GPIO_OSPEEDR_OSPEED9_1));

    // 4. Set the output type of the pins to push-pull
    GPIOC->OTYPER &= ~(
        GPIO_OTYPER_OT5 | GPIO_OTYPER_OT6 | 
        GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9);

    // 5. Set the pins to no pull-up, no pull-down
    GPIOC->PUPDR &= ~(
        GPIO_PUPDR_PUPD5 | GPIO_PUPDR_PUPD6 | 
        GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD9);

}


#define DELAY 60000	// delay between steps of the sequences

// A = PC5
// A' = PC6
// B = PC8
// B' = PC9

//1010, 1001, 0101, 0110

//1001, 1010, 0110, 0101
void Full_Stepping_Clockwise(void){
		
	//1001
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//1010
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);

	//0110
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//0101
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	
}

void Full_Stepping_CounterClockwise(void){
	//0101
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//0110
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//1010
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//1001
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
}

// 1001, 1000, 1010, 0010, 0110, 0100, 0101, 0001
void Half_Stepping_Clockwise(void){
	//1001
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);

	//1000
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//1010
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//0010
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//0110
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//0100
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//0101
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//0001
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
}

void Half_Stepping_CounterClockwise(void){
	//0001
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//0101
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);	
	
	//0100
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);	
	
	//0110
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//0010
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//1010
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);	
	
	//1000
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
	
	//1001
	GPIOC->ODR |= GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for (unsigned int i = 0; i < DELAY; i++);
}


int main(void){
	GPIO_Init();
	
	// Rotate 360 degrees either clockwise or counter-clockwise
	for (int i = 0; i < 512; i++) {
		Half_Stepping_CounterClockwise();
	}
}
