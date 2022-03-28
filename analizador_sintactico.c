#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"
#include "analizador_sintactico.h"
#include "analizador_lexico.h"


//FUNCION: INICIAR
//----------------

/*      Esta funcion se encarga de dar comienzo al "analizador sintactico" que
 *      en esta practica unicamente mostrará por pantalla los componentes lexicos
 *      que recibe del analizador lexico hasta el fin de fichero.
 */

void start() {

    printf( "┌─────────────────────────────────────────┐\n" );
    printf( "│ Analizador Sintactico Iniciado          │\n" );
    printf( "├─────────────────────────────────────────┤\n" );


    //se pide el siguiente componente lexico y se imprime hasta el final de fichero
    do{

        componente  c = siguiente();
        printf("│ ID: "ANSI_COLOR_MAGENTA"%3d"ANSI_COLOR_RESET" │ Lex:"ANSI_COLOR_CYAN" %-24s "ANSI_COLOR_RESET"│ \n", c.id, c.lexema );
        printf( "├─────────────────────────────────────────┤\n" );

        //id de los componenetes almacenados en la tabla
        //se liberaran junto con la tabla
        if (c.id != 300)
            free(c.lexema);

        //id de EOF
        //se rompe el bucle y se sale del analizador sintactico
        if (c.id == -1)
            break;
        
    }while( 1 );
    
    printf( "│ Analizador Sintactico Terminado         │\n" );
    printf( "└─────────────────────────────────────────┘\n" );


}