

void INIT_hardware()
{
    /* 0000 1111 */
    
    MCUCR &= 0xef;      /* habilita pull up quando configurado e desabilita algumas configurações prévias do MCU */
    DDRB  = 0b00000110;       /* Habilita PB0 como entrada e PB5, PB1 e PB2 como saída */
    PORTB = 0x00;
    DDRC  = 0b00111111;
    PORTC = 0x00;       /* Inicia o port_C desligado */
    DDRD  = 0b00001110;
    PORTD = 0x00;
}

void INIT_timer()
{
    TCNT0 = 254;            // Recarrega o Timer 0 para que a contagem seja 1us novamente
    TCCR0B = 0b00000010;    // TC0 com prescaler de 80, a 16 MHz gera uma interrupção a cada 1us 
    TIMSK0 = 0b00000001;    // habilita a interrupção do TC0

    TCCR1A = 0xA3; //Configura operação em fast PWM, utilizando registradores OCR1x para comparação
}