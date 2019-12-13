#include "stm32_timers.h"


//Sets up timer 5 channel 1 as a pwm with hypothetical period of 31.998 ms (Assuming msi clock has not been changed from default) with default duty cycle of 50%
void tim5_pwm1_setup(){
	// Clock setup, PWM setup
	// Leaving MSI clock at default (2.097 MHz)
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Enable General Purpose Timer 5 clock
	TIM5->CR1 |= TIM_CR1_CEN;           // Enable General Purpose Timer 5 Counter
	
	TIM5->CCER |= TIM_CCER_CC1E;        // Enable OC1 to be output to the corresponding pin (A0)
	TIM5->CCMR1 &= ~(TIM_CCMR1_OC1M);   // Reset output compare 1 mode bits
	TIM5->CCMR1 |= TIM_CCMR1_OC1M_PWM1; // Set output compare 1 mode to PWM 1 mode (upcounting)
	TIM5->CCMR1 |= TIM_CCMR1_OC1PE;     // Set output compare 1 preload enable bit
	TIM5->CR1 |= TIM_CR1_ARPE;          // Set auto-reload preload bit
	TIM5->CCR1 = 32767;                 // Set capture/compare register 1 to 32767 giving pwm a duty cycle of 50%
	TIM5->ARR = 65534;                  // Set Auto Reload Register, Timer will reset to 0 upon reaching this value
	TIM5->EGR |= TIM_EGR_UG;            // Re-initialize the counter and generate update of the registers
}

//Sets up timer 5 channel 2 as a pwm with hypothetical period of 31.998 ms (Assuming msi clock has not been changed from default) with default duty cycle of 50%
void tim5_pwm2_setup(){
	// Clock setup, PWM setup
	// Leaving MSI clock at default (2.097 MHz)
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Enable General Purpose Timer 5 clock
	TIM5->CR1 |= TIM_CR1_CEN;           // Enable General Purpose Timer 5 Counter
	
	TIM5->CCER |= TIM_CCER_CC2E;        // Enable OC2 to be output to the corresponding pin (A1)
	TIM5->CCMR1 &= ~(TIM_CCMR1_OC2M);   // Reset output compare 2 mode bits
	TIM5->CCMR1 |= TIM_CCMR1_OC2M_PWM1; // Set output compare 2 mode to PWM 1 mode (upcounting)
	TIM5->CCMR1 |= TIM_CCMR1_OC2PE;     // Set output compare 2 preload enable bit
	TIM5->CR1 |= TIM_CR1_ARPE;          // Set auto-reload preload bit
	TIM5->CCR2 = 32767;                 // Set capture/compare register 2 to 32767 giving pwm a duty cycle of 50%
	TIM5->ARR = 65534;                  // Set Auto Reload Register, Timer will reset to 0 upon reaching this value
	TIM5->EGR |= TIM_EGR_UG;            // Re-initialize the counter and generate update of the registers
}

//Sets up timer 4 channel 1 as a pwm with hypothetical period of 31.998 ms (Assuming msi clock has not been changed from default) with default duty cycle of 50%
void tim4_pwm1_setup(){
	// Clock setup, PWM setup
	// Leaving MSI clock at default (2.097 MHz)
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable General Purpose Timer 4 clock
	TIM4->CR1 |= TIM_CR1_CEN;           // Enable General Purpose Timer 4 Counter
	
	TIM4->CCER |= TIM_CCER_CC1E;        // Enable OC1 to be output to the corresponding pin (B6)
	TIM4->CCMR1 &= ~(TIM_CCMR1_OC1M);   // Reset output compare 1 mode bits
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_PWM1; // Set output compare 1 mode to PWM 1 mode (upcounting)
	TIM4->CCMR1 |= TIM_CCMR1_OC1PE;     // Set output compare 1 preload enable bit
	TIM4->CR1 |= TIM_CR1_ARPE;          // Set auto-reload preload bit
	TIM4->CCR1 = 32767;                 // Set capture/compare register 1 to 32767 giving pwm a duty cycle of 50%
	TIM4->ARR = 65534;                  // Set Auto Reload Register, Timer will reset to 0 upon reaching this value
	TIM4->EGR |= TIM_EGR_UG;            // Re-initialize the counter and generate update of the registers
}

void tim5_pwm1_set_duty_cycle(int percent){
	
	int cnt_period = TIM5->ARR;
	float percent_float = (float) percent;
	float duty_cycle_count_float = ((percent_float/100) * cnt_period);
	unsigned int duty_cycle_count = (unsigned int) duty_cycle_count_float;
	TIM5->CCR1 = (duty_cycle_count);
}

void tim5_pwm2_set_duty_cycle(int percent){
	
	int cnt_period = TIM5->ARR;
	float percent_float = (float) percent;
	float duty_cycle_count_float = ((percent_float/100) * cnt_period);
	unsigned int duty_cycle_count = (unsigned int) duty_cycle_count_float;
	TIM5->CCR2 = (duty_cycle_count);
}

void tim4_pwm1_set_duty_cycle(int percent){
	
	int cnt_period = TIM4->ARR;
	float percent_float = (float) percent;
	float duty_cycle_count_float = ((percent_float/100) * cnt_period);
	unsigned int duty_cycle_count = (unsigned int) duty_cycle_count_float;
	TIM4->CCR1 = (duty_cycle_count);
}

void tim5_pwm1_pin_setup(){
	// Enable GPIOA, set GPIOA0 to alternate function (TIM5_CH1)
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;          // Enable the GPIOA peripheral in 'RCC_AHBENR'
	GPIOA->MODER  &= ~(GPIO_MODER_MODER0);      // Reset pin A0 Mode configuration bits
	GPIOA->MODER  |=  (GPIO_MODER_MODER0_1);    // Set pin A0 Mode to alternate function mode
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_0);       // Set pin A0 output type to push-pull
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL0);       // Reset alternate function register bits corresponding to pin A0
	GPIOA->AFR[0] |= 0x2;                       // Set alternate function for pin A0 to AF2 (TIM5_CH1)
}

void tim5_pwm2_pin_setup(){
	// Enable GPIOA, set GPIOA1 to alternate function (TIM5_CH2)
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;          // Enable the GPIOA peripheral in 'RCC_AHBENR'
	GPIOA->MODER  &= ~(GPIO_MODER_MODER1);      // Reset pin A1 Mode configuration bits
	GPIOA->MODER  |=  (GPIO_MODER_MODER1_1);    // Set pin A1 Mode to alternate function mode
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_1);       // Set pin A1 output type to push-pull
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL1);       // Reset alternate function register bits corresponding to pin A1
	GPIOA->AFR[0] |= 0x20;                      // Set alternate function for pin A1 to AF2 (TIM5_CH2)
}

void tim4_pwm1_pin_setup(){
	// Enable GPIOB, set GPIOB6 to alternate function (TIM4_CH1)
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;          // Enable the GPIOB peripheral in 'RCC_AHBENR'
	GPIOB->MODER  &= ~(GPIO_MODER_MODER6);      // Reset pin B6 Mode configuration bits
	GPIOB->MODER  |=  (GPIO_MODER_MODER6_1);    // Set pin B6 Mode to alternate function mode
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_6);       // Set pin B6 output type to push-pull
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6);       // Reset alternate function register bits corresponding to pin B6
	GPIOB->AFR[0] |= 0x2000000;                 // Set alternate function for pin B6 to AF2 (TIM4_CH1)
}

void tim4_set_period_as_percent_of_clk(int percent){
	float percent_float = (float) percent;
	float period_count_float = ((percent_float/100) * 65535);
	unsigned int period_count = (unsigned int) period_count_float);
	TIM4->ARR = period_count;
}