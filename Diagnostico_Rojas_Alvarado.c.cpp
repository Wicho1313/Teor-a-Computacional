/*Rojas Alvarado Luis Enrique*/
/*22 de Agosto de 2018*/
/*Programa que lea una frase de n tamaño y los espacios restantes rellenarlos con asteriscos(*) */
/*No aceta espacios :'( */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void iniciar(char*, int n);

int main(void)
{
    int n,i;
    char *fra;
    printf("ingresa el largo de la cadena \n");
    scanf("%d",&n);
    fra= (char*)malloc(n*sizeof(char));
    iniciar(fra,n);
    printf("ingresa la cadena \n");
    fflush(stdin);
    scanf("%s",fra);
    for(int i=0;i<n;i++)
    {
        printf("%c",fra[i]);
    }
    return 0;
}

void iniciar(char *fra,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        fra[i]='*';
    }
}
