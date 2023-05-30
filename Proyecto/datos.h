#ifndef FORMATOS_H_INCLUDED
#define FORMATOS_H_INCLUDED

#include <stdbool.h>

// Máximo de caracteres permitidos para cada campo de la estructura Cuenta
#define USUARIO_MAX 15
#define CLAVE_MAX 20
#define NOMBRES_MAX 20
#define APELLIDOS_MAX 20
#define CEDULA_MAX 8
#define SEXO_MAX 1
#define FECHA_DE_NACIMIENTO_MAX 10
#define TELEFONO_MAX 11
#define ESTADO_MAX 20
#define CIUDAD_MAX 20
#define MUNICIPIO_MAX 20
#define DIRECCION_MAX 40
#define CODIGO_POSTAL_MAX 4
#define NUMERO_DE_CUENTA_MAX 10

#define NUM_TIPOS_DE_DATOS 17

extern const char* Nombre_de_Datos[NUM_TIPOS_DE_DATOS];

//Tipos de formato de texto.
typedef enum {
  numerico,
  alfabetico,
  alfanumerico,
  texto,
  formatoDeUsuario,
  fecha,
} Tipo_de_Formato;

//Enumeración de los tipos de datos del proyecto.
typedef enum {
  USUARIO,
  CLAVE,
  NOMBRES,
  APELLIDOS,
  CEDULA,
  SEXO,
  FECHA_DE_NACIMIENTO,
  TELEFONO,
  ESTADO,
  CIUDAD,
  MUNICIPIO,
  DIRECCION,
  CODIGO_POSTAL,
  NUMERO_DE_CUENTA
} Tipo_de_Dato;

// Enumeración de Errores posibles de validación.
enum Errores_de_Validacion {
  ERROR_MAXIMO_DE_CARACTERES = 1,
  ERROR_MINIMO_DE_CARACTERES,
  ERROR_FORMATO_INVALIDO,
  ERROR_FECHA_INVALIDA,
  ERROR_CLIENTE_MENOR_EDAD
};


// Retorna la cadena de formato correspondiente al tipo de dato recibido como parametro.
const char* obtenerFormatoDeDato(Tipo_de_Dato tipo);

// Valida la cadena del parametro buffer de acuerdo al formato correspondiente tipo recibido como parametro,
// retorna 0 si hubo errores de validación o un valor de la enumeración Errores_de_Validacion correspondiente al error.
int validarDato(Tipo_de_Dato tipo, char* buffer);

// Consulta, lee y valida el tipo de dato recibido como parametro, y lo almacena en el parametro puntero.
void leerDato(Tipo_de_Dato tipo, char* puntero);



#endif // FORMATOS_H_INCLUDED
