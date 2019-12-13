#include "main.h"
#include "stm32_timers.h"


int main() {
	
	int duty_cycle_percentage = 1;
	
	tim4_pwm1_setup();
	
	tim4_pwm1_pin_setup();
	
	tim4_pwm1_set_duty_cycle(duty_cycle_percentage);
	
	TIM4->ARR = 32760;
	
	// SET UP TIMER INTERRUPT TO INCREMENT/DECREMENT DUTY CYCLE
	
	
	while(1){
		if (TIM4->CNT > 30000){
			GPIOB->ODR |= (GPIO_ODR_ODR_7);
		}
		else{
			GPIOB->ODR &= ~(GPIO_ODR_ODR_7);
		}
	}
	
	return 0;
}