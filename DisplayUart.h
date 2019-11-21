/*
 * DisplayUart.h
 *
 *  Created on: 11 de nov. de 2019
 *      Author: Icomp2015
 */

#ifndef DISPLAYUART_H_
#define DISPLAYUART_H_

#include "LPC17xx.h"
#define SIZE 3
//#include "lpc17xx_uart.h"
void confPinsDisplayUart(void);
void confUart(void);
void UART_IntTransmit(void);
void confTimerDisplayUart(void);
void enviarUART(void);
void setMessage(uint8_t[SIZE]);
void setCharInMessage(uint8_t,uint8_t);
void updateCharPass(uint8_t);

#endif /* DISPLAYUART_H_ */
