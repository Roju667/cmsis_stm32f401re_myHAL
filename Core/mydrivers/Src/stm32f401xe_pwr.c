/*
 * stm32f401xe_pwr.c
 *
 *  Created on: 27 sty 2022
 *      Author: ROJEK
 */

#include "stm32f401xe_pwr.h"

/*
 * Configure power voltage detection
 * @param[pvd_level] - enter voltage level that ha to be checked
 * @param[mode] - pvdo can be checked by user by polling or can SET IRQ from EXTI line 16
 */
void Pwr_EnablePvd(PvdThresholdLevel_t pvd_level, PvdMode_t mode)
{
	// enable power regulator bit
	PWR->CR |= PWR_CR_PVDE;

	// modify power threshold value
	PWR->CR &= ~(PWR_CR_PLS);
	PWR->CR |= (pvd_level << PWR_CR_PLS_Pos);

	// enable IRQ or not
	if (kPvdModeNormal)
	{
		return;
	}
	else
	{
		NVIC_EnableIRQ(PVD_IRQn);
		EXTI->IMR |= EXTI_IMR_MR16;

		if (mode == kPvdModeIrqRT)
		{
			EXTI->FTSR |= EXTI_FTSR_TR16;
		}

		if (mode == kPvdModeIrqFT)
		{
			EXTI->RTSR |= EXTI_RTSR_TR16;
		}
	}

}

/*
 * Enter sleep mode
 * @param[exit] - enter sleep now [kWFI/kWFE] or enter after exiting ISR [kSleepOnExit]
 */
void Pwr_EnterSleepMode(PwrExit_t exit)
{
	// deselect deep sleep mode
	SCB->SCR &= ~(SCB_SCR_SLEEPDEEP_Msk);

	if(exit == kWFI)
	{
	__WFI();
	}

	if(exit == kWFE)
	{
	__WFE();
	}

	if(exit == kSleepOnExit)
	{
	PWR_SLEEPONEXIT_ENABLE();
	}
}

/*
 * Enter stop mode
 * @param[exit] - enter sleep now [kWFI/kWFE] or enter after exiting ISR [kSleepOnExit]
 * @param[stop_mode] - stop mode configuration described in RM PWR chapter
 */
void Pwr_EnterStopMode(PwrExit_t exit, StopModes_t stop_mode)
{
	//select deep sleep mode
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	//select between stop and standby mode
	PWR->CR &= ~(PWR_CR_PDDS);

	//set parameters for stop mode
	PWR->CR &= ~(PWR_CR_MRLVDS);
	PWR->CR &= ~(PWR_CR_LPLVDS);
	PWR->CR &= ~(PWR_CR_FPDS);
	PWR->CR &= ~(PWR_CR_LPDS);

	switch (stop_mode)
	{
	case (kStopMR):
		break;
	case (kStopMRFPD):
		PWR->CR |= PWR_CR_FPDS;
		break;
	case (kStopLP):
		PWR->CR |= PWR_CR_LPDS;
		break;
	case (kStopLPFPD):
		PWR->CR |= PWR_CR_LPDS | PWR_CR_FPDS;
		break;
	case (kStopMRLV):
		PWR->CR |= PWR_CR_MRLVDS;
		break;
	case (kStopLPLV):
		PWR->CR |= PWR_CR_LPDS | PWR_CR_LPLVDS;
		break;
	default:
		return;
	}

	if(exit == kWFI)
	{
	__WFI();
	}

	if(exit == kWFE)
	{
	__WFE();
	}

	if(exit == kSleepOnExit)
	{
	PWR_SLEEPONEXIT_ENABLE();
	}
}

/*
 * Enter standby mode
 * @param[exit] - enter sleep now [kWFI/kWFE] or enter after exiting ISR [kSleepOnExit]
 * RTC has to be configured (alarm/tamper/timestamp) - come back here after RTC deepdive
 */
void Pwr_EnterStandbyMode(PwrExit_t exit)
{
	//select deep sleep mode
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	//select between stop and standby mode
	PWR->CR |= PWR_CR_PDDS;
	// bit is cleared in Power Control/Status register
	PWR->CSR &= ~(PWR_CSR_WUF);

	if(exit == kWFI)
	{
	__WFI();
	}

	if(exit == kWFE)
	{
	__WFE();
	}

	if(exit == kSleepOnExit)
	{
	PWR_SLEEPONEXIT_ENABLE();
	}
}