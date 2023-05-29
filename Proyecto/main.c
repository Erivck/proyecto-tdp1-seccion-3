#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "banco.h"

#define num_opciones 4

enum Opciones_Enum {
  INGRESAR_SISTEMA = 1,
  INGRESAR_COMO_CLIENTE,
  REGISTRAR_CLIENTE
};

const char *opciones [] = {
  "Ingresar Sistema.",
  "Ingresar como Cliente.",
  "Registrar Cliente.",
  "Salir."
};

int main()
{
  configurarConsola();

  int opcion;

  do {
    limpiarPantalla();
    opcion = 0;
    printf("\t\t---SERVICIO BANCARIO---\n\n\v");
    for (int i = 0; i < num_opciones; i++) {
      printf("%d. %s\n", i+1, opciones[i]);
    }
    printf("\nIngrese una opción: ");

    scanf("%d", &opcion);
    limpiarBuffer();

    switch (opcion) {
      case INGRESAR_SISTEMA:
        bancoIngresarSistema();
        break;
      case INGRESAR_COMO_CLIENTE:
        bancoIngresarCliente();
        break;
      case REGISTRAR_CLIENTE:
        bancoRegistrarCliente();
        break;
    }
  } while (opcion != num_opciones);

  return 0;
}
