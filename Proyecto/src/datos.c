#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../datos.h"
#include "../utils.h"

char* Nombre_de_Datos[] = {
  "Usuario",
  "Clave",
  "Nombre",
  "Apellido",
  "Número de Cedula",
};

int datoMaxChars[] = {
  15, // Usuario
  20, // Clave
  15, // Nombre
  15, // Apellido
  8, // Cedula
};

char* formatos[] = {
    "1234567890",
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñÑ",
    "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñÑ",
    ".,;:-",
};


char* obtenerFormato(Tipo_de_Formato formato) {
  switch(formato) {
    case numerico:
    case alfabetico:
    case signosDePuntuacion:
      return formatos[formato];
    case alfanumerico:
      return strcat(formatos[numerico], formatos[alfabetico]);
    default:
      return NULL;
  }
}

char* obtenerFormatoDeDato(Tipo_de_Dato tipo) {
  switch(tipo) {
    case Usuario: {
      int longitud = strlen(formatos[alfanumerico]) + 2;
      char* formatoUsuario = (char*) calloc(longitud, sizeof(char));
      sprintf(formatoUsuario, "%s_", formatos[alfanumerico]);
      return formatoUsuario;
    }
    case Nombre:
    case Apellido:
      return formatos[alfabetico];
    case Cedula:
      return formatos[numerico];
    case Clave:
    default:
      return NULL;
  }
}

bool validarDato(Tipo_de_Dato tipo, char* buffer) {
  char* formato = obtenerFormatoDeDato(tipo);
  if (formato == NULL) return false;
  for (int i = 0; buffer[i] != 0; i++) {
    if (strchr(formato, buffer[i]) == NULL) return true;
  }
  if (tipo == Usuario) free(formato);
  return false;
}


bool leerDato(Tipo_de_Dato dato, char* puntero) {
  bool error;

  char bufferDeEntrada[27] = {0};

  printf("%s: ", Nombre_de_Datos[dato]);
  scanf(" %26[^\n]", bufferDeEntrada);
  printf("\n");

  int numCaracteres = strlen(bufferDeEntrada);

  if (numCaracteres > datoMaxChars[dato]) {
    printf("El máximo de caracteres es %d.\n\n", datoMaxChars[dato]);
    esperarEntrada();
    return true;
  }

  error = validarDato(dato, bufferDeEntrada);

  if (error) {
    printf("%s inválid%c.\n\n", Nombre_de_Datos[dato], dato == Clave? 'a': 'o');
    esperarEntrada();
    return true;
  }

  strcpy(puntero, bufferDeEntrada);

  return false;
}
