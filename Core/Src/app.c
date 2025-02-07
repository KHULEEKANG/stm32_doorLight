/*
 * app.c
 *
 *  Created on: Feb 4, 2025
 *      Author: LEEKANG
 */

#include "app.h"
// 장치 핸들 선언
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim11;

// us지연함수
void delay_us(uint16_t time) {
	htim11.Instance->CNT = 0;
  while(htim11.Instance->CNT < time);
}

void app() {
	// 초음파 초기화
	initUltrasonic(&htim3);
	// 타이머 초기화
	HAL_TIM_Base_Start(&htim11);
	// 타이머를 PWM모드로 시작
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

	int time = 0;
	int valueR = 0;
	int valueG = 0;
	int valueB = 0;

	while(1) {
		uint16_t distance = getDistance();
		sys
		if(distance <= 5) {
			time = 5000;
			valueR = 999;
			valueG = 0;
			valueB = 999;
		}

		if(distance > 5 && time == 0) {
			valueR = 0;
			valueG = 0;
			valueB = 0;
		}

		// 타이머 CCR값 업데이트
		htim1.Instance->CCR1 = valueR;
		htim1.Instance->CCR2 = valueG;
		htim1.Instance->CCR3 = valueB;

		// 초음파 값 읽기
		printf("%d\n", distance);
		HAL_Delay(10);
		time -= 10;
	}
}
