/*
 * Buzzer.h
 *
 *  Created on: 9 de nov. de 2019
 *      Author: Icomp2015
 *
 *  BUZZER:
 *  Frecuencia 11Hz
 *  Duty: 50%
 *  Vpp: 3.28 V.
 *  AOUT: P0.26
 */

#ifndef BUZZER_H_
#define BUZZER_H_


void confPinDAC(void);
void confDAC(void);
void soundCorrect(void);
void soundIncorrect(void);
void delayBuzzer(void);
void confTimerBuzzer(void);
void soundAlarm(void);

#endif /* BUZZER_H_ */
