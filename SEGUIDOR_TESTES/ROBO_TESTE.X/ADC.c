/*
 * File:   ADC.c
 * Author: Jefferson
 *
 * Created on 29 de Dezembro de 2021, 11:37
 */

#include <avr/io.h> //Biblioteca geral dos AVR
#include "ADC.h"    //Biblioteca de conversao AD

void inicializa_ADC(void){
    
    //Habilita a referencia de tensao interna do ADC e ativa o canal 0
    ADMUX = (1<<REFS0);                   
    
    //Habilita o ADC e configura o prescaler para 128
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
    
}   /*end inicializa_adc*/

unsigned int le_ADC(unsigned char canal){
    
    canal = canal & 0b00001111;
    ADMUX = (ADMUX & 0xF0) | canal; 

    //Inicia a conversÃ£o
    ADCSRA |= (1 << ADSC);

    //Aguarda a finalizaÃ§Ã£o da conversÃ£o
    while ( (ADCSRA & (1<<ADSC)));
    
    //Retorna o valor convertido
    return ( ADC ); 
    
}   /*end le_ADC*/

void ADC_init (void) {
    
    /*
     * Freq_ADC = 1MHz
     * Timer_ADC = 1/1MHz = 1us
     * Primeira Conversão = 25*1 = 25us
     * Demais conversões = 14*1 = 14us
     * Tempo total do prieiro ciclo = (25*1) + (14*1*5) = 95us
     * Tempo das demais conversões = 14*1*6 = 84us
     * Utilizando teoria de amostragem -> 168->190us
     */

    
    ADMUX = 0x40; //0100-0000   //Referência no AVCC
    ADCSRA = 0x8c; //1000-1100  //ADC habilitado, interrupção do AD habilitado e prescaler de 16 - 1MHz
    ADCSRB = 0x00; // 0000-0000 //Modo livre
    DIDR0 = 0x3f;// 0011-1111   //Desabilita a entrada digital desses terminais
 
    /* Atenção. Segundo o datasheet quanto maior a velocidade,
     * menor a precisão do AD, logo, utilizar 8bits em freq. elevadas
     */
    
}   /*end ADC_init*/

void ADC_conv_ch (unsigned char canal) {
    
    ADMUX &= 0xf0;
    ADMUX |= (canal & 0x0f);
    
    ADCSRA |= 0x40;
            
}   /*end ADC_conv_ch*/

unsigned char ADC_ler () {
    
    /*int dado = ADCL;
    dado |= ADCH << 8;
    return dado;*/
    return ADCL;
    
}   /*end ADC_ler*/
