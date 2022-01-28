/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "stm32f401xe_gpio.h"
#include "stm32f401xe_pwr.h"
#include "stm32f401xe_rcc.h"
#include "stm32f4xx.h"


void GPIOConfig (void);

int main(void)
{
	CLEAR_RESET_FLAGS();
	GPIOConfig();
	Pwr_EnterStopMode(kWFI, kStopLPLV);

	while(1)
	{
		for(uint32_t i = 0; i < 100000; i++)
		{

		}
		GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}
}

void GPIOConfig (void)
{

	GPIO_Handle_t GPIOx;
	GPIOx.PinConfig.Mode = GPIO_PIN_MODE_OUTPUT;
	GPIOx.PinConfig.PinNumber = GPIO_PIN_5;
	GPIOx.PinConfig.OutputType = GPIO_PIN_OT_PP;
	GPIOx.pGPIOx = GPIOA;

	GPIO_InitPin(&GPIOx);


	GPIOx.PinConfig.Mode = GPIO_PIN_MODE_EXTI_FT;
	GPIOx.PinConfig.PinNumber = GPIO_PIN_13;
	GPIOx.pGPIOx = GPIOC;

	GPIO_InitPin(&GPIOx);

	return;
}

void EXTI15_10_IRQHandler(void)
{
	GPIO_ClearPendingEXTIFlag(GPIO_PIN_13);
	GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	SCB->SCR ^= SCB_SCR_SLEEPONEXIT_Msk;

	return;
}
