/*
 * LDR.c
 *
 *  Created on: 9 de nov. de 2019
 *      Author: Icomp2015
 */
#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "LDR.h"
void confPinADC(){
	PINSEL_CFG_Type PinCfg;
		PinCfg.Portnum=PINSEL_PORT_0;    /**< Port Number, should be PINSEL_PORT_x,
		                        where x should be in range from 0 to 4 */
		PinCfg.Pinnum=PINSEL_PIN_23;        /**< Pin Number, should be PINSEL_PIN_x,
		                        where x should be in range from 0 to 31 */
		PinCfg.Funcnum= PINSEL_FUNC_1;    /**< Function Number, should be PINSEL_FUNC_x,
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
void confADC(){
	ADC_Init(LPC_ADC, 250);
	ADC_BurstCmd(LPC_ADC, ENABLE);
	ADC_ChannelCmd (LPC_ADC,0, ENABLE);
	ADC_IntConfig (LPC_ADC, ADC_ADINTEN0,ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
return;}
/*
 * @brief: Enciende un led
 */
void modoNocturno(){
	//Falta Implementar
return;}
void modoDiurno(){
	//Falta Implementar
return;}

void ADC_IRQHandler(){
	uint16_t ADC0Value=0;
	ADC0Value=ADC_ChannelGetData(LPC_ADC,0);
	if(ADC0Value<3250){
		GPIO_ClearValue(0,(1<<22));
	}else{
		GPIO_SetValue(0,(1<<22));
		ADC_ChannelCmd (LPC_ADC,0, DISABLE);
		soundAlarm();
		TIM_Cmd(LPC_TIM2,ENABLE);
	}
	//Bajar valor de ADC 250
	//Promedio movil.
	//
return;}
