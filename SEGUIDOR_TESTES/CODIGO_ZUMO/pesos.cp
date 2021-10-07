#line 1 "C:/Users/Alcides Ramos/Desktop/Velocista/Canal/Pesos/pesos.c"




unsigned int timer=0;
#line 31 "C:/Users/Alcides Ramos/Desktop/Velocista/Canal/Pesos/pesos.c"
char banderas=0;
#line 54 "C:/Users/Alcides Ramos/Desktop/Velocista/Canal/Pesos/pesos.c"
char texto[200];



unsigned int lecturas[8];

unsigned int minimos[]={65535,65535,65535,65535,65535,65535,65535,65535};
unsigned int maximos[]={0,0,0,0,0,0,0,0};
unsigned int normalizados[8];





void config_timer1 ()
{
T1CON=0;

TMR1H=236;
TMR1L=120;

T1CKPS1_bit=0;
T1CKPS0_bit=0;

TMR1IF_bit=0;
TMR1ON_bit=0;
}




void config_salidas()
{
  TRISA0_bit =0;
  TRISA1_bit =0;
  TRISA2_bit =0;
  TRISA3_bit =0;
  TRISA4_bit =0;
  TRISA5_bit =0;
}


void config_entradas()
{
  TRISA0_bit =1;
  TRISA1_bit =1;
  TRISA2_bit =1;
  TRISA3_bit =1;
  TRISA4_bit =1;
  TRISA5_bit =1;
}


void saca_uno()
{
 LATA0_bit =1;
 LATA1_bit =1;
 LATA2_bit =1;
 LATA3_bit =1;
 LATA4_bit =1;
 LATA5_bit =1;
}

void analizasensoresir()
{
 char cuenta1;
 config_timer1();
  LATB2_bit =1;
 config_salidas();
 saca_uno();
 Delay_us(10);
 config_entradas();
 TMR1ON_bit=1;



 for (cuenta1=0;cuenta1<=8;cuenta1++) lecturas[cuenta1]=0;
 banderas=0;

 while (TMR1IF_bit==0)
 {


 if (( RA0_bit ==0) && (  banderas.b0 ==0))
 {
 lecturas[0]=(unsigned int)TMR1H<<8 |TMR1L;
  banderas.b0 =1;
 }


 if (( RA1_bit ==0) && (  banderas.b1 ==0))
 {
 lecturas[1]=(unsigned int)TMR1H<<8 |TMR1L;
  banderas.b1 =1;
 }


 if (( RA2_bit ==0) && (  banderas.b2 ==0))
 {
 lecturas[2]=(unsigned int)TMR1H<<8 |TMR1L;
  banderas.b2 =1;
 }


 if (( RA3_bit ==0) && (  banderas.b3 ==0))
 {
 lecturas[3]=(unsigned int)TMR1H<<8 |TMR1L;
  banderas.b3 =1;
 }


 if (( RA4_bit ==0) && (  banderas.b4 ==0))
 {
 lecturas[4]=(unsigned int)TMR1H<<8 |TMR1L;
  banderas.b4 =1;
 }



 if (( RA5_bit ==0) && (  banderas.b5 ==0))
 {
 lecturas[5]=(unsigned int)TMR1H<<8 |TMR1L;
  banderas.b5 =1;
 }
 }

  LATB2_bit =0;

}

void manda_sensores_ir()
{
 sprintf(texto,"s1=%u   s2=%u  s3=%u   s4=%u   s5=%u   s6=%u\r\n\r\n",lecturas[0],lecturas[1],lecturas[2],lecturas[3],lecturas[4],lecturas[5]);
 UART1_Write_Text(texto);

}


void adelante(unsigned char velo)
{
 LATB3_bit =0;
 LATB4_bit =0;
PWM1_Set_Duty(velo);
PWM2_Set_Duty(velo);
}


void atras(unsigned char velo)
{
 LATB3_bit =1;
 LATB4_bit =1;
PWM1_Set_Duty(velo);
PWM2_Set_Duty(velo);
}


void derecha(unsigned char velo)
{
 LATB3_bit =1;
 LATB4_bit =0;
PWM1_Set_Duty(velo);
PWM2_Set_Duty(velo);
}


void izquierda(unsigned char velo)
{
 LATB3_bit =0;
 LATB4_bit =1;
PWM1_Set_Duty(velo);
PWM2_Set_Duty(velo);
}

void quieto()
{
PWM1_Set_Duty(0);
PWM2_Set_Duty(0);
} void calibra_ir()
{
unsigned int cuenta2;
char cont;
 LATC0_bit =0;

 for (cuenta2=0; cuenta2<=200;cuenta2++)
 {
 for (cont=0; cont<6;cont++)
 {
 analizasensoresir();
 if (lecturas[cont]>=maximos[cont]) maximos[cont]=lecturas[cont];
 if (lecturas[cont]<=minimos[cont]) minimos[cont]=lecturas[cont];
 }
 }
  LATC0_bit =1;
 Delay_ms(500);
  LATC0_bit =0;

 }

 void manda_limites()
 {
 sprintf(texto,"min1=%u   min2=%u  min3=%u   min4=%u   min5=%u   min6=%u\r\n",minimos[0],minimos[1],minimos[2],minimos[3],minimos[4],minimos[5]);
 UART1_Write_Text(texto);
 sprintf(texto,"max1=%u   max2=%u  max3=%u   max4=%u   max5=%u   max6=%u\r\n\r\n",maximos[0],maximos[1],maximos[2],maximos[3],maximos[4],maximos[5]);
 UART1_Write_Text(texto);


 }



 void normaliza()
 {
 unsigned char cuenta;
 float min_temp,max_temp;
 float promedio;


 for (cuenta=0;cuenta<6;cuenta++)
 {
 min_temp=minimos[cuenta];
 max_temp=maximos[cuenta];
 promedio=(max_temp-min_temp)/2;
 if (lecturas[cuenta]>=(min_temp+promedio)) normalizados[cuenta]=1;
 else normalizados[cuenta]=0;

 }


 }



 void manda_normalizados()
 {
 sprinti(texto,"s1=%u   s2=%u  s3=%u   s4=%u   s5=%u   s6=%u\r\n\r\n",normalizados[0],normalizados[1],normalizados[2],normalizados[3],normalizados[4],normalizados[5]);
 UART1_Write_Text(texto);
 }




void main()
{

ANSELA=0;
ANSELB=0;
ANSELC=0;


 TRISC1_bit=0;
 TRISC2_bit=0;

  TRISB3_bit =0;
  TRISB4_bit =0;

  TRISB2_bit =0;



 TRISC0_bit=0;


 TRISB7_bit=1;

 NOT_RBPU_bit=0;


 UART1_Init(9600);
 UART1_Write_Text("INICIANDO\r\n");

 PWM1_Init(250);
 PWM2_Init(250);

 PWM1_Set_Duty(0);
 PWM2_Set_Duty(0);
 PWM1_Start();
 PWM2_Start();

calibra_ir();
manda_limites();

while ( RB7_bit ==1);


while (1)
{
 analizasensoresir();
normaliza();
manda_normalizados();


  LATC0_bit =! LATC0_bit ;
 Delay_ms(1000);


}


}
