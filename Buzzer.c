/*
 * Buzzer.c
 *
 *  Created on: 9 de nov. de 2019
 *      Author: Icomp2015
 */
#include "LPC17xx.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_timer.h"
uint8_t counter=0;
uint8_t counterTarget=0;
uint8_t flag=1;
void confDAC(){
	DAC_Init(LPC_DAC);
return;}
void confPinDAC(){
	PINSEL_CFG_Type PinCfg;
	PinCfg.Portnum=PINSEL_PORT_0;    /**< Port Number, should be PINSEL_PORT_x,
	                        where x should be in range from 0 to 4 */
	PinCfg.Pinnum=PINSEL_PIN_26;        /**< Pin Number, should be PINSEL_PIN_x,
	                        where x should be in range from 0 to 31 */
	PinCfg.Funcnum= PINSEL_FUNC_2;    /**< Function Number, should be PINSEL_FUNC_x,
	                        where x should be in range from 0 to 3 */
	PinCfg.Pinmode=PINSEL_PINMODE_TRISTATE;    /**< Pin Mode, should be:
	                        - PINSEL_PINMODE_PULLUP: Internal pull-up resistor
	                        - PINSEL_PINMODE_TRISTATE: Tri-state
	                        - PINSEL_PINMODE_PULLDOWN: Internal pull-down resistor */
	PinCfg.OpenDrain=PINSEL_PINMODE_NORMAL;    /**< OpenDrain mode, should be:
	                        - PINSEL_PINMODE_NORMAL: Pin is in the normal (not open drain) mode
	                        - PINSEL_PINMODE_OPENDRAIN: Pin is in the open drain mode */
	PINSEL_ConfigPin(&PinCfg);
return;}
void confTimerBuzzer(){
	 TIM_TIMERCFG_Type struct_timer;
	    TIM_MATCHCFG_Type struct_match;
	    struct_timer.PrescaleOption=TIM_PRESCALE_TICKVAL;
	    struct_timer.PrescaleValue=100;
	    struct_match.MatchChannel=0;
	    struct_match.IntOnMatch=ENABLE;
	    struct_match.StopOnMatch=DISABLE;
	    struct_match.ResetOnMatch=ENABLE;
	    struct_match.ExtMatchOutputType=TIM_EXTMATCH_NOTHING;
	    struct_match.MatchValue=10000;
	    TIM_Init(LPC_TIM2,TIM_TIMER_MODE,&struct_timer);
	    TIM_ConfigMatch(LPC_TIM2,&struct_match);
	    //TIM_Cmd(LPC_TIM2,ENABLE);
	    NVIC_EnableIRQ(TIMER2_IRQn);
return;}
/*
 * Delay: 400000 equiv 11Hz
 */
void delayBuzzer(){
	for(uint32_t i=0;i<4000000000;i++){}
return;}
/*
 * Funcion Cuadrada
 */
void soundCorrect(){
	counterTarget=2;
return;}
void soundIncorrect(){
	counterTarget=4;
return;}
void soundAlarm(){
	counterTarget=30;
return;}
void TIMER2_IRQHandler(){
	TIM_ClearIntPending(LPC_TIM2,TIM_MR0_INT);
	if(counter<counterTarget){
		if(flag){
			DAC_UpdateValue(LPC_DAC,1023);
			flag=0;
		}else{
			DAC_UpdateValue(LPC_DAC,0);
			flag=1;
		}
		counter++;
	}if(counter==counterTarget){
		 TIM_Cmd(LPC_TIM2,DISABLE);
		 counter=0;
	}
return;}

