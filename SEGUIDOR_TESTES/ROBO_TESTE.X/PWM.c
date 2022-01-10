/*
 * File:   PWM.c
 * Author: Jefferson
 *
 * Created on 29 de Dezembro de 2021, 11:33
 */

#include <avr/io.h>           //Biblioteca geral dos AVR

void setDuty_R(int duty) //Motor_direito
{

    OCR1B = duty; //registrador de PWM do OC1B

} //end setDuty

void setDuty_L(int duty) // Motor_esquerdo
{

    OCR1A = duty; //valores de 0 - 1023

} //end setDuty

void setFreq(char option) // Determina a frequ�ncia de atuacao do PWM dos motores
{
    /*
    TABLE:
  
        option  frequency (as frequ�ncias no timer 1 s�o menores do que as frequ�ncias nos timers 0 e 2)
        
          1      16    kHz
          2       2    kHz
          3     250     Hz
          4     62,5    Hz
          5     15,6    Hz
     */
    TCCR1B = option;

} //end setFrequency
