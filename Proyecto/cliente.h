#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include <stdbool.h>

typedef struct {
  char usuario[16];
  char clave[21];
  char nombre[16];
  char apellido[16];
  char cedula[9];
} Cliente;

bool buscarCliente(char* usuario, Cliente* cliente);

bool crearCliente(Cliente* cliente);

bool existeCliente(char* usuario);


#endif // CLIENTE_H_INCLUDED
