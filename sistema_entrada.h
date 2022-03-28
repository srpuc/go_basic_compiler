#ifndef SISTEMA_ENTRADA_H
#define SISTEMA_ENTRADA_H

// TAMAÑO DE BLOQUE DEL SISTEMA DE ENTRADA
// ---------------------------------------

#define BLOCK_SIZE 64


// PROTOTIPOS DE FUNCIONES
// -----------------------

void inicializar_sistema_entrada(char* filename);

char siguiente_char();

void mover_inicio();

void devolver();

char* get_lexema();

void cargar_bloque(int num_bloque);

void finalizar_sistema_entrada();

#endif