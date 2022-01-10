/*
 * File:   ROBO_TESTE.h
 * Author: Jefferson
 *
 * Created on 29 de Dezembro de 2021, 11:33
 */

/*======================================================================================*/
/* Bibliotecas e frequência do uc*/

#define F_CPU 16000000        //define a frequencia do uC para 16MHz
#include <stdio.h>
#include <avr/io.h>           //Biblioteca geral dos AVR
#include <avr/interrupt.h>    //Biblioteca de interrupção
#include <util/delay.h>       //Biblioteca geradora de atraso
#include <stdbool.h>          //Biblioteca que permite utilizar variável booleana
#include "PWM.h"              //Biblioteca de PWM fast mode de 10 bits
#include "MOTORES.h"          //Biblioteca para controle dos motores
#include "UART.h"
#include "INIT_CONFIG.h"      //Biblioteca para inicializar configurações do uC
#include "SENSORES.h"         //Biblioteca dos sensores
#include "PID.h"              //Biblioteca de controle 

/*======================================================================================*/
/* Mascaras de comando para os registradores */

#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

/*======================================================================================*/
//DECLARACAO DE FUNCOES

void f_timers();    // Função base para temporização das rotinas com base no Timer_0