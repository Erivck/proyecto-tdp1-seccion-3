#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../datos.h"
#include "../utils.h"

const char* Nombre_de_Datos[] = {
  "Usuario",
  "Clave",
  "Nombres",
  "Apellidos",
  "Número de Cédula",
  "Sexo",
  "Fecha de Nacimiento",
  "Número de Teléfono",
  "Estado",
  "Ciudad",
  "Municipio",
  "Dirección",
  "Código Postal",
  "Número de Cuenta",
  "Cédula del Cliente",
  "Teléfono de Pago Móvil",
  "Tipo de Cuenta"
};

const char* Nombre_de_Datos_Minusculas[] = {
  "usuario",
  "clave",
  "nombre",
  "apellido",
  "número de cédula",
  "sexo",
  "fecha de nacimiento",
  "número de teléfono",
  "estado",
  "ciudad",
  "municipio",
  "dirección",
  "código postal",
  "número de cuenta"
};

const char* formatos[] = {
    "1234567890",
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñÑ ",
    "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñÑ ",
    "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñÑ .,;:-",
    "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñÑ_",
    "1234567890/"
};

const time_t edadMinima = 365 * 24 * 60 * 60 * 18;

const char* ejemploDeFormato(Tipo_de_Dato dato) {
  switch (dato){
  case FECHA_DE_NACIMIENTO:
    return " (dd/mm/aaaa)";
  case SEXO:
    return " (M o F)";
  default:
    return NULL;
  }
}

int datoMaxChars[] = {
  USUARIO_MAX, // Usuario
  CLAVE_MAX, // Clave
  NOMBRES_MAX, // Nombre
  APELLIDOS_MAX, // Apellido
  CEDULA_MAX, // Cédula
  SEXO_MAX, // Sexo
  FECHA_DE_NACIMIENTO_MAX, // Fecha de Nacimiento
  TELEFONO_MAX, // Teléfono
  ESTADO_MAX, // Estado
  CIUDAD_MAX, // Ciudad
  MUNICIPIO_MAX, // Municipio
  DIRECCION_MAX, // Direccion
  CODIGO_POSTAL_MAX, // Código Postal
  NUMERO_DE_CUENTA_MAX // Numero de Cuenta
};



int datoMinChars(Tipo_de_Dato tipo) {
  switch (tipo) {
    case CODIGO_POSTAL:
      return 4;
    case TELEFONO:
      return 10;
    case FECHA_DE_NACIMIENTO:
      return 10;
    case NUMERO_DE_CUENTA:
      return 10;
    default:
      return 1;
  }
}

bool datoTerminaConA(Tipo_de_Dato dato) {
  switch(dato) {
    case CLAVE:
    case CIUDAD:
    case DIRECCION:
    case FECHA_DE_NACIMIENTO:
      return true;
    default:
      return false;
  }
}

const char* obtenerFormatoDeDato(Tipo_de_Dato tipo) {
  switch(tipo) {
    case USUARIO:
      return formatos[formatoDeUsuario];
    case NOMBRES:
    case APELLIDOS:
    case ESTADO:
    case CIUDAD:
    case MUNICIPIO:
      return formatos[alfabetico];
    case DIRECCION:
      return formatos[texto];
    case CEDULA:
    case TELEFONO:
    case CODIGO_POSTAL:
    case NUMERO_DE_CUENTA:
      return formatos[numerico];
    case SEXO:
      return "FM";
    case FECHA_DE_NACIMIENTO:
      return formatos[fecha];
    case CLAVE:
    default:
      return NULL;
  }
}

int validarFecha(char* buffer) {
  time_t fechaNacimiento, fechaActual;
  int d, m, a, args;

  args = sscanf(buffer, "%2d/%2d/%4d", &d, &m, &a);
  if (args != 3) return ERROR_FORMATO_INVALIDO;

  struct tm estructuraFecha = {.tm_mday = d, .tm_mon = m, .tm_year = a-1900};
  fechaNacimiento = mktime(&estructuraFecha);

  if (fechaNacimiento < 0) return ERROR_FECHA_INVALIDA;

  fechaActual = time(NULL);

  if  (fechaActual - fechaNacimiento < edadMinima) return ERROR_CLIENTE_MENOR_EDAD;

  return 0;
}

void aplicarFormatoCedula(char* buffer) {
  int numCedula = (int) strtol(buffer, NULL, 10);
  sprintf(buffer, "%08d", numCedula);
}

int validarDato(Tipo_de_Dato tipo, char* buffer) {
  int numCaracteres = strlen(buffer);

  if (numCaracteres > datoMaxChars[tipo]) {
    return ERROR_MAXIMO_DE_CARACTERES;
  }

  if (numCaracteres < datoMinChars(tipo)) {
    return ERROR_MINIMO_DE_CARACTERES;
  }

  const char* formato = obtenerFormatoDeDato(tipo);
  if (formato == NULL) return false;
  for (int i = 0; buffer[i] != 0; i++) {
    if (strchr(formato, buffer[i]) == NULL) return ERROR_FORMATO_INVALIDO;
  }

  if (tipo == CEDULA) aplicarFormatoCedula(buffer);
  if (tipo == FECHA_DE_NACIMIENTO) return validarFecha(buffer);

  return 0;
}


void leerDato(Tipo_de_Dato tipo, char* puntero) {
  int error;

  char bufferDeEntrada[41] = {0};
  const char* ejemplo = ejemploDeFormato(tipo);

  do {
    error = 0;

    printf("%s%s: ", Nombre_de_Datos[tipo], ejemplo ? ejemplo : "");
    scanf(" %40[^\n]", bufferDeEntrada);
    limpiarBuffer();

    error = validarDato(tipo, bufferDeEntrada);

    switch(error) {
      case ERROR_MAXIMO_DE_CARACTERES:
        printf("\e[91mel máximo de caracteres es %d.\e[0m\n\n", datoMaxChars[tipo]);
        break;
      case ERROR_MINIMO_DE_CARACTERES:
        printf("\e[91mel minimo de caracteres es %d.\e[0m\n\n", datoMinChars(tipo));
        break;
      case ERROR_FORMATO_INVALIDO:
        printf("\e[91m%s inválid%c.\e[0m\n\n", Nombre_de_Datos_Minusculas[tipo], datoTerminaConA(tipo) ? 'a': 'o');
        break;
      case ERROR_FECHA_INVALIDA:
        printf("\e[91m%s inválida.\e[0m\n\n", Nombre_de_Datos_Minusculas[FECHA_DE_NACIMIENTO]);
        break;
      case ERROR_CLIENTE_MENOR_EDAD:
        printf("\e[91mtienes que tener 18 años o más.\e[0m\n\n");
        break;
    }
  } while(error);

  printf("\n");

  strcpy(puntero, bufferDeEntrada);

  return;
}

