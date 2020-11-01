#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX 100
#define TRUE	1
#define FALSE	0

typedef unsigned char boolean;

typedef struct elemento{ 		
	char c;						
	float n;
}elemento;
typedef struct nodo{
	elemento e;
	struct nodo *abajo;
}nodo;
typedef struct pila{
	nodo *tope;					
}pila;
void Inicializar(pila *s){
	s -> tope = NULL;	
	return;
}
void Push(pila *s, elemento e){
	nodo *aux; 
	aux = (nodo *)malloc(sizeof(nodo));
	(*aux).e = e;
	aux -> abajo = s -> tope;
	s -> tope = aux;
	return;
}
elemento Top(pila *s){				
	return s -> tope -> e;
}
elemento Pop(pila *s){
	elemento r;	
	nodo *aux;
	r = s -> tope -> e;
	aux = s -> tope;
	s -> tope = s -> tope -> abajo;
	free(aux);
	return r;
}	
boolean Empty(pila *s){
	return (s -> tope == NULL)?TRUE:FALSE;
}

int Size(pila *s){
	int size = 0;
	nodo *aux;
	aux = s -> tope;
	while( aux != NULL){
		aux = aux -> abajo;
		size++;
	}
	return size;
}
void Destroy(pila *s){
	nodo *aux;
	while(s -> tope != NULL){
		aux = s -> tope -> abajo;
		free(s -> tope);
		s -> tope = aux;
	}
	return;
}

boolean otroProceso(){
	char sn, respuesta[20];
	printf("\n\n\t Desea introducir otra expresion ? \n escriba s para si y n para no: ");
	fflush(stdin);
	scanf("%c",&sn);
	printf("\n Usted selecciono %c \n", sn);
	return (sn == 's' || sn == 'S')?TRUE:FALSE;
}
boolean validarParentesis2(char const *cadena){
	int i;
	elemento e1;
	pila p1;
	Inicializar(&p1);
	printf("\nElimina epsilon\n");
	for(i = 0; i < strlen(cadena); i++){
		if(cadena[i] == '('){

			e1.c = cadena[i];
			Push(&p1, e1);
			printf("( S");
		}
		else if(cadena[i] == ')'){
		
			if(Empty(&p1) == FALSE){
				Pop(&p1);
				printf(" ) ");
			
			}
			else{
				printf("\n\t%i ERROR, hay mas parentesis que cierran que los que abren \n", i+1);
				return FALSE;
			}
		}
	}
	return (Empty(&p1) == TRUE)?TRUE:FALSE;
}
boolean validarParentesis(char const *cadena){
	int i;
	elemento e1;
	pila p1;
	Inicializar(&p1);
	printf("\n Su expresion fue guardada correctamente. \nSe procedera a validar parentesis\n");
	for(i = 0; i < strlen(cadena); i++){
		if(cadena[i] == '('){

			e1.c = cadena[i];
			Push(&p1, e1);
			printf("( S");
		}
		else if(cadena[i] == ')'){
		
			if(Empty(&p1) == FALSE){
				Pop(&p1);
				printf(" ) eps ");
			
			}
			else{
				printf("\n\t%i ERROR, hay mas parentesis que cierran que los que abren \n", i+1);
				return FALSE;
			}
		}
	}
validarParentesis2(cadena);
	return (Empty(&p1) == TRUE)?TRUE:FALSE;
}


int main(){
	elemento e1;
	pila p1;
	char expresion[MAX]; 
	int i;				 
	while(1){
		Inicializar(&p1);
		printf("Programa que valida y resuelve expresiones algebraicas por medio de una pila\n");
		printf("Como ejemplo, puede introducir una expresion como () \n");
		printf("NOTA: procure no dejar espacios\n");
		printf("\n\n A continuacion introduzca su expresion: ");
		scanf("%s",expresion);
		if(validarParentesis(expresion) == TRUE){ 
		printf("\nExpresion final\n%s", expresion);
			printf("\nParentesis correctos\n");
			Destroy(&p1); 
		}
		else{ 
			printf("\n Parentesis incorrectos, revise la sintaxis \n");
		}
		if(otroProceso() == TRUE){ 
			Destroy(&p1);
			getchar();
			setbuf(stdin, NULL);
		}
		else break; 
	}
	getchar();
	return 0;
}
