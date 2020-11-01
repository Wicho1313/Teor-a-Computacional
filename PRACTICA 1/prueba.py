if userInput.lower() == "s":

    while True:
        respuesta = input("Respecto a: (1)Interfaz?  (2)Metodos?  (3)Funciones? (4)misceláneos (5)Volver?  ")

        if respuesta == "1":
            while True:
                DetalleRespuesta = input("para interfaz tenemos (1)Teclado y (2)Mouse,*(3)Volver*, Cual de ellos le iteresa?: ")

                if DetalleRespuesta == "1":
                    print("Teclado")

                elif DetalleRespuesta == "2":    
                    print("Mouse")

                elif DetalleRespuesta == "3":
                    break  # Salimos de insterfaz

                else:
                    print("Opción inválida")

        elif respuesta == "2":
            print("Métodos")

        elif respuesta == "3":
            print("Funciones")

        elif respuesta == "4":
            print("Misceláneos")

        elif respuesta == "5":
            break # Salimos de la opción "s"

        else:
            print("Opción inválida")