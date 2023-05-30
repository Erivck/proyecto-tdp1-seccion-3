#ifndef SERVICIO_H_INCLUDED
#define SERVICIO_H_INCLUDED

#include "cliente.h"
#include "cuenta.h"

#define CLAVE_SISTEMA "admin1234"
#define PORCENTAJE_DE_COMISION 0.1


typedef void (*funcionCliente)(Cliente* cliente);

typedef void (*funcionCuenta)(Cuenta* cuenta);

typedef void (*funcionVoid)(void);

// Menu de ingreso al sistema, el cual solicita el usuario y la clave del cliente
void bancoIngresarCliente(void);

// Menu de registro, le pide al cliente sus datos para el registro en el sistema
void bancoRegistrarCliente(void);

void bancoIngresarSistema(void);

void bancoMenuSistema(void);

// Menu correspondiente a un ingreso exitoso, en el que se listan las operaciones que puede realizar el cliente
// recibe como parametro un puntero al cliente ingresado.
void bancoMenuCliente(Cliente* cliente);

void datosCliente(Cliente* cliente);


void menu(
  char* titulo,
  int numOpciones,
  const char* opciones[],
  funcionVoid funciones[]
);

void menuCliente(
  char* titulo,
  int numOpciones,
  const char* opciones[],
  funcionCliente funciones[],
  Cliente* cliente
);

void menuCuenta(
  char* titulo,
  int numOpciones,
  const char* opciones[],
  funcionCuenta funciones[],
  Cuenta* cuenta
);


void consultarDatos(Cliente* cliente);

void actualizarDatosDireccion(Cliente* cliente);

void modificarDatos(Cliente* cliente);

bool eliminarClienteMenu(Cliente* cliente);

void abrirCuenta (Cliente* cliente);

void verCuentas (Cliente* cliente);

void datosDeCuenta(Cuenta* cuenta);

void estadoDeCuenta(Cuenta* cuenta);

void verPagoMovil (Cliente* cliente);

bool menuDeSeleccionDeCuenta (const char* titulo, const char* mensaje, Cliente* cliente, Cuenta* cuenta);

void crearPagoMovil (Cliente* cliente);

void verDatosPagoMovil (Cliente* cliente);

void modificarPagoMovil (Cliente* cliente);

void realizarTransferencia(Cliente* cliente);

void realizarPagoMovil(Cliente* cliente);

void realizarRetiro(void);

void realizarDeposito(void);



#endif // SERVICIO_H_INCLUDED
