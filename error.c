#include <stdlib.h>
#include <stdio.h>
#include "error.h"

// FUNCION: ERROR
// --------------

/*      Se muestra por pantalla un mensaje de error, este mensaje
 *      es custommizable, y lleva una ID con la parte del programa
 *      desde la que se produce.
 */

void error(int ID, char* msg){
    
    switch (ID)
    {

    //error sistema de entrada
    case 1:
        printf( ANSI_COLOR_RED "ERROR: SISTEMA DE ENTRADA \n[%s]\n" ANSI_COLOR_RESET, msg);
        break;
    
    //error analizador lexico
    case 2:
        printf( ANSI_COLOR_RED "ERROR: ANALIZADOR LEXICO \n[%s]\n" ANSI_COLOR_RESET, msg);
        break;

    //error analizador sintactico
    case 3:
        printf( ANSI_COLOR_RED "ERROR: ANALIZADOR SINTACTICO \n[%s]\n" ANSI_COLOR_RESET, msg);
        break;

    default:
        break;
    }

}