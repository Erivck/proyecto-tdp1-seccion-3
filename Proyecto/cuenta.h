#ifndef CUENTA_H_INCLUDED
#define CUENTA_H_INCLUDED

#include <stdbool.h>
#include <time.h>
#include "cliente.h"

#define NUM_TIPOS_DE_CUENTA 3

#define CUENTA_NUM_CAMPOS 4

// Enumeracion de Tipos de Cuenta
typedef enum {
  CORRIENTE,
  AHORRO,
  DIVISA
} Tipo_de_Cuenta;

// Estructura de datos de una Cuenta de un Cliente
typedef struct {
  char numeroDeCuenta[11];
  char cedulaDeCliente[9];
  char telefonoDeCliente[12];
  Tipo_de_Cuenta tipo;
  long double saldo;
} Cuenta;

// Enumeracion de datos de cuenta
typedef enum {
  NumeroDeCuenta = 13,
  CedulaDeCliente,
  TelefonoDeCliente,
  TipoDeCuenta
} Datos_de_Cuenta;


typedef struct {
  char numeroDeCuenta[11];
  Tipo_de_Cuenta tipo;
  long double ingreso;
  long double egreso;
  long double total;
  time_t fecha;
} Movimiento_de_Cuenta;

const char* tipoDeCuenta[3];

bool buscarCuentaPorTipo(Tipo_de_Cuenta tipo, char* cedulaDelCliente, Cuenta* cuenta);

bool buscarCuenta(Datos_de_Cuenta tipo, char* dato, Cuenta* cuenta);

Cuenta** buscarCuentasCliente(Cliente* cliente);

bool registrarCuentaDeCliente(Tipo_de_Cuenta tipo, Cliente* cliente);

bool inicializarCuenta(Tipo_de_Cuenta tipo, Cuenta* cuenta, Cliente* cliente);

int numCuentasRegistradas(void);

const char* obtenerDatoDeCuenta(Datos_de_Cuenta dato, Cuenta* cuenta);

bool eliminarCuenta(char* numeroDeCuenta);

bool actualizarDatosDeCuenta(char* numeroDeCuenta, Cuenta* cuenta);

bool registrarMovimientoDeCuenta(Movimiento_de_Cuenta* movimiento);

#endif // CUENTA_H_INCLUDED
