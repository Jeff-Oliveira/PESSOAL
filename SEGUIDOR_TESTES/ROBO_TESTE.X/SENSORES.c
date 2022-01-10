/*
 * File:   SENSORES.c
 * Author: Jefferson
 *
 * Created on 29 de Dezembro de 2021, 11:54
 */

#include "SENSORES.h"

//variáveis de comando para os registradores
#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

//DECLARACAO DE MASCARAS



//DECLARACAO DE VARIAVEIS

static bool f_sensor = 0;

//DECLARAÇÃO DE FUNÇÕES



void maq_sensor() // FAZ COM QUE OS SENSORES SEJAM OPERAVEIS
{    
    if(!f_sensor) /*primeira leitura*/ 
    {       
        
        // SENSOR COMO SAÍDA 
        set_bit(DDRC , PC0); 
        set_bit(PORTC, PC0);
        _delay_ms(100);
        clr_bit(PORTC, PC0);
        // SENSOR COMO ENTRADA 
        clr_bit(DDRC , PC0);
        set_bit(PORTC, PC0); 
       
    }
    
} /*END maq_sensor*/

void rotina_sensor() // Funcao que testa os sensores
{   
    f_sensor = 1;
    
    if(tst_bit(PORTC, PC0))
    {
        set_bit(PORTB, PB5);
        f_sensor = 0;
    }
    if(!tst_bit(PORTC, PC0))
    {
        clr_bit(PORTB, PB5);
        f_sensor = 0;
    }
       
} /*END rotina_sensor*/
