/*
 * DESCRIÇÃO: BIBLIOTECA PARA TRATAMENTO DOS SENSORES DO ROBÔ SEGUIDOR DE LINHA
 * FILE: Driver_motor.h
 * AUTOR: Jefferson Henrique
 *
 * Created on 02 de Dezembro de 2021, 21:17
 */

/*======================================================================================*/

#include <avr/io.h>           //Biblioteca geral dos AVR

#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

/*== CONTROLE DO ROBO ================================================================*/
//Lado Esquerdo
#define DIR_L PD2   // HIGH == trás / LOW == frente


//Lado Direito
#define DIR_R PD3   // HIGH == trás / LOW == frente

/*======================================================================================*/

void frente()
{
    clr_bit(PORTD, DIR_L);
    clr_bit(PORTD, DIR_R);    
}

void tras()
{
    set_bit(PORTD, DIR_L);
    set_bit(PORTD, DIR_R);
}

void esquerda() 
{    
    clr_bit(PORTD, DIR_L);
    set_bit(PORTD, DIR_R);
}

void direita() 
{   
    set_bit(PORTD, DIR_L);
    clr_bit(PORTD, DIR_R);
}

void motor_off() 
{   
    setDuty_L(0);
    setDuty_R(0);   
}

void freio() 
{      
    motor_off();        //desliga os motores para deixar o próprio atrito frear o robô
    setDuty_L(0);
    setDuty_R(0);
}

void rotina_motor()
{
    esquerda();
    setDuty_L(800);
    setDuty_R(200);
}