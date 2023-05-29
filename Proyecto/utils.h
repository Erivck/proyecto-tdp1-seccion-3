#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED


#ifdef _WIN32
#include <windows.h>
#define configurarConsola() SetConsoleCP(1252); SetConsoleOutputCP(1252)
#else
#define configurarConsola()
#endif // _WIN32


// Limpia la pantalla.
void limpiarPantalla (void);

// Limpia el buffer de entrada, solo usar despues de scanf o getchar.
void limpiarBuffer (void);

// Espera a que el usuario presione la tecla "Enter".
void esperarEntrada(void);


#endif // UTILS_H_INCLUDED
