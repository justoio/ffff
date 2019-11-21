/*
 * DisplayUart.c

 *
 *  Created on: 11 de nov. de 2019
 *      Author: Icomp2015
 */
#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#define SIZE 17
uint8_t info[SIZE] = "PASSWORD:\n\rXXXX\n\r";
uint8_t passChars[4];
uint8_t passCharsCounter=0;


void confPinsDisplayUart(){
	PINSEL_CFG_Type PinCfg;
	//configuración pin de Tx y Rx
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 2;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 3;
	PINSEL_ConfigPin(&PinCfg);
return;}
void confUart(void){
	UART_CFG_Type UARTConfigStruct;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	//configuración por defecto:
	UART_ConfigStructInit(&UARTConfigStruct);
	//inicializa periférico
	UART_Init(LPC_UART0, &UARTConfigStruct);
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	//Inicializa FIFO
	UART_FIFOConfig(LPC_UART0, &UARTFIFOConfigStruct);
	//Habilita transmisión
	UART_TxCmd(LPC_UART0, ENABLE);
	//Habilita interrucpción Tx
	//UART_IntConfig(LPC_UART0, UART_INTCFG_THRE, ENABLE);
	/* preemption = 1, sub-priority = 1 */
	//NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));
	//Habilita interrpción por UART0
	//NVIC_EnableIRQ(UART0_IRQn);
return;}
void setMessage(uint8_t mje[SIZE]){
	for(uint8_t i=0;i<SIZE;i++)
	info[i]=mje[i];
return;}
void setCharInMessage(uint8_t mje,uint8_t i){
	info[i]=mje;
return;}
void updateCharPass(uint8_t mje){
	if(passCharsCounter<4){
	info[11+passCharsCounter]=mje;
	passCharsCounter++;
	}if(passCharsCounter==4){passCharsCounter=0;}

return;}
void confTimerDisplayUart(){
    TIM_TIMERCFG_Type struct_timer;
    TIM_MATCHCFG_Type struct_match;
    struct_timer.PrescaleOption=TIM_PRESCALE_USVAL;
    struct_timer.PrescaleValue=100;
    struct_match.MatchChannel=0;
    struct_match.IntOnMatch=ENABLE;
    struct_match.StopOnMatch=DISABLE;
    struct_match.ResetOnMatch=ENABLE;
    struct_match.ExtMatchOutputType=TIM_EXTMATCH_NOTHING;
    struct_match.MatchValue=10000;
    TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&struct_timer);
    TIM_ConfigMatch(LPC_TIM0,&struct_match);
    TIM_Cmd(LPC_TIM0,ENABLE);
    NVIC_EnableIRQ(TIMER0_IRQn);
return;}

void TIMER0_IRQHandler(){
	TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT);
	UART_Send(LPC_UART0, info, sizeof(info), NONE_BLOCKING);
return;}
