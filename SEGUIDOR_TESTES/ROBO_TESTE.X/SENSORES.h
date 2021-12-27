/*
 * DESCRIÇÃO: BIBLIOTECA PARA TRATAMENTO DOS SENSORES DO ROBÔ SEGUIDOR DE LINHA
 * FILE: SENSORES.h
 * AUTOR: Jefferson Henrique
 *
 * Created on 02 de Dezembro de 2021, 20:59
 */

#include <avr/io.h>           //Biblioteca geral dos AVR

//variáveis de comando para os registradores
#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

//DECLARACAO DE MASCARAS
#define SB_0  (tst_bit(PINC, PC0))
#define SB_1  (tst_bit(PINC, PC1))
#define SB_2  (tst_bit(PINC, PC2))
#define SB_3  (tst_bit(PINC, PC3))
#define SB_4  (tst_bit(PINC, PC4))
#define SB_5  (tst_bit(PINC, PC5))

#define SP_0  (!tst_bit(PINC, PC0))
#define SP_1  (!tst_bit(PINC, PC1))
#define SP_2  (!tst_bit(PINC, PC2))
#define SP_3  (!tst_bit(PINC, PC3))
#define SP_4  (!tst_bit(PINC, PC4))
#define SP_5  (!tst_bit(PINC, PC5))

//DECLARACAO DE VARIAVEIS
char f_sensor = 0;
char v_sensor[6];
//DECLARAÇÃO DE FUNÇÕES
void maq_sensor();
void rotina_sensor();

void maq_sensor() // FAZ COM QUE OS SENSORES SEJAM OPERAVEIS
{    
    if(!f_sensor) /*primeira leitura*/ 
    {       
            // SENSOR COMO SAÍDA 
            /*set_bit(DDRC , PC0); 
            set_bit(PORTC, PC0);
            _delay_us(10);
            clr_bit(PORTC, PC0);
            // SENSOR COMO ENTRADA 
            clr_bit(DDRC , PC0);
            set_bit(PORTC, PC0);*/

            // SENSOR COMO SAÍDA
            DDRC  = 0b01111111; // Define PORTC como saida
            PORTC = 0b01111111; // Define PORTC como saida = ON
            _delay_us(10);
            PORTC = 0b00000000; // Define PORTC como saida = OFF
            // SENSOR COMO ENTRADA
            DDRC  = 0b00000000; // Define PORTC como entrada
            PORTC = 0b01111111; // Define PORTC como entrada = c/Pull-up
    }
    
} /*END maq_sensor*/

void rotina_sensor(char sensor[6]) // Funcao que testa os sensores
{   
    f_sensor = 1;
    
    /*if(SB_0)
    {
        set_bit(PORTB, PB5);
        f_sensor = 0;
    }
    else if(SP_0)
    {
        clr_bit(PORTB, PB5);
        f_sensor = 0;
    }*/
       
    if(SB_0 || SB_1 || SB_2 || SB_3 || SB_4 || SB_5) // -- branco  == 0
    {
        set_bit(PORTB, PB5); // Sinaliza leitura
        
        if(SB_0 && !SP_0)
        {
            sensor[0] = 1;
        }
        if(SB_1 && !SP_1)
        {
            sensor[1] = 1;
        }
        if(SB_2 && !SP_2)
        {
            sensor[2] = 1;
        }
        if(SB_3 && !SP_3)
        {
            sensor[3] = 1;
        }
        if(SB_4 && !SP_4)
        {
            sensor[4] = 1;
        }
        if(SB_5 && !SP_5)
        {
            sensor[5] = 1;
        }
        
        f_sensor = 0;
    }
    
    else if(SP_0 || SP_1 || SP_2 || SP_3 || SP_4 || SP_5) // -- preto   == 1
    {
        clr_bit(PORTB, PB5);
        
        if(!SB_0 && SP_0)
        {
            sensor[0] = 0;
        }
        if(!SB_1 && SP_1)
        {
            sensor[1] = 0;
        }
        if(!SB_2 && SP_2)
        {
            sensor[2] = 0;
        }
        if(!SB_3 && SP_3)
        {
            sensor[3] = 0;
        }
        if(!SB_4 && SP_4)
        {
            sensor[4] = 0;
        }
        if(!SB_5 && SP_5)
        {
            sensor[5] = 0;
        }
        
        f_sensor = 0;
    }       
    //void UART_enviaString(char *s) //configurar a UART para ler os sensores
    
} /*END rotina_sensor*/
