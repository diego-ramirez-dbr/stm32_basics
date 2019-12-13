#ifndef STM32TIMERS_H
#define STM32TIMERS_H

#include "stm32l152xc.h"
#include "system_stm32l1xx.h"

void tim5_pwm1_setup();

void tim5_pwm2_setup();

void tim4_pwm1_setup();

void tim5_pwm1_set_duty_cycle(int percent);

void tim5_pwm2_set_duty_cycle(int percent);

void tim4_pwm1_set_duty_cycle(int percent);

void tim5_pwm1_pin_setup();

void tim5_pwm2_pin_setup();

void tim4_pwm1_pin_setup();

tim4_set_period_as_percent_of_clk(int percent);

#endif