/*Bibliotecas e frequência do uc*/
#define F_CPU 16000000        //define a frequencia do uC para 16MHz
#include <avr/io.h>           //Biblioteca geral dos AVR
#include <avr/interrupt.h>    //Biblioteca de interrupção
#include <util/delay.h>       //Biblioteca geradora de atraso
#include "PWM_10_bits.h"      //Biblioteca de PWM fast mode de 10 bits
/*============================================================*/

//variáveis de comando para os registradores
#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

 
#define DIR_L PD2 // 0 = frente 1 = tras
#define DIR_R PD3 // 0 = frente 1 = tras
#define ON_L  PB1
#define ON_R  PB2

void config_timer();
void frente();
void tras();
void girar();
void freio();
void INIT_ROTINA();

ISR(TIMER0_OVF_vect) // interrupcao TC0
{ 
    
    TCNT0 = 250;    //Recarrega o Timer 0 para que a contagem seja 1ms novamente
    
    INIT_ROTINA();
        
}

int main()
{
            
    DDRD  = 0b00001110;
    PORTD = 0x00;
    DDRB  = 0b00000110;
    PORTB = 0x00;
    
    TCNT0 = 250;    //Recarrega o Timer 0 para que a contagem seja 1ms novamente
    TCCR0B = 0b00000011; //TC0 com prescaler de 1024, a 16 MHz gera uma interrupção a cada 16,384 ms 
    TIMSK0 = 0b00000001; //habilita a interrupção do TC0
    
    setFreq(3);
    
    sei();
    
    while(1)
    {
      
    }
   
}

void INIT_ROTINA()
{
   
    set_bit(PORTB, ON_L);
    set_bit(PORTB, ON_R);
    
}


void freio()
{
    setDuty_1(0);
    setDuty_2(0);
}
