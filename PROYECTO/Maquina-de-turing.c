#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100
typedef struct elemento
{
    char dato;
    struct elemento *sig;
    struct elemento *ant;
}Elemento;
typedef struct ListaIdentificar
{
    Elemento *inicio;
    Elemento *fin;
    int tamano;
}Lista;
void menu(void);
void inicializa(Lista *);
Elemento * creaNodo(char );
void avanzar(Lista*, Elemento *);
void imprime_i_f(Lista *);
void imprime_f_i(Lista *);
int inserta_primer_elem(Lista *, Elemento *);
int inserta_al_inicio(Lista *, Elemento *);
int inserta_al_final(Lista *, Elemento *);
int inserta_en_pos(Lista *, Elemento *, int);
int elimina_al_inicio(Lista *);
int elimina_al_final(Lista *);
void cinta(Lista *);
int elimina_ultimo(Lista *);//lista con 1 elemento
int elimina_en_pos(Lista *, int);
void destruye_lista(Lista *);
void main(void)
{
	char cadena[TAM],quintupla[TAM],dir[TAM];
    int opcion, pos,i,a,num;
    char cad;
    Lista lista1;
    Elemento *nvo;
    do
    {
        menu();
        inicializa(&lista1);
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1: 
            
			        printf("\nIngrese el numero a cambiar a binario:");
			        scanf("%d",&num);
                    cadena[0]=num;
			        nvo=creaNodo(cadena[0]);
			        inserta_primer_elem(&lista1,nvo);
                    

                   cinta(&lista1);
                    break;
            
            case 2: printf("Hasta luego...");
            exit(0);
                    break;
            default: printf("Opción inválida");
        }
        system("pause");
        destruye_lista(&lista1);
    }while(opcion!=3);
}
void menu(void)
{
    system("cls ");
    printf("Menú de la maquina de Turing para transformar de Decimal a Binario.\n\n");
    printf("_____________________________\n");
    printf("1) Cambiar de decinal a binario\n");
    printf("2) Salir\n");
    printf("Opción: ");
}
void inicializa(Lista *l)
{
    l->inicio=NULL;
    l->fin=NULL;
    l->tamano=0;
}
Elemento * creaNodo(char cad)
{

    Elemento *nvo;
    nvo=(Elemento *)malloc(sizeof(Elemento));
    if(nvo!=NULL)
    {
        nvo->sig=NULL;
        nvo->ant=NULL;
        nvo->dato=cad;
    }
    return nvo;
}
void imprime_i_f(Lista *l)
{
    Elemento *aux=l->inicio;
    printf("< ");
    while(aux!=NULL)
    {
        if(aux==l->inicio)
        {
        	printf(" %d | ", aux->dato);
        aux=aux->sig;
		}
		else
		{
		
		printf(" %c | ", aux->dato);
        aux=aux->sig;
    }
    }
    printf(" b >\n");
}
 void imprime_f_i(Lista *l )
 {
 	 Elemento *aux=l->fin;

 	 printf("< ");
    while(aux!=NULL)
    {
        if(aux==l->fin)
        {
        	printf(" %c | ", aux->dato);
        aux=aux->ant;
		}
		else
		{
		
		printf(" %c | ", aux->dato);
        aux=aux->ant;
    }
    }
    printf(" b >\n");
 }
 
int inserta_primer_elem(Lista *l, Elemento *nvo)
{
        if(l->tamano==0)
        {
            l->inicio=nvo;
            l->fin=nvo;
            l->tamano++;
            return 1;
        }
        else
            return 0;
}
int inserta_al_inicio(Lista *l, Elemento *nvo)
{
    if(l->tamano>0)
    {
        nvo->sig=l->inicio;
        l->inicio->ant=nvo;
        l->inicio=nvo;
        l->tamano++;
        return 1;
    }
    else
        return 0;
}
int inserta_al_final(Lista *l, Elemento *nvo)
{
    if(l->tamano>0)
    {
        l->fin->sig=nvo;
        nvo->ant=l->fin;
        l->fin=nvo;
        l->tamano++;
        return 1;
    }
    else
        return 0;
}
int inserta_en_pos(Lista *l, Elemento *nvo, int pos)
{
    Elemento *aux=l->inicio;    int i;
    if(l->tamano>0)
    {
        if((pos>0)&&(pos<=(l->tamano)))
        {
            if(pos==1)
                return (inserta_al_inicio(l,nvo));
            else
            {
                for(i=1;i<pos;i++)
                    aux=aux->sig;
                nvo->sig=aux;
                aux->ant->sig=nvo;
                nvo->ant=aux->ant;
                aux->ant=nvo;
                l->tamano++;
                return 1;
            }
        }
        else
            return 0;
    }
    else
        return 0;
}
int elimina_al_inicio(Lista *l)
{
    Elemento *aux=l->inicio;
    if(l->tamano>1)
    {
        l->inicio=l->inicio->sig;  //l->inicio=aux->sig;
        l->inicio->ant=NULL;
        free(aux);
        l->tamano--;
        return 1;
    }
    else
        return 0;
}
int elimina_al_final(Lista *l)
{
    Elemento *aux=l->inicio;   int i;
    if(l->tamano>1)
    {
        for(i=1;i<=(l->tamano-2);i++)
            aux=aux->sig;
        l->fin=aux;
        l->fin=l->fin->ant;
        l->fin->sig=NULL;
        free(aux->sig);
        l->tamano--;
        return 1;
    }
    else
        return 0;
}
int elimina_ultimo(Lista *l)
{
    if(l->tamano==1)
    {
    	l->fin->sig=NULL;
    	l->inicio->ant=NULL;

        inicializa(l);
        return 1;
    }
    else
        return 0;
}
int elimina_en_pos(Lista *l, int pos)
{
    Elemento *aux1=l->inicio, *aux2;   int i;
    if(l->tamano>0)
    {
        if((pos>0)&&(pos<=(l->tamano)))
        {
           if(pos==1)
           {
                if(l->tamano==1)
                    return (elimina_ultimo(l));
                else
                    return (elimina_al_inicio(l));
           }
           else
           {
                if(pos==l->tamano)
                    return (elimina_al_final(l));
                else
                {
                    for(i=1;i<=(pos-2);i++)
                        aux1=aux1->sig;
                    aux2=aux1->sig;
                    aux1->sig=aux2->sig;
                    aux1->ant=aux2->ant;
                    free(aux2);
                    l->tamano--;
                    return 1;
                }
            }
        }
        else
            return 0;
    }
    else
        return 0;
}
void avanzar(Lista*l, Elemento *nvo)
{
	int elem;
	if(l->tamano==0)
	  inserta_primer_elem(l,nvo);
	else
	 inserta_al_final(l,nvo);
}
void destruye_lista(Lista *l)
{
    int tmp;
    while(l->tamano>0)
    {
        if(l->tamano==1)
            tmp=elimina_ultimo(l);
        else
            tmp=elimina_al_inicio(l);
    }
}
void cinta(Lista *l)
{
	int cont=2,num,h;
	int y=0;
	int t=1;
    char pos;
	Elemento *aux=l->inicio;
	Elemento *nvo;
	Elemento *aux2=l->inicio;
	Elemento *aux3=l->inicio;
	num=aux->dato;
	do
	{
	
	
    if(num%2==0)
    {
        num=(num)/2;
		pos='b';
		nvo=creaNodo(pos);
    	avanzar(l,nvo);
    	imprime_i_f(l);
    	
	}
	else
	{
		if((num+1)%2==0)
		{
		
		num=(num-1)/2;
		pos='c';
		nvo=creaNodo(pos);
    	avanzar(l,nvo);
    	imprime_i_f(l);
       }
       else
       {
       	
       	printf("< b | 0 | b >");
	   }
	}
	aux=aux->sig;
	if(aux->dato=='b')
	{
		aux->dato='0';
	}
	else
	{
		if(aux->dato=='c')
		{
			aux->dato='1';
		}
	}
	imprime_i_f(l);
	
	aux2->dato=num;
}while(num>0);
        printf("\nEl resultado en binario es:\n ");
		aux3->dato='b';
		imprime_f_i(l);
	
}

