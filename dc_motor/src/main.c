#include "main.h"

int main() {
	
	// Clock setup, PWM setup
	// Leaving MSI clock at default (2.097 MHz)
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Enable General Purpose Timer 5 clock
	TIM5->CR1 |= TIM_CR1_CEN;           // Enable General Purpose Timer 5 Counter
	
	TIM5->CCER |= TIM_CCER_CC1E;        //Enable OC1 to be output to the corresponding pin (A0)
	TIM5->CCMR1 &= ~(TIM_CCMR1_OC1M);   // Reset output compare 1 mode bits
	TIM5->CCMR1 |= TIM_CCMR1_OC1M_PWM1; // Set output compare 1 mode to PWM 1 mode (upcounting)
	TIM5->CCMR1 |= TIM_CCMR1_OC1PE;     // Set output compare 1 preload enable bit
	TIM5->CR1 |= TIM_CR1_ARPE;          // Set auto-reload preload bit
	TIM5->CCR1 = 62000;                 // Set capture/compare register 1 to 32767 giving pwm a duty cycle of 50%
	TIM5->ARR = 65534;                  // Set Auto Reload Register, Timer will reset to 0 upon reaching this value
	TIM5->EGR |= TIM_EGR_UG;            // Re-initialize the counter and generate update of the registers
	
	
	// Enable GPIOA, set GPIOA to alternate function (TIM5_CH1)
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;          // Enable the GPIOA peripheral in 'RCC_AHBENR'
	GPIOA->MODER  &= ~(GPIO_MODER_MODER0);      // Reset pin A0 Mode configuration bits
	GPIOA->MODER  |=  (GPIO_MODER_MODER0_1);    // Set pin A0 Mode to alternate function mode
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_0);       // Set pin A0 output type to push-pull
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL0);       // Reset alternate function register bits corresponding to pin A0
	GPIOA->AFR[0] |= 0x2;                       // Set alternate function for pin A0 to AF1 (TIM5_CH1)
	
	
	while(1){
		
	}
	
	return 0;
}