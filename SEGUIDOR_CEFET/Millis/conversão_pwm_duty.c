/* ============================================================================
   
    Título da Aula: Vetores
    
    Autor: Jefferson Henrique
    Data:  15/01/2022

============================================================================ */


/* ========================================================================= */
/* --- Bibliotecas --- */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>                              /* para trabalhar com acentuação */

/* ========================================================================= */
/* --- Pré-compilação --- */



/* ========================================================================= */
/* --- Declaração de funções --- */

char calc_duty(int  pwm);
int  calc_pwm (char duty_cycle, int pwm);

/* ========================================================================= */
/* --- Declaração de variaveis --- */



/* ========================================================================= */
/* --- Função Principal --- */

int main() 
{
	
	char duty_cycle = 0;
	int  pwm = 0;
			
	printf("Valor do PWM: %d", calc_pwm(duty_cycle, pwm));
	
	printf("\n\n");
		
	system("PAUSE");
	
	return 0;
	
} /* end main */

int calc_pwm(char duty_cycle, int pwm)
{
	
	printf("Insira um valor de duty_cycle: ");
	 scanf("%d", &duty_cycle);
	
	printf("\n");
	
	if(duty_cycle <   0) calc_pwm(duty_cycle, pwm);
	
	else if(duty_cycle > 100)
	{
		duty_cycle = 100;
		printf("Valor de duty_cycle corrigido para: %d\n\n", duty_cycle);	
	} 
			
	return duty_cycle*10;
	
} /* end calc_pwm */

char calc_duty(int pwm)
{
	
	printf("Insira um valor de PWM: ");
	 scanf("%d", &pwm);
	
	printf("\n");
	
	if(pwm < 0) calc_duty(pwm);
	
	else if(pwm > 1000)
	{
		pwm = 1000;
		printf("Valor de PWM corrigido para: %d", pwm);	
	} 
	
	printf("Convertendo ..\n");
	printf("Convertendo ..\n");
	printf("Convertendo ..\n");
	
	printf("Valor de duty_cycle: %d", pwm/10);
	printf("\n\n");
	
	system("PAUSE");
	system("CLS");
	
	calc_duty(pwm);
	
} /* end calc_duty */

/* ============================================================================  
                                                              
                                       _                      
                                      / \                     
                                     |oo >                    
                                     _\=/_                    
                    ___         #   /  _  \   #               
                   /<> \         \\//|/.\|\\//                
                 _|_____|_        \/  \_/  \/                 
                | | === | |          |\ /|                    
                |_|  0  |_|          \_ _/                    
                 ||  0  ||           | | |                    
                 ||__*__||           | | |                    
                |* \___/ *|          []|[]                    
                /=\ /=\ /=\          | | |                    
________________[_]_[_]_[_]_________/_]_[_\_______________________________
                                                              
                                                              
============================================================================ */
/* --- Final do Programa --- */
