/*Bibliotecas e frequência do uc*/
#define F_CPU 16000000        //define a frequencia do uC para 16MHz
#include <stdio.h>
#include <avr/io.h>           //Biblioteca geral dos AVR
#include <avr/interrupt.h>    //Biblioteca de interrupção
#include <util/delay.h>       //Biblioteca geradora de atraso
#include "PWM_10_bits.h"      //Biblioteca de PWM fast mode de 10 bits
#include "MOTORES.h"          //Biblioteca para controle dos motores
#include "UART.h"
#include "INIT_CONFIG.h"      //Biblioteca para inicializar configurações do uC
#include "SENSORES.h"         //Biblioteca dos sensores
#include "PID.h"              //Biblioteca de controle 

/*======================================================================================*/
// --- Mascaras de comando para os registradores
#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

// --- Leitura de sensores
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

//------------- MODOULO_POLULU ----------
char  sensor[6]; // Vetor que passa e recebe os estados dos sensores

//---------------------------------------
//DECLARACAO DE FUNCOES
void f_timers();    // Função base para temporização das rotinas com base no Timer_0

//-------------------------------------------
//VARIAVEIS GLOBAIS
unsigned char timer;
unsigned char PWM_L = 0,
              PWM_R = 0;
unsigned char valor;

//-------------------------------------------
// FLAGS
static char f_on;   // Flag que é acionada via interrupção externa e que habilita (ON) o robô

//-------------------------------------------
//VARIAVEIS DA UART
char ch;            //armazena o caracter lido
char s[] = "APERTE PARA INICIAR...\n";

//-------------------------------------------

ISR(TIMER0_OVF_vect) // interrupcao Timer_0
{ 
    
    TCNT0 = 56;    //Recarrega o Timer 0 para que a contagem seja 100us novamente
    timer++;
    f_timers();
            
} /*fim da interrupção_Timer_0*/

ISR (USART_RX_vect) // interrupcao UART
{
	    
	ch = UDR0;		//envia buffer pela serial
		
	//Envia para o computador
	UART_enviaCaractere(ch);
	
} /*fim da interrupção_UART*/

ISR(PCINT2_vect) // interrupcao externa
{ 
    if (!(PIND & (1 << 4))) /* QUANDO PD4 FOR PRA 1 */
    {        
        if(f_on)
        {
            f_on = 0;
        }
        else
        {
            f_on = 1;
        }
    }            
} /*fim da interrupção_externa*/

int main()
{
    cli();      // desabilita todas as interrupções
 
// --- AREA DE INICIALIZACAO -----------------------------------------   
    
    UART_config();          //configura a comunicação serial
    INIT_hardware();        //configura os perifericos do uC
    INIT_timer();           //configura o timer do uC
    INIT_intext();          //configura a interrupção externa
        
 //--- ENVIO DE MENSAGEM VIA UART -------------------------------------  
    
    UART_enviaString(s);    //envia a string armazenada no vetor s
    
 //--- ESCOLHA DA FREQUENCIA DO PWM -----------------------------------    
    
    setFreq(3);  
    
 //--------------------------------------------------------------------
    sei();          // habilita todas as interrupções
        
    while(1){}
   
    return 0;
    
} /*END main*/

void f_timers() // função que cria temporização para tomadas de tempo
{
    if (f_on)   //Só começa a contar a partir do momento que f_on = 1
    {
        if ((timer > 2-1))  //Aciona a cada 100us
        {
            maq_sensor();
        }
        if ((timer > 4-1))  //Aciona a cada 200us 
        {
            rotina_sensor(sensor);
            //rotina_motor(); 
            //rotina_UART(sensor);
            timer = 0;
        }
    } 
    else
    {
        motor_off();
    }
    
} /*END f_timers*/

