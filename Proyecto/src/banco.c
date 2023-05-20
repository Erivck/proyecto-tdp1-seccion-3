#include <stdio.h>
#include "../banco.h"
#include "../cliente.h"
#include "../utils.h"

#define NUM_OPCIONES_BANCO 5

enum Opciones_Banco {
  CONSULTAR = 1,
  INGRESAR,
  MODIFICAR,
  BORRAR,
};

const char* opcionesDelBanco[] = {
  "Consultar Datos.",
  "Ingresar Datos.",
  "Modificar Datos.",
  "Borrar cuenta.",
  "Cerrar sesión."
};


void bancoMenu(Cliente* cliente) {
  int opcion;

  do
  {
    limpiarPantalla();
    opcion = 0;

    printf("\t\t\t---SERVICIO DE BANCARIO---\n\n\v");
    printf("Bienvenido %s %s, seleccione una de la opciones:\n\n", cliente->nombre, cliente->apellido);

    for (int i = 0; i < NUM_OPCIONES_BANCO; i++) {
      printf("%d. %s\n", i+1, opcionesDelBanco[i]);
    }

    printf("\nIntroduzca una opcion: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    switch (opcion) {
      case CONSULTAR:
      case INGRESAR:
      case MODIFICAR:
      case BORRAR:
        break;
    }
  } while(opcion != 5);

}
