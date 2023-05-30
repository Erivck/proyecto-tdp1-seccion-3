#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include <stdbool.h>
#include <time.h>

#define CLIENTE_NUM_CAMPOS 13

// Estructura de datos un Cliente
typedef struct {
  char usuario[16];
  char clave[21];
  char nombres[21];
  char apellidos[21];
  char cedula[9];
  char sexo[2];
  char fechaDeNacimiento[11];
  char telefono[12];
  struct {
    char estado[21];
    char ciudad[21];
    char municipio[21];
    char direccion[41];
    char codigoPostal[5];
  } datos_direccion;
} Cliente;

// Enumeracion de datos de un cliente
typedef enum {
  Usuario,
  Clave,
  Nombres,
  Apellidos,
  Cedula,
  Sexo,
  FechaDeNacimiento,
  Telefono,
  Estado,
  Ciudad,
  Municipio,
  Direccion,
  CodigoPostal,
} Datos_de_Cliente;


// Busca en clientes.dat al cliente con el nombre de usuario recibido como parametro, y lo almacena en el puntero "cliente",
// retorna true si lo encuentra o false si no.
bool buscarCliente(Datos_de_Cliente tipo, char* dato, Cliente* cliente);

// Registra en clientes.dat al cliente que hace referencia el puntero "cliente" recibido como parametro
// retorna true si se registra exitosamente al cliente y false en el caso contrario.
bool registrarCliente(Cliente* cliente);

// Retorna la cadena de el campo del cliente recivido como puntero.
char* obtenerDatoDeCliente(Datos_de_Cliente dato, Cliente* cliente);

// Inicializa los campos del la estructura cliente que recibe como puntero a cero;
void inicializarCliente(Cliente* cliente);


bool actualizarDatosDeCliente(char* usuario, Cliente* cliente);

bool eliminarCliente(char* usuario);

#endif // CLIENTE_H_INCLUDED
