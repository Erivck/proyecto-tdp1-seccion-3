#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "ingresar.h"

#define num_opciones 3

#ifdef _WIN32
#include <windows.h>
#define configurarConsola() SetConsoleCP(1252); SetConsoleOutputCP(1252)
#else
#define configurarConsola()
#endif // _WIN32


enum Opciones_Enum {
  INGRESAR = 1,
  REGISTRARSE
};

const char *opciones [] = {
  "Ingresar.",
  "Registrarse.",
  "Salir."
};

int main()
{
  configurarConsola();

  int opcion;

  do {
    limpiarPantalla();
    opcion = 0;
    printf("\t\t\t---SERVICIO DE ATENCIÓN AL CLIENTE---\n\n\v");
    for (int i = 0; i < num_opciones; i++) {
      printf("%d. %s\n", i+1, opciones[i]);
    }
    printf("\nIngrese una opción: ");

    scanf("%d", &opcion);
    limpiarBuffer();

    switch (opcion) {
      case INGRESAR:
        limpiarPantalla();
        ingresar();
        break;
      case REGISTRARSE:
        limpiarPantalla();
        registrarse();
        break;
    }
  } while (opcion != 3);

  return 0;
}
