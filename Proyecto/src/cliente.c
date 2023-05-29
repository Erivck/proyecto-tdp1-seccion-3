#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../cliente.h"
#include "../datos.h"


bool registrarCliente(Cliente* cliente) {
  bool registrado = false;

  FILE* clientes = fopen("data/clientes.dat", "ab");

  if (clientes == NULL) return false;

  if (fwrite(cliente, sizeof(Cliente), 1, clientes)) registrado = true;

  fclose(clientes);

  return registrado;
}


bool buscarCliente(Datos_de_Cliente tipo, char* dato, Cliente* cliente) {
  bool encontrado = false;
  Cliente* clienteptr = cliente ? cliente : malloc(sizeof(Cliente));

  FILE* clientes = fopen("data/clientes.dat", "rb");

  if (clientes == NULL) return false;

  while(fread(clienteptr, sizeof(Cliente), 1, clientes)) {
    if (strcmp(obtenerDatoDeCliente(tipo, clienteptr), dato) == 0) {
      encontrado = true;
      break;
    }
  }

  fclose(clientes);

  if (cliente == NULL) free(clienteptr);

  return encontrado;
}

bool actualizarDatosDeCliente(char* usuario, Cliente* cliente) {
  Cliente temp;

  FILE* clientes = fopen("data/clientes.dat", "rb");
  FILE* clientesNuevo = fopen("data/clientes_temp.dat", "ab");

  if (clientes == NULL || clientesNuevo == NULL) return false;

  while (fread(&temp, sizeof(Cliente), 1, clientes)) {
    if (strcmp(temp.usuario, usuario) != 0) {
      fwrite(&temp, sizeof(Cliente), 1, clientesNuevo);
    } else {
      fwrite(cliente, sizeof(Cliente), 1, clientesNuevo);
    }
  }

  fclose(clientes);
  fclose(clientesNuevo);

  remove("data/clientes.dat");
  rename("data/clientes_temp.dat", "data/clientes.dat");

  return true;
}

bool eliminarCliente(char* usuario) {
  Cliente temp;

  FILE* clientes = fopen("data/clientes.dat", "rb");
  FILE* clientesNuevo = fopen("data/clientes_temp.dat", "ab");

  if (clientes == NULL || clientesNuevo == NULL) return false;

  while (fread(&temp, sizeof(Cliente), 1, clientes)) {
    if (strcmp(temp.usuario, usuario) != 0)
      fwrite(&temp, sizeof(Cliente), 1, clientesNuevo);
  }

  fclose(clientes);
  fclose(clientesNuevo);

  remove("data/clientes.dat");
  rename("data/clientes_temp.dat", "data/clientes.dat");

  return true;
}

void inicializarCliente(Cliente* cliente) {
  for (Datos_de_Cliente dato = Usuario; dato < CLIENTE_NUM_CAMPOS; dato++){
    char* datoCliente = obtenerDatoDeCliente(dato, cliente);
    datoCliente[0] = 0;
  }
}


char* obtenerDatoDeCliente(Datos_de_Cliente dato, Cliente* cliente) {
  switch (dato) {
    case Usuario:
      return cliente->usuario;
    case Clave:
      return cliente->clave;
    case Nombres:
      return cliente->nombres;
    case Apellidos:
      return cliente->apellidos;
    case Cedula:
      return cliente->cedula;
    case Sexo:
      return cliente->sexo;
    case FechaDeNacimiento:
      return cliente->fechaDeNacimiento;
    case Telefono:
      return cliente->telefono;
    case Estado:
      return cliente->datos_direccion.estado;
    case Ciudad:
      return cliente->datos_direccion.ciudad;
    case Municipio:
      return cliente->datos_direccion.municipio;
    case Direccion:
      return cliente->datos_direccion.direccion;
    case CodigoPostal:
      return cliente->datos_direccion.codigoPostal;
    default:
      return NULL;
  }
}
