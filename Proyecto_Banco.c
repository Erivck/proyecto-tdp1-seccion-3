#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#define configurarConsola() SetConsoleCP(1252); SetConsoleOutputCP(1252)
#else
#define configurarConsola()
#endif // _WIN32

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

#define CLIENTE_NUM_CAMPOS 13

#define CLIENTE_NUM_CAMPOS 13

#define NUM_TIPOS_DE_CUENTA 3

#define CUENTA_NUM_CAMPOS 4

#define CLAVE_SISTEMA "admin1234"

#define NUM_OPCIONES_BANCO 5
#define NUM_OPCIONES_DATOS 3
#define NUM_OPCIONES_CUENTAS 3
#define NUM_OPCIONES_OPERACIONES 2
#define NUM_OPCIONES_CUENTA 2


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


//Tipos de formato de texto.
typedef enum {
  numerico,
  alfabetico,
  alfanumerico,
  texto,
  formatoDeUsuario,
  fecha,
} Tipo_de_Formato;

//Enumeraciï¿½n de los tipos de datos del proyecto.
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

// Enumeraciï¿½n de Errores posibles de validaciï¿½n.
enum Errores_de_Validacion {
  ERROR_MAXIMO_DE_CARACTERES = 1,
  ERROR_MINIMO_DE_CARACTERES,
  ERROR_FORMATO_INVALIDO,
  ERROR_FECHA_INVALIDA,
  ERROR_CLIENTE_MENOR_EDAD
};

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


typedef void (*funcionCliente)(Cliente* cliente);

typedef void (*funcionCuenta)(Cuenta* cuenta);

typedef void (*funcionVoid)(void);


void limpiarPantalla (void);
void limpiarBuffer (void);
void esperarEntrada(void);
const char* obtenerFormatoDeDato(Tipo_de_Dato tipo);
int validarDato(Tipo_de_Dato tipo, char* buffer);
void leerDato(Tipo_de_Dato tipo, char* puntero);
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
bool buscarCliente(Datos_de_Cliente tipo, char* dato, Cliente* cliente);
bool registrarCliente(Cliente* cliente);
char* obtenerDatoDeCliente(Datos_de_Cliente dato, Cliente* cliente);
void inicializarCliente(Cliente* cliente);
bool actualizarDatosDeCliente(char* usuario, Cliente* cliente);
bool eliminarCliente(char* usuario);
void bancoIngresarCliente(void);
void bancoRegistrarCliente(void);
void bancoIngresarSistema(void);
void bancoMenuSistema(void);
void bancoMenuCliente(Cliente* cliente);
void datosCliente(Cliente* cliente);
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
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñÑ ‘ ",
    "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñÑ .,;:-",
    "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñÑ_",
    "1234567890/"
};

const time_t edadMinima = 365 * 24 * 60 * 60 * 18;

int datoMaxChars[] = {
  USUARIO_MAX, // Usuario
  CLAVE_MAX, // Clave
  NOMBRES_MAX, // Nombre
  APELLIDOS_MAX, // Apellido
  CEDULA_MAX, // Cï¿½dula
  SEXO_MAX, // Sexo
  FECHA_DE_NACIMIENTO_MAX, // Fecha de Nacimiento
  TELEFONO_MAX, // Telï¿½fono
  ESTADO_MAX, // Estado
  CIUDAD_MAX, // Ciudad
  MUNICIPIO_MAX, // Municipio
  DIRECCION_MAX, // Direccion
  CODIGO_POSTAL_MAX, // Cï¿½digo Postal
  NUMERO_DE_CUENTA_MAX // Numero de Cuenta
};

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
  "Pago Móvil.",
};

const char* opcionesOperaciones[] = {
  "Transferencia.",
  "Pago Móvil.",
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


const char* cuentaOpciones[] = {
  "Ver Datos de Cuenta.",
  "Ver Estado de Cuenta.",
};

funcionCuenta funcionesCuenta[] = {
  datosDeCuenta,
  estadoDeCuenta
};







#define num_opciones 4

enum Opciones_Enum {
  INGRESAR_SISTEMA = 1,
  INGRESAR_COMO_CLIENTE,
  REGISTRAR_CLIENTE
};

const char *opciones [] = {
  "Ingresar Sistema.",
  "Ingresar como Cliente.",
  "Registrar Cliente.",
  "Salir."
};




int main()
{
  configurarConsola();

  int opcion;

  do {
    limpiarPantalla();
    opcion = 0;
    printf("\t\t---SERVICIO BANCARIO---\n\n\v");
    for (int i = 0; i < num_opciones; i++) {
      printf("%d. %s\n", i+1, opciones[i]);
    }
    printf("\nIngrese una opción: ");

    scanf("%d", &opcion);
    limpiarBuffer();

    switch (opcion) {
      case INGRESAR_SISTEMA:
        bancoIngresarSistema();
        break;
      case INGRESAR_COMO_CLIENTE:
        bancoIngresarCliente();
        break;
      case REGISTRAR_CLIENTE:
        bancoRegistrarCliente();
        break;
    }
  } while (opcion != num_opciones);

  return 0;
}







void limpiarPantalla () {
  system("clear||cls");
}

void limpiarBuffer () {
  while ((getchar()) != '\n');
}

void esperarEntrada() {
  printf("Presione \"Enter\" para continuar...");
  limpiarBuffer();
}






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









bool registrarCuentaDeCliente (Tipo_de_Cuenta tipo, Cliente* cliente) {
  bool registrado = false;
  Cuenta cuentaNueva;

  if (!inicializarCuenta(tipo, &cuentaNueva, cliente)) return false;

  FILE* cuentas = fopen("cuentas.dat", "ab");

  if (cuentas == NULL) return false;

  if (fwrite(&cuentaNueva, sizeof(Cuenta), 1, cuentas)) registrado = true;

  fclose(cuentas);

  return registrado;
}


bool buscarCuentaPorTipo(Tipo_de_Cuenta tipo, char* cedulaDelCliente, Cuenta* cuenta) {
  bool encontrado = false;
  Cuenta* cuentaptr = cuenta ? cuenta : malloc(sizeof(Cuenta));

  FILE* cuentas = fopen("cuentas.dat", "rb");

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

  FILE* cuentas = fopen("cuentas.dat", "rb");

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

  FILE* cuentas = fopen("cuentas.dat", "rb");
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
  FILE* cuentas = fopen("cuentas.dat", "rb");
  Cuenta temp;

  if (cuentas == NULL) return 0;

  int total = 0;

  while(fread(&temp, sizeof(Cuenta), 1, cuentas)) total++;

  fclose(cuentas);

  return total;
}


bool inicializarCuenta(Tipo_de_Cuenta tipo, Cuenta* cuenta, Cliente* cliente) {
  char numeroDeCuenta[12];
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

  FILE* cuentas = fopen("cuentas.dat", "rb");
  FILE* cuentasNuevo = fopen("cuentas_temp.dat", "ab");

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

  remove("cuentas.dat");
  rename("cuentas_temp.dat", "cuentas.dat");

  return true;
}

bool eliminarCuenta(char* numeroDeCuenta) {
  Cuenta temp;

  FILE* cuentas = fopen("cuentas.dat", "rb");
  FILE* cuentasNuevo = fopen("cuentas_temp.dat", "ab");

  if (cuentas == NULL || cuentasNuevo == NULL) return false;

  while (fread(&temp, sizeof(Cuenta), 1, cuentas)) {
    if (strcmp(temp.numeroDeCuenta, numeroDeCuenta) != 0)
      fwrite(&temp, sizeof(Cuenta), 1, cuentasNuevo);
  }

  fclose(cuentas);
  fclose(cuentasNuevo);

  remove("clientes.dat");
  rename("clientes_temp.dat", "clientes.dat");

  return true;
}


bool registrarMovimientoDeCuenta(Movimiento_de_Cuenta* movimiento) {
  bool registrado = false;

  FILE* movimientos = fopen("movimientos.dat", "ab");

  if (movimientos == NULL) return false;

  if (fwrite(movimiento, sizeof(Movimiento_de_Cuenta), 1, movimientos)) registrado = true;

  fclose(movimientos);

  return registrado;
}












bool registrarCliente(Cliente* cliente) {
  bool registrado = false;

  FILE* clientes = fopen("clientes.dat", "ab");

  if (clientes == NULL) return false;

  if (fwrite(cliente, sizeof(Cliente), 1, clientes)) registrado = true;

  fclose(clientes);

  return registrado;
}


bool buscarCliente(Datos_de_Cliente tipo, char* dato, Cliente* cliente) {
  bool encontrado = false;
  Cliente* clienteptr = cliente ? cliente : malloc(sizeof(Cliente));

  FILE* clientes = fopen("clientes.dat", "rb");

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

  FILE* clientes = fopen("clientes.dat", "rb");
  FILE* clientesNuevo = fopen("clientes_temp.dat", "ab");

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

  remove("clientes.dat");
  rename("clientes_temp.dat", "clientes.dat");

  return true;
}

bool eliminarCliente(char* usuario) {
  Cliente temp;

  FILE* clientes = fopen("clientes.dat", "rb");
  FILE* clientesNuevo = fopen("clientes_temp.dat", "ab");

  if (clientes == NULL || clientesNuevo == NULL) return false;

  while (fread(&temp, sizeof(Cliente), 1, clientes)) {
    if (strcmp(temp.usuario, usuario) != 0)
      fwrite(&temp, sizeof(Cliente), 1, clientesNuevo);
  }

  fclose(clientes);
  fclose(clientesNuevo);

  remove("clientes.dat");
  rename("clientes_temp.dat", "clientes.dat");

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
    "Realizar Depósito.",
    "Realizar Retiro."
  };

  funcionVoid funciones[] = {
    realizarDeposito,
    realizarRetiro
  };

  menu("SISTEMA DE SERVICIO BANCARIO", numOpciones, opciones, funciones);
}


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
  int numDatosAModificar = 8;
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
  } while(opcion != numDatosAModificar);
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
