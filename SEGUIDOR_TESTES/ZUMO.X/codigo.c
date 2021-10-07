#define led  LATC0_bit
#define sw  RB7_bit


unsigned int timer=0;//variable acumula contador del sensor

//pines sesnores

int sentores_in  [6];
int sensores_out [6];
#define s1_out  LATA0_bit
#define s1_in  RA0_bit
#define s2_out  LATA1_bit
#define s2_in  RA1_bit
#define s3_out  LATA2_bit
#define s3_in  RA2_bit
#define s4_out  LATA3_bit
#define s4_in  RA3_bit
#define s5_out  LATA4_bit
#define s5_in  RA4_bit
#define s6_out  LATA5_bit
#define s6_in  RA5_bit

// configuracion de los tris
#define s1_dir  TRISA0_bit
#define s2_dir  TRISA1_bit
#define s3_dir  TRISA2_bit
#define s4_dir  TRISA3_bit
#define s5_dir  TRISA4_bit
#define s6_dir  TRISA5_bit


//banderas de la lectura de los sensores
char banderas=0;
#define flag_s1  banderas.b0
#define flag_s2  banderas.b1
#define flag_s3  banderas.b2
#define flag_s4   banderas.b3
#define flag_s5   banderas.b4
#define flag_s6   banderas.b5



// pin giro motor
#define m1_g LATB3_bit
#define m2_g LATB4_bit

#define m1_g_dir TRISB3_bit
#define m2_g_dir TRISB4_bit


//leds infrarijos
#define leds LATB2_bit
#define leds_dir TRISB2_bit


char texto[200];


//Almacena el valor de la Lectura
unsigned int lecturas[8];// Lectura actual
//limites
unsigned int minimos[]={65535,65535,65535,65535,65535,65535,65535,65535}; //Lectura minima   inicia con un valor alto
unsigned int maximos[]={0,0,0,0,0,0,0,0}; // Lectura de maximo  inicia con un valor bajo
unsigned int normalizados[8]; // Lectura normalizadas de 0 a 1




//configuracion del timer >=5ms
void config_timer1 ()
{
T1CON=0;
//5 Milisegundo
TMR1H=236;
TMR1L=120;
//preescalador uno
T1CKPS1_bit=0;
T1CKPS0_bit=0;

TMR1IF_bit=0;
TMR1ON_bit=0;
}

//realiza la lectura actual de los sesnores


void config_salidas()//salida todos los sensores
{
  s1_dir=0;
  s2_dir=0;
  s3_dir=0;
  s4_dir=0;
  s5_dir=0;
  s6_dir=0;
}


void config_entradas()//entrada todos los sensores
{
  s1_dir=1;
  s2_dir=1;
  s3_dir=1;
  s4_dir=1;
  s5_dir=1;
  s6_dir=1;
}

//para sacar un uno en todo los sebsores
void saca_uno()
{
s1_out=1;
s2_out=1;
s3_out=1;
s4_out=1;
s5_out=1;
s6_out=1;
}

void analizasensoresir()
{
  char cuenta1;
  config_timer1();
  leds=1;// enciende la regleta d elos leds
  config_salidas();
  saca_uno();
  Delay_us(10);
  config_entradas();
  TMR1ON_bit=1; //prende el timer

//Limpia la lectura de los sensores

  for (cuenta1=0;cuenta1<=8;cuenta1++)  lecturas[cuenta1]=0;
  banderas=0;    //limpi las bandera de los sesnores

  while (TMR1IF_bit==0)
  {

  // detecta si ta calló la señal del sensor1
    if ((s1_in==0) && ( flag_s1==0))
    {
     lecturas[0]=(unsigned int)TMR1H<<8 |TMR1L;
     flag_s1=1;
    }

  // detecta si ta calló la señal del sensor2
    if ((s2_in==0) && ( flag_s2==0))
    {
     lecturas[1]=(unsigned int)TMR1H<<8 |TMR1L;
     flag_s2=1;
    }

     // detecta si ta calló la señal del sensor3
    if ((s3_in==0) && ( flag_s3==0))
    {
     lecturas[2]=(unsigned int)TMR1H<<8 |TMR1L;
     flag_s3=1;
    }

    // detecta si ta calló la señal del sensor4
    if ((s4_in==0) && ( flag_s4==0))
    {
     lecturas[3]=(unsigned int)TMR1H<<8 |TMR1L;
     flag_s4=1;
    }

     // detecta si ta calló la señal del sensor5
    if ((s5_in==0) && ( flag_s5==0))
    {
     lecturas[4]=(unsigned int)TMR1H<<8 |TMR1L;
     flag_s5=1;
    }

    // detecta si ta calló la señal del sensor6

    if ((s6_in==0) && ( flag_s6==0))
    {
     lecturas[5]=(unsigned int)TMR1H<<8 |TMR1L;
     flag_s6=1;
    }
  } // fin del tiempo para leeer los sensores
   // apaga la reglet d elos leds para ahorrar bateria
    leds=0;//

}

void manda_sensores_ir()
{
  sprintf(texto,"s1=%u   s2=%u  s3=%u   s4=%u   s5=%u   s6=%u\r\n\r\n",lecturas[0],lecturas[1],lecturas[2],lecturas[3],lecturas[4],lecturas[5]);
   UART1_Write_Text(texto);

}


void adelante(unsigned char velo)
{
m1_g=0;
m2_g=0;
PWM1_Set_Duty(velo);
PWM2_Set_Duty(velo);
}


void atras(unsigned char velo)
{
m1_g=1;
m2_g=1;
PWM1_Set_Duty(velo);
PWM2_Set_Duty(velo);
}


void derecha(unsigned char velo)
{
m1_g=1;
m2_g=0;
PWM1_Set_Duty(velo);
PWM2_Set_Duty(velo);
}


void izquierda(unsigned char velo)
{
m1_g=0;
m2_g=1;
PWM1_Set_Duty(velo);
PWM2_Set_Duty(velo);
}

void quieto()
{
PWM1_Set_Duty(0);
PWM2_Set_Duty(0);
}   void calibra_ir()
{
unsigned int cuenta2;
char cont;
led=0;
     //toma 200 muestras del terreno  para calibrar los sensores
    for (cuenta2=0; cuenta2<=200;cuenta2++)
    {
    for (cont=0; cont<6;cont++)
        {
           analizasensoresir();
           if (lecturas[cont]>=maximos[cont]) maximos[cont]=lecturas[cont];
           if (lecturas[cont]<=minimos[cont]) minimos[cont]=lecturas[cont];
        }  //
    } //fin for cuenta
     led=1;
     Delay_ms(500);
     led=0;

 }

 void manda_limites()
 {
   sprintf(texto,"min1=%u   min2=%u  min3=%u   min4=%u   min5=%u   min6=%u\r\n",minimos[0],minimos[1],minimos[2],minimos[3],minimos[4],minimos[5]);
   UART1_Write_Text(texto);
   sprintf(texto,"max1=%u   max2=%u  max3=%u   max4=%u   max5=%u   max6=%u\r\n\r\n",maximos[0],maximos[1],maximos[2],maximos[3],maximos[4],maximos[5]);
   UART1_Write_Text(texto);


 }


 // normaliza el valor leido en un ranfo en este caso de 0 a 1
 void normaliza()
 {
   unsigned char cuenta;
   float min_temp,max_temp;
   float promedio;


   for (cuenta=0;cuenta<6;cuenta++)
   {
    min_temp=minimos[cuenta];
    max_temp=maximos[cuenta];
    promedio=(max_temp-min_temp)/2;  // calcual la diferencia entre el maximo y minimo del sensor correspondiente
     if (lecturas[cuenta]>=(min_temp+promedio))  normalizados[cuenta]=1;
     else  normalizados[cuenta]=0;

   } // fin del for cuenta


 }



 void manda_normalizados()
 {
    sprinti(texto,"s1=%u   s2=%u  s3=%u   s4=%u   s5=%u   s6=%u\r\n\r\n",normalizados[0],normalizados[1],normalizados[2],normalizados[3],normalizados[4],normalizados[5]);
   UART1_Write_Text(texto);
 }




void main() 
{
// TODO DIGITAL;
ANSELA=0;
ANSELB=0;
ANSELC=0;

 // salidas PWM
   TRISC1_bit=0;
   TRISC2_bit=0;
  //PINES DE GIRO MOTOR
  m1_g_dir=0;
  m2_g_dir=0;
  // salida leds infrarojo
  leds_dir=0;


    //SALIDA LED normal
    TRISC0_bit=0;

    //entrada pulsador
    TRISB7_bit=1;
  // pull up
  NOT_RBPU_bit=0;


 UART1_Init(9600);
 UART1_Write_Text("INICIANDO\r\n");

 PWM1_Init(250);
 PWM2_Init(250);
 // arrancan quieto
 PWM1_Set_Duty(0);
 PWM2_Set_Duty(0);
 PWM1_Start();
 PWM2_Start();
 
calibra_ir();
manda_limites();

while (sw==1);


while (1)
{
 analizasensoresir();
normaliza();
manda_normalizados();

//manda_sensores_ir();
 led=!led;
 Delay_ms(1000);
 

}


}