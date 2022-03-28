#ifndef ERROR_H
#define ERROR_H

//colores
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//errores sistemas
#define ERROR_SISTEMA_ENTRADA 1
#define ERROR_ANALIZADOR_LEXICO 2
#define ERROR_ANALIZADOR_SINTACTICO 3

//sistema de entrada
#define ERROR_TAMANO_LEXEMA

//declaracion de funciones
void error(int id, char* msg);

#endif