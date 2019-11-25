#include "main.h"
#include "tim5_pwm.h"


int main() {
	int duty_cycle_percentage = 10;
	
	tim5_pwm1_setup();
	tim5_pwm1_pin_setup();
	tim5_pwm1_set_duty_cycle(duty_cycle_percentage);
	
	while(1){
		
	}
	
	return 0;
}