/*
 * File:   INIT_CONFIG.c
 * Author: Jefferson
 *
 * Created on 29 de Dezembro de 2021, 11:52
 */

#include <avr/io.h>           //Biblioteca geral dos AVR
#include <avr/interrupt.h>    //Biblioteca de interrupção

/*======================================================================================
 * 
 * tempo = X_bit_timer * Prescaler/Fosc
 * tempo =65536 * Prescaler/Fosc = 65536 * 1024/16000000 = 4, 19s
 * 
 * Valor inicial de contagem = X_bit_timer - tempo_desejado*Fosc/Prescaler 
 * Valor inicial de contagem = 256 - tempo_desejado*Fosc/Prescaler 
 *
 ======================================================================================*/

void INIT_timer()
{
    TCNT0  = 56;            // Recarrega o Timer_0 para que a contagem seja 100us novamente
    TCCR0B = 0b00000010;    // TC0 com prescaler de 8, a 16 MHz gera uma interrupção a cada 100us 
    TIMSK0 = 0b00000001;    // habilita a interrupção do TC0

    TCCR1A = 0xA3; //Configura operação em fast PWM, utilizando registradores OCR1x para comparação
  
}

void INIT_hardware()
{
    /* 0000 1111 */
    
    MCUCR &= 0xef;          /* habilita pull up quando configurado e desabilita algumas configurações prévias do MCU */
    
    DDRB  = 0b00110110;     /* Habilita PB0 como entrada e PB5, PB1 e PB2 como saída */
    PORTB = 0x00;
    DDRC  = 0b11111111;
    PORTC = 0b10000000;     /* Inicia o port_C desligado e RESET desabilitado */
    DDRD  = 0b00001110;
    PORTD = 0x11;

}

void INIT_intext()
{
    PCICR  = 0b00000100;    //hab. interrupção por mudança de sinal no PORTD
    PCMSK2 = 0b00010000;    //hab. os pinos PCINT10 e PCINT11 para gerar interrupção
}
