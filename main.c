#include <stdio.h>
#include <stdlib.h>
#include "analizador_sintactico.h"
#include "tabla_simbolos.h"
#include "sistema_entrada.h"

//declaracion de funciones
void procesar_entrada(int argc, char** argv);
FILE *abrir_archivo(char* filename);

//hilo de ejecución principal
int main(int argc, char** argv) {

    //procesar entrada
    procesar_entrada(argc, argv);

    //inicializar sistema de entrada
    inicializar_sistema_entrada(argv[1]);
    
    //iniciar tabla de simbolos
    inicializar_tabla();

    //iniciar analizador sintactico
    start();

    //liberar memoria
    liberar_tabla();

    //liberar sistema entrada
    finalizar_sistema_entrada();

    exit(EXIT_SUCCESS);
}


//implementacion de las funciones

void procesar_entrada(int argc, char** argv){

    //check args
    if(argc != 2){
        perror("Failed ARGS");
        exit(EXIT_FAILURE);
    }

}