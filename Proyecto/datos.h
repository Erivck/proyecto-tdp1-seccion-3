#ifndef FORMATOS_H_INCLUDED
#define FORMATOS_H_INCLUDED

#include <stdbool.h>

typedef enum {
  numerico,
  alfabetico,
  alfanumerico,
  signosDePuntuacion,
} Tipo_de_Formato;

typedef enum {
  Usuario,
  Clave,
  Nombre,
  Apellido,
  Cedula,
} Tipo_de_Dato;


char* obtenerFormato(Tipo_de_Formato formato);

char* obtenerFormatoDeDato(Tipo_de_Dato tipo);

bool validarDato(Tipo_de_Dato tipo, char* buffer);

bool leerDato(Tipo_de_Dato dato, char* puntero);



#endif // FORMATOS_H_INCLUDED
