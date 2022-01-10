/*
 * File:   PWM.c
 * Author: Jefferson
 *
 * Created on 29 de Dezembro de 2021, 11:33
 * 
 * PWM em fast mode de 10 bits do Timer 1 do atemga328p
 * 
 */

void setDuty_R(int duty);  // Motor_direito
void setDuty_L(int duty);  // Motor_esquerdo
void setFreq(char option); // Determina a frequência de atuacao do PWM dos motores

