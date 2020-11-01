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
    printf("ingresa el largo de la cadena \n"); //se pide al usuario el espacio a reservar para la cadena
    scanf("%d",&n);
    fra= (char*)malloc(n*sizeof(char)); //arreglo dinamico
    iniciar(fra,n);                         //funcion que inicializa con (*) toda la cadena de n valor
    printf("ingresa la cadena \n");
    fflush(stdin); 
    scanf("%s",fra);          //cuando se ingresa la cadena se borran los (*) usados al inicio de la cadena y se sustituyen por lo que se escribió
    for(i=0;i<n;i++)
    {
        printf("%c",fra[i]);    //imprime los caracteres
    }
    return 0;
}

void iniciar(char *fra,int n) //funcion para rellenar con (*)
{
    int i;
    for(i=0;i<n;i++)
    {
        fra[i]='*';
    }
}
