#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void inicializarArregloBanderas(int *);
void pedirSimbolosNoTerminales(char* ,int*);
void pedirProducciones(char*,char*);
void phase1(char* ,char* ,int *);
void phase1Paso1(char* ,char* ,char* ,int *);
void phase1Paso2(char* ,char* ,char* ,int *);
void phase1Paso3(char* ,char* ,char* ,int *);
void imprimir4tupla(char *,char *,char*,char*,int *);
void obtenerSimbolosTerminales(char* ,char*);
void imprimirProducciones(char*,char *,int *);
void inicializarArregloBanderasletras(int *);
void inicializarArregloBanderasdigitos(int*);
int tamanoArregloBandera(int *);
void formatoNoTerminales(int*,char*);
void formatoSimbolosTerminales(char* ,char*);
void phase2(char* ,char* ,char* ,int *);
void phase2Paso1(char *,char*,char* ,char* ,int*);
void phase2Paso2(char *,char*,char* ,int*);
void phase2Paso3(char *,char*,char* ,int*);
void obtenerSimbolosNoTerminales(int *,char *);
void sustituirEpsilonEncontrado(char* ,char *,char );
void removerEpsilon(char *,char *);
void sustituirUnitarioEncontrado(int ,char *,char*);
void removerUnitarias(char *,char *);
int validarSiQuedanUnitarias(char *);

//PROGRAMA PRINCIPAL
int main()
{
	char simbolos_no_terminales[1001],producciones[7000],simbolos_terminales[1001];
	int alfabeto[26];
	char simboloInicial[2];
	inicializarArregloBanderas(alfabeto);
	pedirSimbolosNoTerminales(simbolos_no_terminales,alfabeto);
	simboloInicial[0]=simbolos_no_terminales[0];
	simboloInicial[1]='\0';
	pedirProducciones(producciones,simbolos_no_terminales);
	
	removerEpsilon(producciones,simbolos_no_terminales);
	removerUnitarias(simbolos_no_terminales,producciones);
	phase1(producciones,simbolos_no_terminales,alfabeto);
	printf("RESULTADOS DE LA FASE 1:\n");
	imprimir4tupla(producciones,simbolos_terminales,simboloInicial,simbolos_no_terminales,alfabeto);
	phase2(producciones,simbolos_no_terminales,simboloInicial,alfabeto);
	printf("RESULTADOS DE LA FASE 2:\n");
	imprimir4tupla(producciones,simbolos_terminales,simboloInicial,simbolos_no_terminales,alfabeto);
};

void inicializarArregloBanderas(int *alfabeto)
{
	int i;
	for(i=0;i<=25;i++)
	{
		alfabeto[i]=0;
	}
};

void pedirSimbolosNoTerminales(char* simbolos_no_terminales,int* alfabeto)
{
	int tam,i,j=0,contiguedad=0,posicion;
	char auxiliar[1001];
	printf("Digita los simbolos no terminales separados por comas (S0,S1...Sn):\n");
	scanf("%s",auxiliar);
	strcat(auxiliar,",");//agrega una , al final del arreglo,esto lo hice por que más adelante en el for de abajo me quise ahorrar una condicional
	tam=strlen(auxiliar)-1;
	//Mete los simbolos no terminales en un arreglo,siempre y cuando sean solo mayusculas solas 
	for(i=0;i<=tam;i++)
	{
		if(isalpha(auxiliar[i]))
			contiguedad++;
		else if(auxiliar[i]==',')
		{
			if(isupper(auxiliar[i-1]) && contiguedad==1)
			{
				posicion=auxiliar[i-1]-65;
			if(alfabeto[posicion]==0)
			{
				simbolos_no_terminales[j]=auxiliar[i-1];
				j++;
				simbolos_no_terminales[j]='\0';
				alfabeto[posicion]=1;
			}
			}
			contiguedad=0;
		}
	}
	printf("Simbolos No terminales:%s\n",simbolos_no_terminales); 
};

void pedirProducciones(char* producciones,char* simbolos_no_terminales)
{	
	int tam,i;
	char auxiliar[1001];
	tam=strlen(simbolos_no_terminales)-1;
	printf("Digite las producciones de los respectivos simbolos con simbolos terminales(letras minusculas,* para representar epsilon) y no terminales (i.e S->a|b|aS...):\n");
	for(i=0;i<=tam;i++)
	{
		printf("%c->",simbolos_no_terminales[i]);
		scanf("%s",auxiliar);
		strcat(producciones,auxiliar);
		strcat(producciones,".");
		fflush(stdin);
	}
};

void phase1(char* producciones,char* simbolos_no_terminales,int *alfabeto)
{
	char auxiliar[1001];
	printf("FASE 1 :ELIMINACION DE SIMBOLOS NO GENERATIVOS\n");
	
	phase1Paso1(producciones,simbolos_no_terminales,auxiliar,alfabeto);
	
	phase1Paso2(producciones,simbolos_no_terminales,auxiliar,alfabeto);
	
	phase1Paso3(producciones,simbolos_no_terminales,auxiliar,alfabeto);
	
	obtenerSimbolosNoTerminales(alfabeto,simbolos_no_terminales);
};

//Identifica que simbolos  producen al menos un simbolo terminal

void phase1Paso1(char* producciones,char* simbolos_no_terminales,char* auxiliar,int *alfabeto)
{
	int i,j=0,k=0,tam,posicion,terminales=0,no_terminales=0;
	tam=strlen(producciones)-1;
	inicializarArregloBanderas(alfabeto);
	for(i=0;i<=tam;i++)
	{	
		if(producciones[i]=='.')
		{
			if(no_terminales==0 && terminales>=1)
			{
				posicion=simbolos_no_terminales[j]-65;
				if(alfabeto[posicion]==0)
				{
					auxiliar[k]=simbolos_no_terminales[j];
					k++;
					auxiliar[k]='\0';
					alfabeto[posicion]++;
				}
			}
			terminales=0;
			no_terminales=0;
			j++;
		}
		else if(islower(producciones[i]) || isdigit(producciones[i]))
			terminales++;
		else if(isupper(producciones[i]))
		{
			no_terminales++;
		}
		else if(producciones[i]=='|')
		{
			if(no_terminales==0 && terminales>=1)
			{
				posicion=simbolos_no_terminales[j]-65;
				if(alfabeto[posicion]==0)
				{
					auxiliar[k]=simbolos_no_terminales[j];
					k++;
					auxiliar[k]='\0';
					alfabeto[posicion]++;
				}
			}
			else
			{
				terminales=0;
				no_terminales=0;
			}
		}
	}
};

//Verifica que simbolos producen los simbolos que se guardaron en el paso anterior
void phase1Paso2(char*producciones,char*simbolos_no_terminales,char*auxiliar,int* alfabeto)
{
	int produce=0,i,j=0,k=0,no_terminales=0,tam,posicion;
	char auxiliar2[1001];
	tam=strlen(producciones)-1;
	while(strcmp(auxiliar2,auxiliar))
	{
		for(i=0;i<=tam;i++)
		{
			if(producciones[i]=='.')
			{
				if(produce==no_terminales )
				{
					posicion=simbolos_no_terminales[j]-65;
					if(alfabeto[posicion]==0)
					{
						alfabeto[posicion]=1;
						strcpy(auxiliar2,auxiliar);
						auxiliar2[strlen(auxiliar2)]=simbolos_no_terminales[j];
						strcpy(auxiliar,auxiliar2);
						}
				}
				produce=0;
				no_terminales=0;
				j++;
			}
			else if(isupper(producciones[i]))
			{
				posicion=producciones[i]-65;
				no_terminales++;
				if(alfabeto[posicion]==1)
					produce++;
			}
			else if(producciones[i]=='|')
			{
				if(produce==no_terminales)
				{
					posicion=simbolos_no_terminales[j]-65;
					if(alfabeto[posicion]==0)
					{
						alfabeto[posicion]=1;
						strcpy(auxiliar2,auxiliar);
						auxiliar2[strlen(auxiliar2)]=simbolos_no_terminales[j];
						strcpy(auxiliar,auxiliar2);
					}
				}
				produce=0;
				no_terminales=0;
			}	
		}
	}
};

//actualiza los nuevos simbolos no terminales
void phase1Paso3(char*producciones,char*simbolos_no_terminales,char*auxiliar,int* alfabeto)
{
	int produce=0,i,j=0,k=0,no_terminales=0,tam,posicion,indice=0,punto=0,x=0;
	char auxiliar2[1001],producciones_fase1[1001];
	producciones_fase1[0]='\0';
	tam=strlen(producciones)-1;
	
	for(i=0;i<strlen(simbolos_no_terminales);i++)
	{
		posicion=simbolos_no_terminales[i]-65;
		if(alfabeto[posicion]==1)
		{
			punto=0;
			while(punto==0)
			{
				if(isalpha(producciones[j]) || isdigit(producciones[j]) || producciones[j]=='*')
				{
					auxiliar2[k]=producciones[j];
					k++;
					auxiliar2[k]='\0';	
				}
				else
				{
					for(x=0;x<strlen(auxiliar2);x++)
					{
						if(isupper(auxiliar2[x]))
						{
							posicion=auxiliar2[x]-65;
							no_terminales++;
							if(alfabeto[posicion]==1)
								produce++;
						}
					}
					if(produce==no_terminales && producciones[j]=='|')
					{
						if(indice==0)
						{
							strcat(producciones_fase1,auxiliar2);
							produce=0;
							no_terminales=0;
							auxiliar2[0]='\0';
							indice=1;
							k=0;
						}
						else
						{
							strcat(producciones_fase1,"|");
							strcat(producciones_fase1,auxiliar2);
							produce=0;
							no_terminales=0;
							auxiliar2[0]='\0';
							k=0;
						}
					}
					else if(produce==no_terminales && producciones[j]=='.')
					{
						if(indice==1)
						{
							strcat(producciones_fase1,"|");
							strcat(producciones_fase1,auxiliar2);
							produce=0;
							no_terminales=0;
							auxiliar2[0]='\0';
							strcat(producciones_fase1,".");
							punto=1;
							k=0;
							indice=0;	
						}
						else
						{
							strcat(producciones_fase1,auxiliar2);
							produce=0;
							no_terminales=0;
							auxiliar2[0]='\0';
							strcat(producciones_fase1,".");
							punto=1;
							k=0;
							indice=0;
						}
					}
					else 
					{
						if(producciones[j]=='|')
						{
							produce=0;
							no_terminales=0;
							auxiliar2[0]='\0';
							k=0;
						}
						else
						{
							produce=0;
							no_terminales=0;
							auxiliar2[0]='\0';
							strcat(producciones_fase1,".");
							punto=1;
							indice=0;
							k=0;
						}
					}
				}
				j++;
			}
		}
		else
		{
			punto=0;
			while(punto==0)
			{
				if(producciones[j]=='.')
				{
					punto=1;
				}
				j++;
			}
		}
	}
	strcpy(producciones,producciones_fase1);
};

void imprimir4tupla(char *producciones,char *simbolos_terminales,char* simboloInicial,char*simbolos_no_terminales,int *alfabeto)
{
	int i;
	char no_terminales[101],terminales[101];
	printf("La Gramatica G esta dada por la 4drupla:\n");
	obtenerSimbolosTerminales(producciones,simbolos_terminales);
	formatoNoTerminales(alfabeto,no_terminales);
	formatoSimbolosTerminales(terminales,simbolos_terminales);
	printf("G:(%s,%s,P,{%s})\n",no_terminales,terminales,simboloInicial);
	printf("Donde las producciones P:\n");
	imprimirProducciones(producciones,simbolos_no_terminales,alfabeto);
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void obtenerSimbolosTerminales(char* producciones,char* simbolos_terminales)
Descripción:obtiene los simbolos terminales de una produccion
Recibe: Referencia a la cadena "producciones" y referencia a la cadena "simbolos_terminales".
Devuelve: NADA
Observaciones:
*/
void obtenerSimbolosTerminales(char* producciones,char* simbolos_terminales)
{
	int tam,i,j=0,posicion;
	int letras[26],digitos[10];//-97 y  -48
	inicializarArregloBanderasletras(letras);
	inicializarArregloBanderasdigitos(digitos);
	for(i=0;i<strlen(producciones);i++)
	{
		if(islower(producciones[i]) || isdigit(producciones[i]))
		{
			if(islower(producciones[i]))
			{
				posicion=producciones[i]-97;
				if(letras[posicion]==0)
				{
					simbolos_terminales[j]=producciones[i];
					letras[posicion]=1;
					j++;
				}
			}
			else
			{
				posicion=producciones[i]-48;
				if(digitos[posicion]==0)
				{
					simbolos_terminales[j]=producciones[i];
					digitos[posicion]=1;
					j++;
				}
			}
			
		}
	}
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void imprimirProducciones(char*producciones,char *simbolos_no_terminales,int *alfabeto)
Descripción:imprime las producciones de los simbolos no terminales
Recibe: Referencia a la cadena "producciones", referencia a la cadena "simbolos_no_terminales" y referencia al arreglo de enteros "alfabeto".
Devuelve: NADA
Observaciones:
*/
void imprimirProducciones(char*producciones,char *simbolos_no_terminales,int *alfabeto)
{
	int i,j=0,posicion;
	for(i=0;i<strlen(simbolos_no_terminales);i++)
		{	
			posicion=simbolos_no_terminales[i]-65;
			if(alfabeto[posicion]==1)
			{
				printf("%c->",simbolos_no_terminales[i]);
				while(producciones[j]!='.')
				{
					printf("%c",producciones[j]);
					j++;					
				}
				printf("\n");
				j++;
			}												
		}
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void inicializarArregloBanderasletras(int *letras)
Descripción:inicializa un arreglo de banderas para letras minusculas con 0´s
Recibe: Referencia al arreglo de enteros "letras".
Devuelve: NADA
Observaciones:
*/
void inicializarArregloBanderasletras(int *letras)
{
	int i;
	for(i=0;i<=25;i++)
	{
		letras[i]=0;
	}
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void inicializarArregloBanderasdigitos(int *digitos)
Descripción:inicializa un arreglo de banderas para digitos con 0's
Recibe: Referencia al arreglo de enteros "digitos".
Devuelve: NADA
Observaciones:
*/
void inicializarArregloBanderasdigitos(int *digitos)
{
	int i;
	for(i=0;i<=9;i++)
	{
		digitos[i]=0;
	}
};

/*
DEFINICIÓN DE PROCEDIMIENTO
int tamanoArregloBandera(int *alfabeto)
Descripción:muestra el "tamano" del arreglo de banderas,esto es,cuando sus posiciones son diferentes de 0
Recibe: Referencia al arreglo de enteros "alfabeto".
Devuelve:
Observaciones:
*/
int tamanoArregloBandera(int *alfabeto)
{
	int i,contador=0;
	for(i=0;i<=25;i++)
	{
		if(alfabeto[i]==1)
		{
			contador++;
		}
	}
	return contador;
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void formatoNoTerminales(int *alfabeto,char* no_terminales)
Descripción:Da formato para impresión de simbolos no terminales de la gramatica
Recibe: Referencia al arreglo de enteros "alfabeto" y a la cadena "no_terminales"
Devuelve: NADA
Observaciones:
*/
void formatoNoTerminales(int *alfabeto,char* no_terminales)
{
	int i,j=0;
	no_terminales[j]='{';
	j++;
	no_terminales[j]='\0';
	for(i=0;i<=25;i++)
	{
		if(alfabeto[i]==1)
		{
			no_terminales[j]=i+65;
			j++;
			no_terminales[j]=',';
			j++;
			no_terminales[j]='\0';
		}
	}
	no_terminales[j-1]='}';
	no_terminales[j+1]='\0';
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void formatoSimbolosTerminales(char* terminales,char* simbolos_terminales)
Descripción:Da formato para imprimir los simbolos terminales de la gramatica
Recibe: Referencia a la cadena "terminales" y a la cadena "simbolos_terminales".
Devuelve: NADA
Observaciones:
*/
void formatoSimbolosTerminales(char* terminales,char* simbolos_terminales)
{
	int i,j=0;
	terminales[j]='{';
	j++;
	terminales[j]='\0';
	for(i=0;i<strlen(simbolos_terminales);i++)
	{
		terminales[j]=simbolos_terminales[i];
		j++;
		terminales[j]=',';
		j++;
		terminales[j]='\0';
	}
	terminales[j-1]='}';
	terminales[j+1]='\0';
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void phase2(char* producciones,char* simbolos_no_terminales,char* simboloInicial,int *alfabeto)
Descripción:En la fase 2 se eliminan las producciones inalcanzables
Recibe: Referencia a la cadena "producciones", referencia a la cadena "simbolos_no_terminales", referencia a la cadena "simboloInicial"
y al arreglo de enteros "alfabeto".
Devuelve: NADA
Observaciones:
*/
void phase2(char* producciones,char* simbolos_no_terminales,char* simboloInicial,int *alfabeto)
{
	char auxiliar[1001];
	printf("FASE 2 :ELIMINACION DE SIMBOLOS INACCESIBLES\n");
	phase2Paso1(producciones,simbolos_no_terminales,simboloInicial,auxiliar,alfabeto);
	phase2Paso2(producciones,simbolos_no_terminales,auxiliar,alfabeto);
	phase2Paso3(producciones,simbolos_no_terminales,auxiliar,alfabeto);
	obtenerSimbolosNoTerminales(alfabeto,simbolos_no_terminales);
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void phase2Paso1(char *producciones,char*simbolos_no_terminales,char* simboloInicial,char* auxiliar,int*alfabeto)
Descripción:En este paso se agrega a un nuevo conjunto,
el simbolo inicial y los simbolos no terminales que produce
Recibe: Referencia a la cadena "producciones", referencia a la cadena "simbolos_no_terminales", referencia a la cadena "simboloInicial",
referencia a la cadena "auxiliar" y al arreglo de enteros "alfabeto".
Devuelve: NADA
Observaciones:
*/
void phase2Paso1(char *producciones,char*simbolos_no_terminales,char* simboloInicial,char* auxiliar,int*alfabeto)
{
	int i=0,j=0,k=1,tam,posicion;
	inicializarArregloBanderas(alfabeto);
	strcpy(auxiliar,simboloInicial);
	auxiliar[k]='\0';
	posicion=auxiliar[0]-65;
	alfabeto[posicion]=1;
	while(j==0)
	{
		if(isupper(producciones[i]))
		{
			posicion=producciones[i]-65;
			if(alfabeto[posicion]==0)
			{
			alfabeto[posicion]=1;
			auxiliar[k]=producciones[i];
			k++;
			auxiliar[k]='\0';
			}			
		}
		else if(producciones[i]=='.')
		{
			j++;
		}
		i++;
	}
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void phase2Paso2(char *producciones,char*simbolos_no_terminales,char* auxiliar,int*alfabeto)
Descripción:Se agregan los simbolos no terminales que producen los
simbolos agregados en el paso anterior
Recibe:Referencia a la cadena "producciones", referencia a la cadena "simbolos_no_terminales", referencia a la cadena "simboloInicial"
y al arreglo de enteros "alfabeto".
Devuelve: NADA
Observaciones:
*/
void phase2Paso2(char *producciones,char*simbolos_no_terminales,char* auxiliar,int*alfabeto)//por confirmar que este bien
{
	int i=0,j=1,k=0,posicion;
	while(j<strlen(auxiliar))
	{
		k=0;
		i=0;
		posicion=auxiliar[j]-65;
		while(k!=posicion+1)
		{
			if(producciones[i]=='.')
				k++;
			i++;
		}
		while(producciones[i]!='.')
		{		
			if(isupper(producciones[i]))
			{
			posicion=producciones[i]-65;
			if(alfabeto[posicion]==0)
				{				
				alfabeto[posicion]=1;
				auxiliar[strlen(auxiliar)]=producciones[i];
				auxiliar[strlen(auxiliar)]='\0';
				}			
			}
			i++;
		}
		j++;
	}
};

/*
DEFINICIÓN DE PROCEDIMIENTO
void phase2Paso3(char *producciones,char*simbolos_no_terminales,char* auxiliar,int*alfabeto)
Descripción:Actualiza las producciones nuevas ,omitiendo los simbolos
no terminales que quedaron fuera del conjunto final
Recibe: Referencia a la cadena "producciones", referencia a la cadena "simbolos_no_terminales", referencia a la cadena "auxiliar"
y al arreglo de enteros "alfabeto".
Devuelve: NADA
Observaciones:
*/
void phase2Paso3(char *producciones,char*simbolos_no_terminales,char* auxiliar,int*alfabeto)
{
	int i=0,j=0,k=0,x=0,posicion;
	char producciones_fase2[1001],auxiliar2[1001];
	int punto=0;
	for(i=0;i<strlen(simbolos_no_terminales);i++)
	{
		posicion=simbolos_no_terminales[i]-65;
		if(alfabeto[posicion]==1)
		{
			punto=0;
			while(punto==0)
			{				
				if(producciones[j]!='.')
				{
					auxiliar2[k]=producciones[j];
					k++;
					auxiliar2[k]='\0';						
				}
				else
				{
					punto=1;
					strcat(producciones_fase2,auxiliar2);
					strcat(producciones_fase2,".");
					k=0;
					auxiliar2[0]='\0';
				}
				j++;
			}
		}
		else
		{
			punto=0;
			while(punto==0)
			{				
				if(producciones[j]=='.')
				{
					punto=1;
				}
				j++;
			}
		}
	}
	strcpy(producciones,producciones_fase2);
};
//Obtiene los simbolos no terminales de un conjunto dado

void obtenerSimbolosNoTerminales(int *alfabeto,char *simbolos_no_terminales)
{
	int i=0,j=0;
	char auxiliar[1001];
	for(i=0;i<strlen(simbolos_no_terminales);i++)
	{
		if(alfabeto[(simbolos_no_terminales[i]-65)]==1)
		{
			auxiliar[j]=simbolos_no_terminales[i];
			j++;
			auxiliar[j]='\0';
		}
	}
	strcpy(simbolos_no_terminales,auxiliar);
};

//remueve los epsilons de la gramatica

void removerEpsilon(char *producciones,char *simbolos_no_terminales)
{
	int i=0,j=0,k=0,posicion,haynulo=0;
	while(producciones[i]!='.')
	{
		i++;
	}
	j++;
	i++;
	while(i<strlen(producciones))
	{
		if(producciones[i]=='.')
		{
			if(haynulo==1)
			{
				sustituirEpsilonEncontrado(simbolos_no_terminales,producciones,simbolos_no_terminales[j]);
				j=0;
				haynulo=0;
			}
			else
			{
			j++;	
			}
		}
		else if(producciones[i]=='*')
		{
			haynulo=1;
		}
		i++;
	}
};
//sustituye un epsilon encontrado en todas las producciones ,sustituyendo el simbolo no terminal que genera a este
//en las producciones que contengan a este simbolo
void sustituirEpsilonEncontrado(char* simbolos_no_terminales,char *producciones,char simboloEpsilon)
{
	int i=0,j=0,k=0,x=0,y=0,punto=0,haynulo=0,indice=0;
	char auxiliar2[1001];
	char auxiliar3[1001];
	char producciones_s[1001];
	for(i=0;i<strlen(simbolos_no_terminales);i++)
	{
			punto=0;
			while(punto==0)
			{
				if(isalpha(producciones[j]) || isdigit(producciones[j]))
				{
					if(producciones[j]==simboloEpsilon)
						haynulo=1;
					auxiliar2[k]=producciones[j];
					k++;
					auxiliar2[k]='\0';						
				}
				else if(producciones[j]=='*')
				{
					if(producciones[j+1]=='.')
						j++;
					else
						j=j+2;
				}
				else if(producciones[j]=='|' && producciones[j+1]=='*')
				{
					j++;
				}
				else
				{
				if(strlen(auxiliar2)!=0)
				{
					for(x=0;x<strlen(auxiliar2);x++)
					{
						if(haynulo==1)
						{
							if(auxiliar2[x]!=simboloEpsilon)
								{
								auxiliar3[y]=auxiliar2[x];
								y++;
								auxiliar3[y]='\0';
								}
						}
					}
				}
					if(producciones[j]=='|')
					{
						if(indice==0)
						{
							strcat(producciones_s,auxiliar2);
							auxiliar2[0]='\0';
							indice=1;
							k=0;
							if(haynulo==1)
							{
								strcat(producciones_s,"|");
								strcat(producciones_s,auxiliar3);
								y=0;
								auxiliar3[y]='\0';
								haynulo=0;
							}
							y=0;
						}
						else
						{
							strcat(producciones_s,"|");
							strcat(producciones_s,auxiliar2);
							auxiliar2[0]='\0';
							k=0;
							if(haynulo==1)
							{
								strcat(producciones_s,"|");
								strcat(producciones_s,auxiliar3);
								y=0;
								auxiliar3[y]='\0';
								haynulo=0;
							}
							y=0;
						}
					}
					else if(producciones[j]=='.')
					{
						if(indice==1)
						{
							strcat(producciones_s,"|");
							strcat(producciones_s,auxiliar2);
							auxiliar2[0]='\0';
							if(haynulo==1)
							{
								strcat(producciones_s,"|");
								strcat(producciones_s,auxiliar3);
								y=0;
								auxiliar3[y]='\0';
								haynulo=0;
							}
							y=0;	
							strcat(producciones_s,".");
							punto=1;
							k=0;
							indice=0;
						}
						else
						{
							strcat(producciones_s,auxiliar2);
							auxiliar2[0]='\0';
							if(haynulo==1)
							{
								strcat(producciones_s,"|");
								strcat(producciones_s,auxiliar3);
								y=0;
								auxiliar3[y]='\0';
								haynulo=0;
							}	
							strcat(producciones_s,".");
							punto=1;
							k=0;
							indice=0;
							y=0;
						}
					}					
				}
				j++;
			}
	}
	strcpy(producciones,producciones_s);
};
//Remueve producciones unitarias
void removerUnitarias(char *simbolos_no_terminales,char *producciones)
{
	int i=0,j=0,k=0,x=0,posicion,punto=0,simbolosNoTerminales=0,indice=0,totales=0;
	char auxiliar[1001],producciones_u[1001];
	do
	{	
	i=0;
	j=0;
	k=0;
	for(i=0;i<strlen(simbolos_no_terminales);i++)
	{
		punto=0;
		while(punto==0)
		{
			if(isalpha(producciones[j]) || isdigit(producciones[j]))
			{
				auxiliar[k]=producciones[j];
				k++;
				auxiliar[k]='\0';
				totales++;
				if(isupper(producciones[j]))
				{
					simbolosNoTerminales++;
				}
			}
			else if(producciones[j]=='|')
			{
				if(indice==0)
						{
							if(simbolosNoTerminales==1 && totales==1)
							{
								sustituirUnitarioEncontrado((auxiliar[k-1]-65)+1,auxiliar,producciones);
								strcat(producciones_u,auxiliar);
								auxiliar[0]='\0';
								k=0;
								simbolosNoTerminales=0;
								totales=0;							
							}
							else
							{
								strcat(producciones_u,auxiliar);
								auxiliar[0]='\0';
								indice=1;
								k=0;
								simbolosNoTerminales=0;
								totales=0;							
							}
						}
						else
						{
							if(simbolosNoTerminales==1 && totales==1)
							{
								strcat(producciones_u,"|");
								sustituirUnitarioEncontrado((auxiliar[k-1]-65)+1,auxiliar,producciones);
								strcat(producciones_u,auxiliar);
								auxiliar[0]='\0';
								k=0;
								simbolosNoTerminales=0;
								totales=0;							
							}
							else
							{
								strcat(producciones_u,"|");
								strcat(producciones_u,auxiliar);
								auxiliar[0]='\0';
								k=0;
								simbolosNoTerminales=0;
								totales=0;							
							}		
						}
			}
			else if(producciones[j]=='.')
			{
				if(indice==1)
						{	
							if(simbolosNoTerminales==1 && totales==1)
							{
								strcat(producciones_u,"|");
								sustituirUnitarioEncontrado((auxiliar[k-1]-65)+1,auxiliar,producciones);
								strcat(producciones_u,auxiliar);
								auxiliar[0]='\0';
								strcat(producciones_u,".");
								punto=1;
								k=0;
								indice=0;
								simbolosNoTerminales=0;
								totales=0;
							}
							else
							{
								strcat(producciones_u,"|");
								strcat(producciones_u,auxiliar);
								auxiliar[0]='\0';
								strcat(producciones_u,".");
								punto=1;
								k=0;
								indice=0;
								simbolosNoTerminales=0;
								totales=0;
							}
						}
						else
						{
							if(simbolosNoTerminales==1 && totales==1)
							{		
								sustituirUnitarioEncontrado((auxiliar[k-1]-65)+1,auxiliar,producciones);
								strcat(producciones_u,auxiliar);
								auxiliar[0]='\0';
								strcat(producciones_u,".");
								punto=1;
								k=0;
								indice=0;
								simbolosNoTerminales=0;
								totales=0;
							}
							else
							{
								strcat(producciones_u,auxiliar);
								auxiliar[0]='\0';
								strcat(producciones_u,".");
								punto=1;
								k=0;
								indice=0;
								simbolosNoTerminales=0;
								totales=0;
							}							
						}
			}
			j++;
		}		
	}
	strcpy(producciones,producciones_u);
	producciones_u[0]='\0';
	}while(validarSiQuedanUnitarias(producciones));
};

//Sustituye el valor de las producciones 

void sustituirUnitarioEncontrado(int limite,char *auxiliar,char *producciones)
{
	int i=0,j=0,k=0;
	while(j!=limite)
	{
		if(producciones[i]=='.')
			j++;
		i++;
	}
	while(producciones[i]!='.')
	{
		auxiliar[k]=producciones[i];
		k++;
		auxiliar[k]='\0';
		i++;
	}
};

int validarSiQuedanUnitarias(char *producciones)
{
	int i=0,j=0,k=0,unitarias=0,totales=0,nt=0;
	for(i=0;i<strlen(producciones);i++)
	{
		if(isalpha(producciones[i])|| isdigit(producciones[i]))
		{
			totales++;
			if(isupper(producciones[i]))
			{
				nt++;
			}
		}
		else
		{
			if(nt==1 && totales==1)
			{
				unitarias++;
				totales=0;
				nt=0;
			}
			else
			{
				totales=0;
				nt=0;
			}
		}
	}
	if(unitarias==0)
		return 0;
	else
		return 1;
};
