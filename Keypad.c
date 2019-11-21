/*
 * Keypad.c

 *
 *  Created on: 11 de nov. de 2019
 *      Author: Icomp2015
 */
#include "LPC17xx.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_gpio.h"
#include "DisplayUART.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_pinsel.h"
#include "Security.h"
#include "LDR.h"
#include "Buzzer.h"

#define RISING_EDGE (uint8_t)((0))
#define FALLING_EDGE (uint8_t)((1))
#define PORT2 (uint8_t)((2))
#define INPUT (uint8_t)((0))
#define OUTPUT (uint8_t)((1))
#define FILA1 (uint8_t)((0))
#define FILA2 (uint8_t)((1))
#define FILA3 (uint8_t)((2))
#define FILA4 (uint8_t)((3))

uint8_t auxSystick=0;
uint8_t aButtonCounter=0;
void confPinsKeypad(){
	//PINSEL_CFG_Type PinCfg;
	GPIO_SetDir(PORT2,(0b11110000),OUTPUT);
	GPIO_SetValue(PORT2,(0b11110000));//
	GPIO_SetDir(PORT2,(0b1111),INPUT);
	//GPIO_ClearValue(PORT2,(0b1111));//
	GPIO_IntCmd(PORT2,(0b1111),RISING_EDGE);
	NVIC_EnableIRQ(EINT3_IRQn);
return;}
void confTimerKeypad(){
    TIM_TIMERCFG_Type struct_timer;
    TIM_MATCHCFG_Type struct_match;
    struct_timer.PrescaleOption=TIM_PRESCALE_TICKVAL;
    struct_timer.PrescaleValue=100;
    struct_match.MatchChannel=0;
    struct_match.IntOnMatch=ENABLE;
    struct_match.StopOnMatch=DISABLE;//Que no se detenga luego
    struct_match.ResetOnMatch=ENABLE;
    struct_match.ExtMatchOutputType=TIM_EXTMATCH_NOTHING;
    struct_match.MatchValue=100000;
    TIM_Init(LPC_TIM1,TIM_TIMER_MODE,&struct_timer);
    TIM_ConfigMatch(LPC_TIM1,&struct_match);
    TIM_Cmd(LPC_TIM1,ENABLE);
    NVIC_EnableIRQ(TIMER1_IRQn);
return;}
void RedLedTooglerBlinker(){
	uint32_t tmp_port0=GPIO_ReadValue(0);
	if(tmp_port0&(1<<22)) GPIO_ClearValue(0,(1<<22));
	else GPIO_SetValue(0,(1<<22));
return;}
void delayBuzzer2(){
	for(uint32_t i=0;i<4000000;i++){}
return;}
void EINT3_IRQHandler(){
	uint32_t tmp_port2=GPIO_ReadValue(PORT2);
	RedLedTooglerBlinker();
	if(LPC_GPIOINT->IO2IntStatR&(0b1)){
		if(~(tmp_port2)&(1<<4)){
			saveKey(1);
			keyCounter();
			updateCharPass(49);//1 ASCII
		}
		if(~(tmp_port2)&(1<<5)){
			saveKey(2);
			keyCounter();
			updateCharPass(50);//2 ASCII
		}
		if(~(tmp_port2)&(1<<6)){
			saveKey(3);
			keyCounter();
			updateCharPass(51);//3 ASCII
		}
		if(~(tmp_port2)&(1<<7)){
			aButtonCounter++;
			if(testTryPass1()&&aButtonCounter==1){
				setMessage("CORRECT\n\r!!!\n\r");
				GPIO_ClearValue(1,(1<<19));
				GPIO_SetValue(1,(1<<20));
				soundCorrect();
				TIM_Cmd(LPC_TIM2,ENABLE);
			}else{
				setMessage("INCORRECT\n\r!!!\n\r");
				GPIO_ClearValue(1,(1<<19));
				GPIO_SetValue(1,(1<<18));
				soundIncorrect();
				TIM_Cmd(LPC_TIM2,ENABLE);
			}
			if(aButtonCounter==2){
				setMessage("PASSWORD:\n\rXXXX\n\r");
				aButtonCounter=0;
				resetTryPassword();
				GPIO_ClearValue(1,(1<<20));
				GPIO_ClearValue(1,(1<<18));
				GPIO_SetValue(1,(1<<19));
			}
		}
	}
	if(LPC_GPIOINT->IO2IntStatR&(0b10)){
		if(~(tmp_port2)&(1<<4)){
			saveKey(4);
			keyCounter();
			updateCharPass(52);//1 ASCII
		}
		if(~(tmp_port2)&(1<<5)){
			setMessage("5\n\r");
		}
		if(~(tmp_port2)&(1<<6)){
			setMessage("6\n\r");
		}
		if(~(tmp_port2)&(1<<7)){
			if(testTryPass2()){
					setMessage("NIGHT\n\rMODE!!\n\r");
					GPIO_ClearValue(1,(1<<19));
					GPIO_SetValue(1,(1<<18));
					GPIO_SetValue(1,(1<<21));
					confADC();

				}else{
					setMessage("INCORRECT\n\r!!!\n\r");
				}
		}
	}
	if(LPC_GPIOINT->IO2IntStatR&(0b100)){
		if(~(tmp_port2)&(1<<4)){
			setMessage("7\n\r");
		}
		if(~(tmp_port2)&(1<<5)){
			setMessage("8\n\r");
		}
		if(~(tmp_port2)&(1<<6)){
			setMessage("9\n\r");
		}
		if(~(tmp_port2)&(1<<7)){
			setMessage("C\n\r");
		}
	}
	if(LPC_GPIOINT->IO2IntStatR&(0b1000)){
		if(~(tmp_port2)&(1<<4)){
			setMessage("*\n\r");
		}
		if(~(tmp_port2)&(1<<5)){
			setMessage("0\n\r");
		}
		if(~(tmp_port2)&(1<<6)){
			setMessage("#\n\r");
		}
		if(~(tmp_port2)&(1<<7)){
			setMessage("D\n\r");
		}
	}
	GPIO_ClearInt(PORT2,(0xF));
return;}

void confSystickKeypad(){
	SYSTICK_InternalInit(160);
	SYSTICK_IntCmd(ENABLE);
	SYSTICK_Cmd(ENABLE);
	//NVIC_EnableIRQ( SysTick_IRQn);
return;}
void rotarNibbles(){
	auxSystick++;
	if(auxSystick==1){
		GPIO_SetValue(PORT2,(0b00010000));
		GPIO_ClearValue(PORT2,(0b11100000));
	}if(auxSystick==2){
		GPIO_SetValue(PORT2,(0b00100000));
		GPIO_ClearValue(PORT2,(0b11010000));
	}if(auxSystick==3){
		GPIO_SetValue(PORT2,(0b01000000));
		GPIO_ClearValue(PORT2,(0b10110000));
	}if(auxSystick==4){
		GPIO_SetValue(PORT2,(0b10000000));
		GPIO_ClearValue(PORT2,(0b01110000));
		auxSystick=0;
	}
return;}
void SysTick_Handler(void){
	//RedLedTooglerBlinker();
	//rotarNibbles();
return;}
void TIMER1_IRQHandler(void){
	TIM_ClearIntPending(LPC_TIM1,TIM_MR0_INT);
	//RedLedTooglerBlinker();
	//rotarNibbles();

return;}

