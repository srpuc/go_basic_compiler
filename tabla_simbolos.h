#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

//PROTOTIPOS DE FUNCIONES
//-----------------------

void inicializar_tabla();

void liberar_tabla();

void insertar_tabla(int id, char* lexema);

int buscar_tabla( int id, char* lexema);

#endif