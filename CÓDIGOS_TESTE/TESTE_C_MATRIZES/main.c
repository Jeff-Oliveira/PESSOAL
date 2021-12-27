#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void att_valores();
void maq_matriz();

int main() 
{
	while(1)
	{
		att_ponteiros();
		maq_matriz();
	}
								
	return 0;
	
}

void att_valores()
{
	
	int f_ponteiro_1 = 2;
		 
	int *ponteiro_1 = &f_ponteiro_1; // passo o valor 2 para o ponteiro " *ponteiro_1 "
	
}

void maq_matriz(int *ponteiro_1)
{
	
	int	numero, valor,
		i, j;		
		
	int matriz[100][100]; /*{{1, 2, 3},
						     {4, 5, 6},
					 	     {7, 8, 9}};*/	
	
	printf("Selecione uma linha: ");
	scanf("%d", &i);
	printf("\nSelecione uma coluna: ");
	scanf("%d", &j);
	
	printf("\nDigite um valor: ");
	scanf("%d", &valor);
	
	matriz[i][j] = valor;
	
	//*ponteiro = *ponteiro + matriz[i][j];
	
	//printf("\nO valor da linha %d | Coluna %d = %d", i+1, j+1, ponteiro);
	
}

