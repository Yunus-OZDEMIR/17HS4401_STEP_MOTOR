/*
 * STEP.c
 *
 *  Created on: Sep 19, 2022
 *      Author: yunus
 *      STEP MOTOR : 17HS4401 | 200 STEP = 360°
 *      Maximum RPM is 800 for Speed Parameter
 *      Delay(Speed) -> Delay parameter is microsecond
 *
 */

#include "stm32f4xx_hal.h"
#include "STEP.h"
#include "main.h"
#include <stdbool.h>

extern TIM_HandleTypeDef htim10;
uint8_t StepBuffer = 0;


void Delay(uint16_t Delay){
	__HAL_TIM_SET_COUNTER(&htim10,0);
	while(__HAL_TIM_GET_COUNTER(&htim10)<Delay);
}


void FullStep(uint16_t StepSize, uint8_t Direction, uint16_t Speed){
	GPIOC->ODR = 0;
	if (Direction == RL ){

		for (int i=1; i<=StepSize; i++){

			GPIOC->ODR = 1<<((i-1)%4);
			Delay(Speed);
		}
		GPIOC->ODR = 0;

	}
	else if(Direction == RR){
		for (int i=1; i<=StepSize; i++){
			GPIOC->ODR = 8>>(i-1)%4;
			Delay(Speed);
		}
		GPIOC->ODR = 0;
	}

}

void HalfStep(uint16_t StepSize, uint8_t Direction, uint16_t Speed){
	GPIOC->ODR = 0;
	uint32_t count_full = 1;
	uint32_t count_half = 1;

	if (Direction == RL ){

		for (int i=1; i<=StepSize; i++){
				if (i%2 != 0){
					GPIOC->ODR = (1<<(count_full-1)%4);
					Delay(Speed/2);
					count_full++;
				}
				else{
					if (count_half % 4 != 0){
						GPIOC->ODR = (3<<(count_half-1)%4);
					}
					else{
						GPIOC->ODR = 9;
					}
						Delay(Speed/2);
						count_half++;
				}
		}
		GPIOC->ODR = 0;
	}
	else if(Direction == RR){
		for (int i=1; i<=StepSize; i++){
				if (i%2 != 0){
					GPIOC->ODR = (8>>(count_full-1)%4);
					Delay(Speed/2);
					count_full++;
				}
				else{
					if (count_half % 4 != 0){
						GPIOC->ODR = (12>>(count_half-1)%4);
					}
					else{
						GPIOC->ODR = 9;
					}
					Delay(Speed/2);
					count_half++;
				}
		}
		GPIOC->ODR = 0;
	}
}
