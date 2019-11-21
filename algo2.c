#include "Buzzer.h"
#include "LDR.h"
#include "lcd2004.h"
#include "Keypad.h"
#include "DisplayUART.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "Historial.h"

void confPinsGPIO(void);
void confPINS(void);
void confPeripherals(void);
void confTimers(void);
int main(void){
//	uint8_t mensaje[32] = "ABCDEFGHIJKLMN\n\r";
	//confRTC();
	confPinsGPIO();
	confPINS();
	confPeripherals();
	confTimers();
	//TIM_Cmd(LPC_TIM2,ENABLE);
   while(1){

   }
return 0 ;}
/*	@brief: Pins configurados :
 * 		P0.2 UART (RXD0)
 * 		P0.3 UART (TXD0)
 *		P0.23 ADC (AD0.0)
 *		P0.26 DAC (AOUT)
 *		P2.(0-7) TECLADO (GPIOs)
 *		PX.X LED NOCTURNO (GPIO)
 *
 *
 */
void confPINS(){
	confPinsGPIO();
	confPinDAC();
	confPinADC();
	confPinsDisplayUart();
	confPinsKeypad();
return;}
void confPeripherals(){
	confDAC();
	confUart();
return;}
void confPinsGPIO(){
	GPIO_SetDir(0,(1<<22),1);
	GPIO_SetDir(1,(1<<18),1);
	GPIO_SetDir(1,(1<<19),1);
	GPIO_SetDir(1,(1<<20),1);
	GPIO_SetDir(1,(1<<21),1);
	GPIO_SetValue(1,(1<<19));
return;}
/* 	@brief: Timers Configurados:
 *
 * 	@should:
 * 	 1. Keypad TIM1
 * 	 2. Uart TIM0
 * 	 3. Buzzer TIM2
 * 	 4.
 *
 */
void confTimers(){
	//confSystickKeypad();
	confTimerBuzzer();
	confTimerKeypad();
	confTimerDisplayUart();
return;}
