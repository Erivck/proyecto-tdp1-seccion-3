#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../cliente.h"


bool existeCliente(char* usuario) {
  Cliente cliente;

  FILE* clientes = fopen("data/clientes.dat", "rb");

  if (clientes == NULL) return false;

  while(fread(&cliente, sizeof(Cliente), 1, clientes)) {
    if (strcmp(cliente.usuario, usuario) == 0) return true;
  }

  fclose(clientes);

  return false;
}

bool buscarCliente(char* usuario, Cliente* cliente) {
  bool encontrado = false;

  FILE* clientes = fopen("data/clientes.dat", "rb");

  if (clientes == NULL) return false;

  while(fread(cliente, sizeof(Cliente), 1, clientes)) {
    if (strcmp(cliente->usuario, usuario) == 0)
      encontrado = true;
  }

  fclose(clientes);

  return encontrado;
}

bool crearCliente(Cliente* cliente) {
  bool creado = false;

  FILE* clientes = fopen("data/clientes.dat", "ab");

  if (clientes == NULL) return false;

  if (fwrite(cliente, sizeof(Cliente), 1, clientes)) creado = true;

  fclose(clientes);

  return creado;
}
