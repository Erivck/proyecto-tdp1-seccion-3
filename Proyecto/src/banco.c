#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../datos.h"
#include "../banco.h"
#include "../cliente.h"
#include "../utils.h"
#include "../cuenta.h"

#define NUM_OPCIONES_BANCO 5
#define NUM_OPCIONES_DATOS 3
#define NUM_OPCIONES_CUENTAS 3
#define NUM_OPCIONES_OPERACIONES 2
#define NUM_OPCIONES_CUENTA 2


// SISTEMA DE INGRESO DEL BANCO:

void bancoIngresarCliente() {
  char usuario[16];
  char clave[21];
  Cliente cliente;

  limpiarPantalla();

  printf("\t\tINGRESAR COMO CLIENTE:\n\n\v");

  leerDato(USUARIO, usuario);

  if (!buscarCliente(Usuario, usuario, &cliente)) {
    printf("\nEl usuario \"%s\" no existe.\n\n", usuario);
    esperarEntrada();
    return;
  }

  leerDato(CLAVE, clave);

  if (strcmp(clave, cliente.clave) != 0) {
    printf("\nClave incorrecta.\n\n");
    esperarEntrada();
    return;
  }

  bancoMenuCliente(&cliente);
}


void bancoRegistrarCliente() {
  Cliente cliente;
  inicializarCliente(&cliente);

  limpiarPantalla();

  printf("\t\tREGISTRAR CLIENTE:\n\n\v");

  leerDato(USUARIO, cliente.usuario);

  if (buscarCliente(Usuario, cliente.usuario, NULL)) {
    printf("\nEl usuario \"%s\" ya existe.\n\n", cliente.usuario);
    esperarEntrada();
    return;
  }

  leerDato(CLAVE, cliente.clave);
  leerDato(NOMBRES, cliente.nombres);
  leerDato(APELLIDOS, cliente.apellidos);
  leerDato(CEDULA, cliente.cedula);

  if (buscarCliente(Cedula, cliente.cedula, NULL)) {
    printf("\nEl número de cedula \"%s\" ya se encuentra registrado.\n\n", cliente.cedula);
    esperarEntrada();
    return;
  }

  leerDato(SEXO, cliente.sexo);
  leerDato(FECHA_DE_NACIMIENTO, cliente.fechaDeNacimiento);

  registrarCliente(&cliente);

  printf("\nCliente registrado exitosamente.\n\n");

  esperarEntrada();
}



void bancoIngresarSistema() {
  char clave[21];

  limpiarPantalla();

  printf("\t\tINGRESAR SISTEMA:\n\n\v");

  leerDato(CLAVE, clave);

  if (strcmp(clave, CLAVE_SISTEMA) != 0) {
    printf("\nClave incorrecta.\n\n");
    esperarEntrada();
    return;
  }

  bancoMenuSistema();
}



void bancoMenuSistema() {
  int numOpciones = 2;

  const char* opciones[] = {
    "Realizar Deposito.",
    "Realizar Retiro."
  };

  funcionVoid funciones[] = {
    realizarDeposito,
    realizarRetiro
  };

  menu("SISTEMA DE SERVICIO BANCARIO", numOpciones, opciones, funciones);
}



// MENU PRINCIPAL DEL BANCO:

enum Opciones_Banco {
  DATOS_CLIENTE = 1,
  CUENTAS_CLIENTE,
  OPERACIONES,
  ELIMINAR_CLIENTE
};

const char* opcionesBanco[] = {
  "Datos del Cliente.",
  "Cuentas.",
  "Operaciones.",
  "Eliminar Cliente.",
  "Cerrar Sesión."
};

const char* opcionesDatos[] = {
  "Consultar Datos.",
  "Actualizar Datos de Dirección.",
  "Modificar Datos.",
};

const char* opcionesCuentas[] = {
  "Abrir cuenta.",
  "Ver cuentas.",
  "Pago Movil.",
};

const char* opcionesOperaciones[] = {
  "Transferencia.",
  "Pago Movil.",
};


funcionCliente funcionesDatos[] = {
  consultarDatos,
  actualizarDatosDireccion,
  modificarDatos
};

funcionCliente funcionesCuentas[] = {
  abrirCuenta,
  verCuentas,
  verPagoMovil
};

funcionCliente funcionesOperaciones[] = {
  realizarTransferencia,
  realizarPagoMovil
};

void bancoMenuCliente(Cliente* cliente) {
    int opcion;

  char nombre[21];
  char apellido[21];
  sscanf(cliente->nombres, "%s", nombre);
  sscanf(cliente->apellidos, "%s", apellido);

  do
  {
    limpiarPantalla();
    opcion = 0;

    printf("\t  ---SERVICIO DE ATENCIÓN AL CLIENTE---\n\n\v");
    printf("Bienvenido %s %s, seleccione una de la opciones:\n\n", nombre, apellido);

    for (int i = 0; i < NUM_OPCIONES_BANCO; i++) {
      printf("%d. %s\n", i+1, opcionesBanco[i]);
    }

    printf("\nIntroduzca una opción: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    switch (opcion) {
      case DATOS_CLIENTE:
        menuCliente("DATOS DEL CLIENTE", NUM_OPCIONES_DATOS, opcionesDatos, funcionesDatos, cliente);
        break;
      case CUENTAS_CLIENTE:
        menuCliente("CUENTAS", NUM_OPCIONES_CUENTAS, opcionesCuentas, funcionesCuentas, cliente);
        break;
      case OPERACIONES:
        menuCliente("OPERACIONES", NUM_OPCIONES_OPERACIONES, opcionesOperaciones, funcionesOperaciones, cliente);
        break;
      case ELIMINAR_CLIENTE:
        if (eliminarClienteMenu(cliente)) return;
        break;
    }
  } while(opcion != 5);

}






void consultarDatos(Cliente* cliente) {
  limpiarPantalla();

  printf("\t\t---CONSULTAR DATOS---\n\n\v");

  for (Datos_de_Cliente dato = Usuario; dato < CLIENTE_NUM_CAMPOS; dato++){
    if (dato == Clave) continue;
    char* datoCliente = obtenerDatoDeCliente(dato, cliente);
    if (datoCliente[0] != 0) printf("%s: %s\n", Nombre_de_Datos[dato], datoCliente);
  }
  printf("\n");

  esperarEntrada();
}


void actualizarDatosDireccion(Cliente* cliente) {
  bool actualizado;

  limpiarPantalla();

  printf("\t\t---ACTUALIZAR DATOS DE DIRECCIÓN---\n\n\v");

  leerDato(ESTADO, cliente->datos_direccion.estado);
  leerDato(CIUDAD, cliente->datos_direccion.ciudad);
  leerDato(MUNICIPIO, cliente->datos_direccion.municipio);
  leerDato(DIRECCION, cliente->datos_direccion.direccion);
  leerDato(CODIGO_POSTAL, cliente->datos_direccion.codigoPostal);

  actualizado = actualizarDatosDeCliente(cliente->usuario, cliente);

  if (!actualizado) {
    printf("Ocurrió un error al intentar actualizar los datos del cliente.\n\n");
    esperarEntrada();
    return;
  }

  printf("\nDatos de dirección registrados exitosamente.\n\n");
  esperarEntrada();
}


void modificarDatos(Cliente* cliente) {
  char clave[21];
  int numDatosAModificar = 7;
  Tipo_de_Dato datoAModificar;
  int opcion;

  do {
    opcion = 0;
    limpiarPantalla();

    printf("\t\t---MODIFICAR DATOS---\n\n\v");

    for (int i = 0; i < numDatosAModificar; i++) {
      printf("%d. %s.\n", i+1, Nombre_de_Datos[i]);
    }
    printf("8. Salir\n\n");

    printf("Introduzca una opción a modificar: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    if (opcion > 0 && opcion < 8) {
      bool modificado = false;
      datoAModificar = opcion - 1;
      char usuario[16];
      strcpy(usuario, cliente->usuario);

      limpiarPantalla();

      printf("\t\t---MODIFICAR DATOS---\n\n\v");

      printf("Introduzca Clave Actual: ");
      scanf("%20[^\n]", clave);
      printf("\n");
      limpiarBuffer();


      if (strcmp(clave, cliente->clave) != 0) {
        printf("Clave incorrecta.\n\n");
        esperarEntrada();
        continue;
      }

      leerDato(datoAModificar, obtenerDatoDeCliente((Datos_de_Cliente)datoAModificar, cliente));

      modificado = actualizarDatosDeCliente(usuario, cliente);

      if (!modificado) {
        printf("Ocurrió un error al intentar actualizar los datos del cliente.\n\n");
        esperarEntrada();
        return;
      }


      printf("\n%s actualizado exitosamente.\n\n", Nombre_de_Datos[datoAModificar]);
      esperarEntrada();
    }
  } while(opcion != numDatosAModificar+1);
}


bool eliminarClienteMenu(Cliente* cliente) {
  bool eliminado = false;
  char clave[21];

  limpiarPantalla();

  printf("\t\t---ELIMINAR CLIENTE---\n\n\v");

  leerDato(CLAVE, clave);

  if (strcmp(cliente->clave, clave) == 0) {
    eliminado = eliminarCliente(cliente->usuario);
  } else {
    printf("Clave incorrecta.\n\n");
    esperarEntrada();
    return eliminado;
  }

  if (!eliminado) {
    printf("Ocurrió un error al intentar eliminar la cuenta.\n\n");
    esperarEntrada();
    return eliminado;
  }

  printf("Cuenta del cliente eliminada exitosamente.\n\n");
  esperarEntrada();
  return eliminado;
}


void abrirCuenta (Cliente* cliente) {
  int opcion;
  Tipo_de_Cuenta tipo;

  do {
    opcion = 0;
    limpiarPantalla();

    printf("\t\t---ABRIR CUENTA---\n\n\v");

    printf("Seleccione el tipo de Cuenta:\n\n");

    for (int i = 0; i < NUM_TIPOS_DE_CUENTA; i++) {
      printf("%d. %s.\n", i+1, tipoDeCuenta[i]);
    }
    printf("%d. Salir.\n\n", NUM_TIPOS_DE_CUENTA+1);

    printf("Ingrese una opción: ");
    scanf(" %d", &opcion);
    limpiarBuffer();

    if (opcion > 0 && opcion < NUM_TIPOS_DE_CUENTA+1) {

      tipo = opcion - 1;

      if (buscarCuentaPorTipo(tipo, cliente->cedula, NULL)) {
        printf("\n\nYa tiene una cuenta %s.\n\n", tipoDeCuenta[tipo]);
        esperarEntrada();
        return;
      }

      if (!registrarCuentaDeCliente(tipo, cliente)) {
        printf("\n\nOcurrió un error al registrar la cuenta.\n\n");
        esperarEntrada();
        return;
      }

      printf("\n\nCuenta registrada exitosamente.\n\n");
      esperarEntrada();
      return;
    }

  } while(opcion != NUM_TIPOS_DE_CUENTA+1);
}



const char* cuentaOpciones[] = {
  "Ver Datos de Cuenta.",
  "Ver Estado de Cuenta.",
};

funcionCuenta funcionesCuenta[] = {
  datosDeCuenta,
  estadoDeCuenta
};


void verCuentas (Cliente* cliente) {
  Cuenta cuenta;
  bool cuentaSeleccionada;
  char titulo[18];

  cuentaSeleccionada = menuDeSeleccionDeCuenta(NULL, NULL, cliente, &cuenta);

  if (!cuentaSeleccionada) return;

  sprintf(titulo, "CUENTA %s", cuenta.numeroDeCuenta);

  menuCuenta(titulo, NUM_OPCIONES_CUENTA, cuentaOpciones, funcionesCuenta, &cuenta);

}


bool menuDeSeleccionDeCuenta (const char* titulo, const char* mensaje, Cliente* cliente, Cuenta* cuenta) {
  int opcion, numCuentas = 0;
  Cuenta** cuentasDelCliente = buscarCuentasCliente(cliente);

  if (cuentasDelCliente) {
    for (int i = 0; cuentasDelCliente[i]; i++) numCuentas += 1;
  }

  do {
    opcion = 0;
    limpiarPantalla();

    printf("\t\t---%s---\n\n\v", titulo ? titulo : "CUENTAS DEL CLIENTE");

    if(!numCuentas) {
      printf("No se encontraron cuentas del cliente.\n\n");
      esperarEntrada();
      return false;
    }

    for (int i = 0; cuentasDelCliente[i]; i++) {
        printf("%d. %s (%s).\n", i+1, obtenerDatoDeCuenta(TipoDeCuenta, cuentasDelCliente[i]),
               obtenerDatoDeCuenta(NumeroDeCuenta, cuentasDelCliente[i]));
    }
    printf("%d. Salir.\n\n", numCuentas+1);

    printf("%s: ", mensaje ? mensaje : "Seleccione una de las cuentas");
    scanf("%d", &opcion);
    limpiarBuffer();

    if (opcion > 0 && opcion < numCuentas+1) {
        *cuenta = *cuentasDelCliente[opcion-1];
        return true;
    }
  } while (opcion != numCuentas+1);


  for (int i = 0; i < NUM_TIPOS_DE_CUENTA && cuentasDelCliente[i]; i++ ) {
    free(cuentasDelCliente[i]);
  }
  free(cuentasDelCliente);

  return false;
}




void datosDeCuenta(Cuenta* cuenta) {
  limpiarPantalla();

  printf("\t\t---DATOS DE CUENTA---\n\n\v");

  for (Datos_de_Cuenta dato = NumeroDeCuenta; dato < NumeroDeCuenta+CUENTA_NUM_CAMPOS; dato++) {
    if (dato == CedulaDeCliente) continue;
    const char* datoCuenta = obtenerDatoDeCuenta(dato, cuenta);
    if (datoCuenta[0] != 0) printf("%s: %s\n", Nombre_de_Datos[dato], datoCuenta);
  }
  printf("Saldo: %.2lf %s\n\n", (double) cuenta->saldo, cuenta->tipo == DIVISA ? "$" : "Bs.");

  esperarEntrada();
}

void estadoDeCuenta(Cuenta* cuenta) {
  int opcion;

  const char* estadoCadena[] = {
    "MENSUAL",
    "SEMANAL"
  };

  do {
    opcion = 0;
    limpiarPantalla();

    printf("\t\t---ESTADO DE CUENTA---\n\n\v");

    printf("1. Mensual.\n2. Semanal.\n3. Salir\n\n");

    printf("Seleccione una opción: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    if (opcion > 0 && opcion < 3) {
      limpiarPantalla();

      printf("\t\t\t---ESTADO DE CUENTA %s---\n\n\v", estadoCadena[opcion-1]);

      FILE* movimientos = fopen("movimientos.dat", "rb");
      char fechaMovimiento[11];

      if (movimientos == NULL) {
        printf("Ocurrió un error al revisar los movimientos de la cuenta.\n\n");
        esperarEntrada();
        continue;
      }

      Movimiento_de_Cuenta temp;
      time_t tiempoActual = time(NULL);
      time_t lapsoDeTiempo = opcion == 1 ? 30 * 24 * 60 * 60 : 7 * 24 * 60 * 60;
      time_t tiempoACalcular =  tiempoActual - lapsoDeTiempo;

      printf("+------------+------------------+-------------+------------+-------------+\n");
      printf("|   FECHA    | NÚMERO DE CUENTA |   INGRESO   |   EGRESO   |    TOTAL    |\n");
      printf("+------------+------------------+-------------+------------+-------------+\n");
      while (fread(&temp, sizeof(Movimiento_de_Cuenta), 1, movimientos)) {
        if (strcmp(temp.numeroDeCuenta, cuenta->numeroDeCuenta) == 0 && temp.fecha >= tiempoACalcular) {
          strftime(fechaMovimiento, sizeof fechaMovimiento, "%d/%m/%Y", localtime(&temp.fecha));
          printf("| %-10s |    %-10s    | %-10.2lf  | %-10.2lf | %-10.2lf  |\n", fechaMovimiento,
                 temp.numeroDeCuenta, (double)temp.ingreso, (double)temp.egreso, (double)temp.total);
          printf("+------------+------------------+-------------+------------+-------------+\n");
        }
      }

      fclose(movimientos);

      printf("\n\n");
      esperarEntrada();
    }

  } while (opcion != 3);
}




void verPagoMovil (Cliente* cliente) {
  int numOpciones = 4;

  const char* opcionesPagoMovil[] = {
    "Crear Pago Móvil.",
    "Ver Datos de Pago Móvil.",
    "Modificar Pago Móvil.",
    "Salir."
  };

  funcionCliente funcionesPagoMovil[] = {
    crearPagoMovil,
    verDatosPagoMovil,
    modificarPagoMovil
  };

  menuCliente("PAGO MÓVIL", numOpciones, opcionesPagoMovil, funcionesPagoMovil, cliente);
}


void crearPagoMovil (Cliente* cliente) {
  bool telefonoActualizado = false, cuentaActualizada = false;
  Cuenta cuenta;

  limpiarPantalla();

  printf("\t\t---CREAR PAGO MÓVIL---\n\n\v");


  leerDato(TELEFONO, cliente->telefono);

  if (!menuDeSeleccionDeCuenta("CREAR PAGO MÓVIL", "Seleccione cuenta a la cual vincular el pago móvil", cliente, &cuenta)) {
    strcpy(cliente->telefono, "");
    return;
  }

  strcpy(cuenta.telefonoDeCliente, cliente->telefono);

  telefonoActualizado = actualizarDatosDeCliente(cliente->usuario, cliente);

  if (!telefonoActualizado) {
    printf("\n\nOcurrió un error al intentar actualizar los datos del cliente.\n\n");
    esperarEntrada();
    return;
  }


  cuentaActualizada = actualizarDatosDeCuenta(cuenta.numeroDeCuenta, &cuenta);

  if (!cuentaActualizada) {
    printf("\n\nOcurrió un error al intentar actualizar los datos de la cuenta.\n\n");
    esperarEntrada();
    return;
  }


  printf("\n\nPago móvil creado exitosamente.\n\n");
  esperarEntrada();
}


void verDatosPagoMovil (Cliente* cliente) {
  Cuenta cuenta;

  limpiarPantalla();

  printf("\t\t---VER DATOS PAGO MÓVIL---\n\n\v");

  if (!buscarCuenta(TelefonoDeCliente, cliente->telefono, &cuenta)) {
    printf("No tiene un pago móvil registrado.\n\n");
    esperarEntrada();
    return;
  }


  printf("Número de Teléfono Vinculado: %s\n", cliente->telefono);
  printf("Cuenta de Pago Móvil: %s (%s)\n\n", obtenerDatoDeCuenta(TipoDeCuenta, &cuenta), cuenta.numeroDeCuenta);

  esperarEntrada();
}


void modificarPagoMovil (Cliente* cliente) {
  int opcion;
  Cuenta cuenta;

  do {
    limpiarPantalla();

    printf("\t\t---MODIFICAR PAGO MÓVIL---\n\n\v");

    if (!buscarCuenta(TelefonoDeCliente, cliente->telefono, &cuenta)) {
      printf("No tiene un pago móvil registrado.\n\n");
      esperarEntrada();
      return;
    }

    printf("1. Número de Teléfono.\n2. Cuenta Vinculada\n3. Salir.\n\n");

    printf("Seleccion una opción: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    switch(opcion) {
      case 1: {
        bool cuentaActualizada, telefonoActualizado;
        limpiarPantalla();

        printf("\t\t---CAMBIAR TELÉFONO DE PAGO MOVIL---\n\n\v");

        leerDato(TELEFONO, cliente->telefono);
        strcpy(cuenta.telefonoDeCliente, cliente->telefono);

        telefonoActualizado = actualizarDatosDeCliente(cliente->usuario, cliente);

        if (!telefonoActualizado) {
          printf("\nOcurrió un error al intentar actualizar los datos del cliente.\n\n");
          esperarEntrada();
          continue;
        }

        cuentaActualizada = actualizarDatosDeCuenta(cuenta.numeroDeCuenta, &cuenta);

        if (!cuentaActualizada) {
          printf("\nOcurrió un error al intentar actualizar los datos de la cuenta.\n\n");
          esperarEntrada();
          continue;
        }

        printf("\nSe Cambió el número de pago móvil exitosamente.\n\n");
        esperarEntrada();
        break;
      }
      case 2: {
        bool cuentaActualizada;
        Cuenta cuentaNueva;

        if (!menuDeSeleccionDeCuenta("CAMBIAR CUENTA VINCULADA", "Seleccion cuenta a la cual vincular el pago movil", cliente, &cuentaNueva)) {
          continue;
        }

        limpiarPantalla();

        printf("\t\t---CAMBIAR CUENTA VINCULADA---\n\n\v");

        strcpy(cuentaNueva.telefonoDeCliente, cliente->telefono);
        strcpy(cuenta.telefonoDeCliente, "");

        cuentaActualizada = actualizarDatosDeCuenta(cuenta.numeroDeCuenta, &cuenta) &&
                            actualizarDatosDeCuenta(cuentaNueva.numeroDeCuenta, &cuentaNueva);

        if (!cuentaActualizada) {
          printf("Ocurrió un error al intentar actualizar los datos de la cuenta.\n\n");
          esperarEntrada();
          continue;
        }

        printf("Se Cambió la cuenta vinculada a el pago móvil exitosamente.\n\n");
        esperarEntrada();
        break;
      }
    }
  } while(opcion != 3);
}




void realizarTransferencia(Cliente* cliente) {
  bool cuentaSeleccionada, cuentasActualizadas;
  char numeroDeCuenta[11];
  double monto;
  Cuenta cuenta, cuentaATransferir;
  Movimiento_de_Cuenta movimientoIngreso, movimientoEgreso;

  cuentaSeleccionada = menuDeSeleccionDeCuenta("REALIZAR TRANSFERENCIA", "Seleccione cuenta con la cual realizar la transferencia", cliente, &cuenta);

  if(!cuentaSeleccionada) return;

  limpiarPantalla();

  printf("\t\t---REALIZAR TRANSFERENCIA---\n\n\v");

  printf("Ingrese el Número de Cuenta al cual transferir.\n\n");
  leerDato(NUMERO_DE_CUENTA, numeroDeCuenta);

  if(!buscarCuenta(NumeroDeCuenta, numeroDeCuenta, &cuentaATransferir)) {
    printf("\n\nNo se encontro una cuenta con el número de cuenta %s\n\n", numeroDeCuenta);
    esperarEntrada();
    return;
  }

  printf("Ingrese monto: ");
  scanf("%lf", &monto);
  limpiarBuffer();

  if (monto > cuenta.saldo) {
    printf("\n\nSaldo insuficiente.\n\n");
    esperarEntrada();
    return;
  } else if (monto < 0) {
    printf("\n\nMonto inválido.\n\n");
    esperarEntrada();
    return;
  }

  cuenta.saldo -= monto;
  strcpy(movimientoEgreso.numeroDeCuenta, cuenta.numeroDeCuenta);
  movimientoEgreso.egreso = monto;
  movimientoEgreso.ingreso = 0;
  movimientoEgreso.total = cuenta.saldo;
  movimientoEgreso.fecha = time(NULL);

  cuentaATransferir.saldo += monto;
  strcpy(movimientoIngreso.numeroDeCuenta, cuentaATransferir.numeroDeCuenta);
  movimientoIngreso.ingreso = monto;
  movimientoIngreso.egreso = 0;
  movimientoIngreso.total = cuentaATransferir.saldo;
  movimientoIngreso.fecha = time(NULL);

  cuentasActualizadas = actualizarDatosDeCuenta(cuenta.numeroDeCuenta, &cuenta) &&
                        actualizarDatosDeCuenta(cuentaATransferir.numeroDeCuenta, &cuentaATransferir);

  if (!cuentasActualizadas) {
    cuenta.saldo += monto;
    cuentaATransferir.saldo -= monto;
    while(!(actualizarDatosDeCuenta(cuenta.numeroDeCuenta, &cuenta) &&
            actualizarDatosDeCuenta(cuentaATransferir.numeroDeCuenta, &cuentaATransferir))) ;

    printf("\n\nOcurrió un error al intentar actualizar los datos de las cuentas, se revirtió la operacion.\n\n");
    esperarEntrada();
    return;
  }

  registrarMovimientoDeCuenta(&movimientoEgreso);
  registrarMovimientoDeCuenta(&movimientoIngreso);

  printf("\n\nTransferencia realizada exitosamente.\n\n");
  esperarEntrada();
}



void realizarPagoMovil(Cliente* cliente) {
  bool cuentasActualizadas;
  char telefono[12];
  double monto;
  Cuenta cuenta, cuentaATransferir;
  Movimiento_de_Cuenta movimientoIngreso, movimientoEgreso;

  limpiarPantalla();
  printf("\t\t---REALIZAR PAGO MÓVIL---\n\n\v");

  if (!buscarCuenta(TelefonoDeCliente, cliente->telefono, &cuenta)) {
    printf("No tiene un pago móvil registrado.\n\n");
    esperarEntrada();
    return;
  }

  printf("Ingrese el número de teléfono de Pago Móvil al cual transferir.\n\n");
  leerDato(TELEFONO, telefono);

  if (!buscarCuenta(TelefonoDeCliente, telefono, &cuentaATransferir)) {
    printf("\n\nNo se encontro una cuenta con el número de teléfono %s vinculado.\n\n", telefono);
    esperarEntrada();
    return;
  }

  printf("Ingrese monto: ");
  scanf("%lf", &monto);
  limpiarBuffer();

  if (monto > cuenta.saldo) {
    printf("\n\nSaldo insuficiente.\n\n");
    esperarEntrada();
    return;
  } else if (monto < 0) {
    printf("\n\nMonto inválido.\n\n");
    esperarEntrada();
    return;
  }

  cuenta.saldo -= monto;
  strcpy(movimientoEgreso.numeroDeCuenta, cuenta.numeroDeCuenta);
  movimientoEgreso.egreso = monto;
  movimientoEgreso.ingreso = 0;
  movimientoEgreso.total = cuenta.saldo;
  movimientoEgreso.fecha = time(NULL);

  cuentaATransferir.saldo += monto;
  strcpy(movimientoIngreso.numeroDeCuenta, cuentaATransferir.numeroDeCuenta);
  movimientoIngreso.ingreso = monto;
  movimientoIngreso.egreso = 0;
  movimientoIngreso.total = cuentaATransferir.saldo;
  movimientoIngreso.fecha = time(NULL);

  cuentasActualizadas = actualizarDatosDeCuenta(cuenta.numeroDeCuenta, &cuenta) &&
                        actualizarDatosDeCuenta(cuentaATransferir.numeroDeCuenta, &cuentaATransferir);

  if (!cuentasActualizadas) {
    cuenta.saldo += monto;
    cuentaATransferir.saldo -= monto;
    while(!(actualizarDatosDeCuenta(cuenta.numeroDeCuenta, &cuenta) &&
            actualizarDatosDeCuenta(cuentaATransferir.numeroDeCuenta, &cuentaATransferir))) ;

    printf("\n\nOcurrió un error al intentar actualizar los datos de las cuentas, se revirtió la operacion.\n\n");
    esperarEntrada();
    return;
  }

  registrarMovimientoDeCuenta(&movimientoEgreso);
  registrarMovimientoDeCuenta(&movimientoIngreso);

  printf("\n\nPago móvil realizado exitosamente.\n\n");
  esperarEntrada();
}


void realizarDeposito() {
  bool cuentasActualizada;
  char numeroDeCuenta[11];
  double monto;
  Cuenta cuenta;
  Movimiento_de_Cuenta movimiento;

  limpiarPantalla();
  printf("\t\t---REALIZAR DEPÓSITO---\n\n\v");

  printf("Ingrese el Número de Cuenta a la cual depositar.\n\n");
  leerDato(NUMERO_DE_CUENTA, numeroDeCuenta);

  if(!buscarCuenta(NumeroDeCuenta, numeroDeCuenta, &cuenta)) {
    printf("\n\nNo se encontro una cuenta con el número de cuenta %s\n\n", numeroDeCuenta);
    esperarEntrada();
    return;
  }

  printf("Ingrese monto: ");
  scanf("%lf", &monto);
  limpiarBuffer();

  if (monto < 0) {
    printf("\n\nMonto inválido.\n\n");
    esperarEntrada();
    return;
  }

  cuenta.saldo += monto;
  strcpy(movimiento.numeroDeCuenta, cuenta.numeroDeCuenta);
  movimiento.ingreso = monto;
  movimiento.egreso = 0;
  movimiento.total = cuenta.saldo;
  movimiento.fecha = time(NULL);

  cuentasActualizada = actualizarDatosDeCuenta(cuenta.numeroDeCuenta, &cuenta);

  if (!cuentasActualizada) {
    cuenta.saldo -= monto;

    printf("\n\nOcurrió un error al intentar actualizar los datos de la cuenta, se revirtió la operacion.\n\n");
    esperarEntrada();
    return;
  }

  registrarMovimientoDeCuenta(&movimiento);

  printf("\n\nDepósito realizado exitosamente.\n\n");
  esperarEntrada();

}

void realizarRetiro() {
  bool cuentasActualizada;
  char numeroDeCuenta[11];
  double monto;
  Cuenta cuenta;
  Movimiento_de_Cuenta movimiento;

  limpiarPantalla();
  printf("\t\t---REALIZAR RETIRO---\n\n\v");

  printf("Ingrese el Número de Cuenta a la cual realizar el retiro.\n\n");
  leerDato(NUMERO_DE_CUENTA, numeroDeCuenta);

  if(!buscarCuenta(NumeroDeCuenta, numeroDeCuenta, &cuenta)) {
    printf("\n\nNo se encontro una cuenta con el número de cuenta %s\n\n", numeroDeCuenta);
    esperarEntrada();
    return;
  }

  printf("Ingrese monto: ");
  scanf("%lf", &monto);
  limpiarBuffer();

  if (monto < 0) {
    printf("\n\nMonto inválido.\n\n");
    esperarEntrada();
    return;
  }

  cuenta.saldo -= monto;
  strcpy(movimiento.numeroDeCuenta, cuenta.numeroDeCuenta);
  movimiento.ingreso = 0;
  movimiento.egreso = monto;
  movimiento.total = cuenta.saldo;
  movimiento.fecha = time(NULL);

  cuentasActualizada = actualizarDatosDeCuenta(cuenta.numeroDeCuenta, &cuenta);

  if (!cuentasActualizada) {
    cuenta.saldo += monto;

    printf("\n\nOcurrió un error al intentar actualizar los datos de la cuenta, se revirtió la operacion.\n\n");
    esperarEntrada();
    return;
  }

  registrarMovimientoDeCuenta(&movimiento);

  printf("\n\nRetiro realizado exitosamente.\n\n");
  esperarEntrada();

}




void menuCliente(
  char* titulo,
  int numOpciones,
  const char* opciones[],
  funcionCliente funciones[],
  Cliente* cliente
) {
  int opcion, salir = numOpciones+1;

  do
  {
    limpiarPantalla();
    opcion = 0;

    printf("\t\t---%s---\n\n\v", titulo);

    for (int i = 0; i < numOpciones; i++) {
      printf("%d. %s\n", i+1, opciones[i]);
    }
    printf("%d. Salir.\n", salir);

    printf("\nIntroduzca una opción: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    if (opcion > 0 && opcion < salir) {
      funciones[opcion-1](cliente);
    }
  } while(opcion != salir);
}


void menuCuenta(
  char* titulo,
  int numOpciones,
  const char* opciones[],
  funcionCuenta funciones[],
  Cuenta* cuenta
) {
  int opcion, salir = numOpciones+1;

  do
  {
    limpiarPantalla();
    opcion = 0;

    printf("\t\t---%s---\n\n\v", titulo);

    for (int i = 0; i < numOpciones; i++) {
      printf("%d. %s\n", i+1, opciones[i]);
    }
    printf("%d. Salir.\n", salir);

    printf("\nIntroduzca una opción: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    if (opcion > 0 && opcion < salir) {
      funciones[opcion-1](cuenta);
    }
  } while(opcion != salir);
}



void menu (
  char* titulo,
  int numOpciones,
  const char* opciones[],
  funcionVoid funciones[]
) {
  int opcion, salir = numOpciones+1;

  do
  {
    limpiarPantalla();
    opcion = 0;

    printf("\t\t---%s---\n\n\v", titulo);

    for (int i = 0; i < numOpciones; i++) {
      printf("%d. %s\n", i+1, opciones[i]);
    }
    printf("%d. Salir.\n", salir);

    printf("\nIntroduzca una opción: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    if (opcion > 0 && opcion < salir) {
      funciones[opcion-1]();
    }
  } while(opcion != salir);
}
