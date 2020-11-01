import re 
import time
emailipn=re.compile('[a-z]{4,15}\@["alumno."]["ipn."]\.["mx"]|["ipn."]\.["mx"]')
email=input("Ingrese su correo institucional: ")
com=emailipn.search(email)
if com:
	print("Correo valido")
else: 
	print("Correo no valido")
time.sleep(10)
