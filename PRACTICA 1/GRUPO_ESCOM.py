#Rojas Alvarado Luis Enrique
# 2CM11
#06/09/2018
import re 

def grupo():
	grupoESCOM=re.compile('^([1-5][C][MV])([1]?[1-4]|[1-9])$')
	grupo=input("Ingrese su grupo: ")
	com=grupoESCOM.search(grupo)
	if com: 
		print("El grupo que ingreso es valido")
	else: 
		print("El grupo que ingreso es no valido")
	pass
grupo()
print("Presione 1/0 para si/no")
while True:
	respuesta=input("Quiere ingresarlo de nuevo?:")
	if respuesta=="1":
		grupo()
		pass
	elif respuesta=="0":
		break
	else:
		print("opcion no valida")
		print("Por favor seleccione 1/0")
	pass