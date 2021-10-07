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

//------------- CONTROLE ROBO ------------
#define DIR_L PD2 // 0 = frente 1 = tras
#define DIR_R PD3 // 0 = frente 1 = tras
#define ON_L  PB1
#define ON_R  PB2


//------------- MODOULO_POLULU ----------
char            f_sensor[6];
unsigned char   sensor[6];
#define S_0 PC0
#define S_1 PC1
#define S_2 PC2
#define S_3 PC3
#define S_4 PC4
#define S_5 PC5
#define LED PB4

void INIT_ROTINA();
void config_timer();
void f_timers();
//-------------------------------------------
void frente();
void tras();
void girar();
void freio();

//-------------------------------------------
//VARIAVEIS GLOBAIS
char micro;
//-------------------------------------------
char f_set_sensor;
static char converte = 0;

ISR(TIMER0_OVF_vect) // interrupcao TC0
{ 
    
    TCNT0 = 254;    //Recarrega o Timer 0 para que a contagem seja 1us novamente
    micro++;
    f_timers();
            
}

int main()
{
            
    DDRB  = 0b00000110;
    PORTB = 0x00;
    DDRC  = 0b00111111;
    PORTC = 0x3F;
    DDRD  = 0b00001110;
    PORTD = 0x00;
        
    TCNT0 = 254;            // Recarrega o Timer 0 para que a contagem seja 1us novamente
    TCCR0B = 0b00000010;    // TC0 com prescaler de 80, a 16 MHz gera uma interrupção a cada 1us 
    TIMSK0 = 0b00000001;    // habilita a interrupção do TC0
    
    setFreq(4);
    
    sei();
    
    while(1)
    {
      
    }
   
}

void INIT_ROTINA()
{
    /*set_bit(PORTB, ON_L);
    set_bit(PORTB, ON_R);
    frente();*/    
}

void frente()
{
    cpl_bit(PORTD, DIR_L);
    cpl_bit(PORTD, DIR_R);
    _delay_ms(200);
}

void freio()
{
    setDuty_1(0);
    setDuty_2(0);
}

void maq_sensores() 
{
    
    if (f_set_sensor) 
    {
        set_bit(PORTD, LED);
        DDRD = 0x00;
        PORTD = 0x3F;
        
        
        for (int i = 0; i < 6; i++)
        {
            //Limpa leitura dos sensores
            sensor[i] = 0;
            //limpa flag dos sensores
            f_sensor[i] = 0;
        }
       
        while (converte == 0) {

            // detecta sinal do sensor_0
            if ((tst_bit(PORTC, S_0) == 0) && (f_sensor[0] == 0)) {
                sensor[0] = ADC_ler(0);
                f_sensor[0] = 1;
            }

            // detecta sinal do sensor_1
            if ((tst_bit(PORTC, S_1) && (f_sensor[1] == 0)) {
                sensor[1] = ADC_ler(1);
                f_sensor[1] = 1;
            }

            // detecta sinal do sensor_2
            if ((tst_bit(PORTC, S_2) && (f_sensor[2] == 0)) {
                sensor[2] = ADC_ler(2);
                f_sensor[2] = 1;
            }

            // detecta sinal do sensor_3
            if ((tst_bit(PORTC, S_3) && (f_sensor[3] == 0)) {
                sensor[3] = ADC_ler(3);
                f_sensor[3] = 1;
            }

            // detecta sinal do sensor_4
            if ((tst_bit(PORTC, S_4) && (f_sensor[4] == 0)) {
                sensor[4] = ADC_ler(4);
                f_sensor[4] = 1;
            }

            // detecta sinal do sensor_5

            if ((tst_bit(PORTC, S_5) && (f_sensor[5] == 0)) {
                sensor[5] = ADC_ler(5);
                f_sensor[5] = 1;
            }
        } // fim da leitura dos sensores
        // apaga led para economizar bateria e reseta a variavel
        
        clr_bit(PORTD, LED);
        
        converte = 1;
    }
    
}

void UART_enviaString(char *s) //configurar a UART para ler os sensores

void f_timers() 
{
    if (micro == 10) 
    {
        f_set_sensor++;
    }
}