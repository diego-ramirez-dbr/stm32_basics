#ifndef TIM5PWM_H
#define TIM5PWM_H

#include "stm32l152xc.h"
#include "system_stm32l1xx.h"

void tim5_pwm1_setup();

void tim5_pwm1_set_duty_cycle(int percent);

void tim5_pwm1_pin_setup();

#endif