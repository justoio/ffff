/*
 * lcd2004.c

 *
 *  Created on: 9 de nov. de 2019
 *      Author: Icomp2015
 */
#include "LPC17xx.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
void confPinI2C(void){
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
		PinCfg.OpenDrain=PINSEL_PINMODE_OPENDRAIN;    /**< OpenDrain mode, should be:
		                        - PINSEL_PINMODE_NORMAL: Pin is in the normal (not open drain) mode
		                        - PINSEL_PINMODE_OPENDRAIN: Pin is in the open drain mode */
		PINSEL_ConfigPin(&PinCfg);
return;}
void confI2C(void){
	uint32_t clockrate=100000;
	I2C_Init(LPC_I2C0,clockrate);
	I2C_Cmd(LPC_I2C0, ENABLE);
return;}


