#include "../cuenta.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* tipoDeCuenta[] = {
  "Corriente",
  "Ahorro",
  "Divisa"
};

const char* Nombre_de_Dato_de_Cuenta[] = {
  "Número de Cuenta",
  "Cédula del Cliente",
  "Teléfono de Pago Móvil",
  "Tipo de Cuenta"
};


bool registrarCuentaDeCliente (Tipo_de_Cuenta tipo, Cliente* cliente) {
  bool registrado = false;
  Cuenta cuentaNueva;

  if (!inicializarCuenta(tipo, &cuentaNueva, cliente)) return false;

  FILE* cuentas = fopen("data/cuentas.dat", "ab");

  if (cuentas == NULL) return false;

  if (fwrite(&cuentaNueva, sizeof(Cuenta), 1, cuentas)) registrado = true;

  fclose(cuentas);

  return registrado;
}


bool buscarCuentaPorTipo(Tipo_de_Cuenta tipo, char* cedulaDelCliente, Cuenta* cuenta) {
  bool encontrado = false;
  Cuenta* cuentaptr = cuenta ? cuenta : malloc(sizeof(Cuenta));

  FILE* cuentas = fopen("data/cuentas.dat", "rb");

  if (cuentas == NULL) return false;

  while(fread(cuentaptr, sizeof(Cuenta), 1, cuentas)) {
    if (strcmp(cuentaptr->cedulaDeCliente, cedulaDelCliente) == 0 && tipo == cuentaptr->tipo) {
      encontrado = true;
      break;
    }
  }

  fclose(cuentas);

  if (cuenta == NULL) free(cuentaptr);

  return encontrado;
}



bool buscarCuenta(Datos_de_Cuenta tipo, char* dato, Cuenta* cuenta) {
  if (tipo == TipoDeCuenta) return false;

  bool encontrado = false;
  Cuenta* cuentaptr = cuenta ? cuenta : malloc(sizeof(Cuenta));

  FILE* cuentas = fopen("data/cuentas.dat", "rb");

  if (cuentas == NULL) return false;

  while(fread(cuentaptr, sizeof(Cuenta), 1, cuentas)) {
    if (strcmp(obtenerDatoDeCuenta(tipo, cuentaptr), dato) == 0) {
      encontrado = true;
      break;
    }
  }

  fclose(cuentas);

  if (cuenta == NULL) free(cuentaptr);

  return encontrado;
}




Cuenta** buscarCuentasCliente (Cliente* cliente) {
  int i = 0;
  Cuenta temp;

  Cuenta** cuentasCliente = calloc(NUM_TIPOS_DE_CUENTA, sizeof(Cuenta*));

  FILE* cuentas = fopen("data/cuentas.dat", "rb");
  printf("hola\n");

  if (cuentas == NULL) return NULL;


  while(fread(&temp, sizeof(Cuenta), 1, cuentas)) {
    if (strcmp(temp.cedulaDeCliente, cliente->cedula) == 0) {
        cuentasCliente[i] = malloc(sizeof(Cuenta));
        *cuentasCliente[i] = temp;
        i++;
        if (i == NUM_TIPOS_DE_CUENTA) break;
    }
  }

  fclose(cuentas);

  return cuentasCliente;
}


int numCuentasRegistradas () {
  FILE* cuentas = fopen("data/cuentas.dat", "rb");
  Cuenta temp;

  if (cuentas == NULL) return 0;

  int total = 0;

  while(fread(&temp, sizeof(Cuenta), 1, cuentas)) total++;

  fclose(cuentas);

  return total;
}


bool inicializarCuenta(Tipo_de_Cuenta tipo, Cuenta* cuenta, Cliente* cliente) {
  char numeroDeCuenta[11];
  int numero = numCuentasRegistradas();

  sprintf(numeroDeCuenta, "%010d", numero+1);

  cuenta->saldo = 0;
  cuenta->tipo = tipo;
  cuenta->telefonoDeCliente[0] = 0;
  strcpy(cuenta->numeroDeCuenta, numeroDeCuenta);
  strcpy(cuenta->cedulaDeCliente, cliente->cedula);

  return true;
}


const char* obtenerDatoDeCuenta(Datos_de_Cuenta dato, Cuenta* cuenta) {
  switch(dato) {
  case CedulaDeCliente:
    return cuenta->cedulaDeCliente;
  case NumeroDeCuenta:
    return cuenta->numeroDeCuenta;
  case TelefonoDeCliente:
    return cuenta->telefonoDeCliente;
  case TipoDeCuenta:
    return tipoDeCuenta[cuenta->tipo];
  default:
    return NULL;
  }
}


bool actualizarDatosDeCuenta(char* numeroDeCuenta, Cuenta* cuenta) {
  Cuenta temp;

  FILE* cuentas = fopen("data/cuentas.dat", "rb");
  FILE* cuentasNuevo = fopen("data/cuentas_temp.dat", "ab");

  if (cuentas == NULL || cuentasNuevo == NULL) return false;

  while (fread(&temp, sizeof(Cuenta), 1, cuentas)) {
    if (strcmp(temp.numeroDeCuenta, numeroDeCuenta) != 0) {
      fwrite(&temp, sizeof(Cuenta), 1, cuentasNuevo);
    } else {
      fwrite(cuenta, sizeof(Cuenta), 1, cuentasNuevo);
    }
  }

  fclose(cuentas);
  fclose(cuentasNuevo);

  remove("data/cuentas.dat");
  rename("data/cuentas_temp.dat", "data/cuentas.dat");

  return true;
}

bool eliminarCuenta(char* numeroDeCuenta) {
  Cuenta temp;

  FILE* cuentas = fopen("data/cuentas.dat", "rb");
  FILE* cuentasNuevo = fopen("data/cuentas_temp.dat", "ab");

  if (cuentas == NULL || cuentasNuevo == NULL) return false;

  while (fread(&temp, sizeof(Cuenta), 1, cuentas)) {
    if (strcmp(temp.numeroDeCuenta, numeroDeCuenta) != 0)
      fwrite(&temp, sizeof(Cuenta), 1, cuentasNuevo);
  }

  fclose(cuentas);
  fclose(cuentasNuevo);

  remove("data/clientes.dat");
  rename("data/clientes_temp.dat", "data/clientes.dat");

  return true;
}


bool registrarMovimientoDeCuenta(Movimiento_de_Cuenta* movimiento) {
  bool registrado = false;

  FILE* movimientos = fopen("data/movimientos.dat", "ab");

  if (movimientos == NULL) return false;

  if (fwrite(movimiento, sizeof(Movimiento_de_Cuenta), 1, movimientos)) registrado = true;

  fclose(movimientos);

  return registrado;
}
