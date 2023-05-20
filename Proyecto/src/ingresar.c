#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../cliente.h"
#include "../ingresar.h"
#include "../utils.h"
#include "../datos.h"
#include "../banco.h"

void ingresar() {
  char usuario[16];
  char clave[21];
  Cliente cliente;

  printf("\t\tINGRESAR:\n\n\v");

  leerDato(Usuario, usuario);

  if (!buscarCliente(usuario, &cliente)) {
    printf("\nEl usuario \"%s\" no existe.\n\n", cliente.usuario);
    esperarEntrada();
    return;
  }

  leerDato(Clave, clave);

  printf("%s\n", cliente.clave);

  if (strcmp(clave, cliente.clave) != 0) {
    printf("\nClave incorrecta.\n\n");
    esperarEntrada();
    return;
  }

  bancoMenu(&cliente);
}

void registrarse() {
  bool usuarioInvalido;
  bool error;
  Cliente cliente;

  printf("\t\tREGISTRARSE:\n\n\v");

  usuarioInvalido = leerDato(Usuario, cliente.usuario);

  if (usuarioInvalido) return;

  if (existeCliente(cliente.usuario)) {
    printf("\nEl usuario \"%s\" ya existe.\n\n", cliente.usuario);
    esperarEntrada();
    return;
  }

  error = leerDato(Nombre, cliente.nombre) ||
          leerDato(Apellido, cliente.apellido) ||
          leerDato(Clave, cliente.clave);

  if (error) return;

  crearCliente(&cliente);

  printf("\nCliente registrado exitosamente.\n\n");

  esperarEntrada();
}
