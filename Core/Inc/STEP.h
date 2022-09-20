/*
 * STEP.h
 *
 *  Created on: Sep 19, 2022
 *      Author: yunus
 */

#ifndef INC_STEP_H_
#define INC_STEP_H_


#define RR	0x01
#define RL	0x02

void FullStep(uint16_t StepSize, uint8_t Direction, uint16_t Speed);
void HalfStep(uint16_t StepSize, uint8_t Direction, uint16_t Speed);
void Delay(uint16_t Delay);


#endif /* INC_STEP_H_ */
