#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../utils.h"

void limpiarPantalla () {
  system("clear||cls");
}

void limpiarBuffer () {
  while ((getchar()) != '\n');
}

void esperarEntrada() {
  printf("Presione \"Enter\" para continuar...");
  limpiarBuffer();
}

