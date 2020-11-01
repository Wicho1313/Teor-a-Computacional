#include <stdio.h>
#include <string.h>
#include <conio.h>
int validar_tam(char grupo[]){
	int i=0;
	while (grupo[i]!='\0'){
		i++;
	}
	return i;
}
void validar_grupo(char grupo[]){
	int i;
	for(i=0;i<=validar_tam(grupo);i++){
		printf("%c",grupo);
	}
	
}
#define MAX_CARACTERES 6
int main (){
	char grupo[MAX_CARACTERES]={'\0'};
	char mat[3]={'C','M'};
	char ves[3]={'C','V'};
	printf("\tRecuerde que su cadena debe ser de maximo %d\n",MAX_CARACTERES-1);
	printf("\nIngrese su grupo: \n");
	scanf("%c",grupo);
	//printf("La cadena que ingresaste fue: %s", grupo);
	validar_grupo(grupo);
	//strcat(mat,ves);
	//sprintf(frase,"%s",palabra);
	validar_grupo(grupo);
	getch();
	return 0;
}


