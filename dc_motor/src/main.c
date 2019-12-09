#include "main.h"
#include "tim5_pwm.h"


int main() {
	int duty_cycle_percentage = 10;
	
	tim5_pwm2_setup();                                 //Set up channel 2 on timer 5 as pwm
	tim5_pwm2_pin_setup();                             // Set up pin A1 to output timer 5 channel 2 (PWM)
	tim5_pwm2_set_duty_cycle(duty_cycle_percentage);   // Set duty cycle for pwm on timer 5 channel 2
	
	/*
	
	Need to buy external op amp due to gpio not being able to power motor and internal op amps inability to be used as buffers.
	
	*/

	while(1){
		
	}
	
	return 0;
}