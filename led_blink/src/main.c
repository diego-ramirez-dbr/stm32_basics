#include "main.h"

int main() {

	// Enable the GPIOB peripheral in 'RCC_AHBENR'.
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	
	//Set MSI clock to 65.536 kHz
	RCC->ICSCR &= ~(0x7 << 13);
	
	// Enable the TIM2 counter
	RCC->APB1ENR |= 0x1;
	TIM2->CR1 |= 0x1;
	//TIM2->CR1 |= TIM_CR1_CEN;
	
	// Set TIM2 up as output compare
	//TIM2->CCMR1 |= (0x3 << 4); //Set output compare 1 mode to toggle channel 1 level on match
	
	// Enable OC1(output compare) Signal
	//TIM2->CCER |= 0x1;
	
	//Set capture/compare register 1 to 65535
	//TIM2->CCR1 = 0xFFFE;
	

	// Initialize the GPIOB pins.
	// B2 should be set to 'input' mode with pull-up.
	GPIOB->MODER &= ~(0x3 << (BUTTON_PIN*2));
	GPIOB->PUPDR &= ~(0x3 << (BUTTON_PIN*2));
	GPIOB->PUPDR |=  (0x1 << (BUTTON_PIN*2));
	// B6 is connected to an LED on the 'Discovery' board.
	// It should be set to push-pull low-speed output.
	GPIOB->MODER  &= ~(0x3 << (LED_PIN*2));
	GPIOB->MODER  |=  (0x1 << (LED_PIN*2));
	GPIOB->OTYPER &= ~(1 << LED_PIN);
	
	// Unsigned int holding value of GPIOB pins
	uint32_t gpiob_input = GPIOB->IDR;
	
	// Set LED pin high.
	GPIOB->ODR |= (1 << LED_PIN);
	
	// Keep track of whether the button is pressed.
	uint8_t button_down = 0;
	while (1) {
		// Invert the IDR register since '0' means 'pressed'.
		uint32_t idr_val = ~GPIOB->IDR;
		//Variable to be set to 1 if counter has reached compare value.
		uint32_t sr_val = TIM2->SR;
		/*if (sr_val & 0x2) {
			// The button is pressed; if it was not already
			// pressed, change the LED state.
			GPIOB->ODR ^= (1 << LED_PIN);
			
			TIM2->SR &= ~(0x2);
		}*/
		if (TIM2->CNT > 0x7FFF){
			GPIOB->ODR |= (1 << LED_PIN);
		}
		else {
			GPIOB->ODR &= ~(1 << LED_PIN);
		}
	}
	
	return 0;
}