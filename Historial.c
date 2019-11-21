/*
 * Historial.c
 *
 *  Created on: 20 de nov. de 2019
 *      Author: Icomp2015
 */
#include "lpc17xx_rtc.h"
void confRTC(){
	RTC_TIME_Type pFullTime;
	RTC_TIME_Type pFullTime2;
	RTC_GetFullTime(LPC_RTC,&pFullTime);
	RTC_Init(LPC_RTC);
	pFullTime2.SEC=0;         /*!< Seconds Register */
	pFullTime2.MIN=10;         /*!< Minutes Register */
	pFullTime2.HOUR=23;         /*!< Hours Register */
	pFullTime2.DOM=19;        /*!< Day of Month Register */
	pFullTime2.DOW=2;         /*!< Day of Week Register */
	pFullTime2.DOY=323;         /*!< Day of Year Register */
	pFullTime2.MONTH=11;     /*!< Months Register */
	pFullTime2.YEAR=2019;         /*!< Years Register */
	RTC_SetFullTime(LPC_RTC, &pFullTime2);
	RTC_Cmd(LPC_RTC, ENABLE);
	while(1){
	RTC_GetFullTime(LPC_RTC,&pFullTime);
	}
return;}

