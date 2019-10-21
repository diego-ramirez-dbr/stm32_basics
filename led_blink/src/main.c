#include "main.h"

// Interrupt Request Handler for Timer 2 interrupts
void TIM2_IRQHandler (void){
	if(GPIOB->ODR & GPIO_ODR_ODR_6){ // If pin B6 output data regist = 1(LED is on),
		GPIOB->ODR &= ~(GPIO_ODR_ODR_6); // Set pin B6 output data register = 0(Turn LED off)
	}
	else {
		GPIOB->ODR |= (GPIO_ODR_ODR_6); // Else set pin B6 output data register = 1(turn LED on)
	}
	TIM2->SR &= ~(TIM_SR_UIF); // Clear Timer 2 update interrupt flag
	NVIC_ClearPendingIRQ(TIM2_IRQn); // Clears pending status of Timer 2 interrupt
}


int main() {
	
	// Clock setup, timer setup, interrupt setup
	RCC->ICSCR &= ~(0x7 << 13); // Set MSI clock to 65.536 kHz (Couldn't figure out a way to use macros here that made sense)
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable the GPIOB peripheral in 'RCC_AHBENR'
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable General Purpose Timer 2 clock
	TIM2->CR1 |= TIM_CR1_CEN; // Enable General Purpose Timer 2 Counter
	NVIC_EnableIRQ(TIM2_IRQn); // Enable General Purpose Timer 2 Interrupts
	TIM2->DIER |= TIM_DIER_UIE; // Enable Timer 2 interrupt on update
	
	// Auto Reload Register calculation and setting
	float timer_period = 0.5; // Timer period in seconds, must be between 0 and 1 seconds
	unsigned int arr_reg_val = 65535 / (1 / timer_period); //Calculate value to put in ARR register by dividing register full value by frequency desired (1/period)
	TIM2->ARR = arr_reg_val; // Set Auto Reload Register, Timer will reset to 0 upon reaching this value
	
	// B6 is connected to an LED on the 'Discovery' board
	// Set to push-pull output
	GPIOB->MODER  &= ~(GPIO_MODER_MODER6);      // Reset pin B6 Mode configuration bits
	GPIOB->MODER  |=  (GPIO_MODER_MODER6_0);    // Set pin B6 Mode to general purpose output mode
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_6);       // Set pin B6 output type to push-pull
	
	while (1) {
		
	}
	
	return 0;
}