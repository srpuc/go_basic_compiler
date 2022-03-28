#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include "tabla_simbolos.h"
#include "abb.h"

//ESTRUCTURA
//----------

/*      La estructura que se implementa dentro de la tabla de simbolos
 *      es un arbol binario de busqueda generio, obtenido de la asignatura
 *      AED. Por ello consediro importante destacar que los ficheros "abb.c"
 *      y "abb.h" no estarán comentados de la misma manera que el resto del
 *      codigo de este programa.
 * 
 *      Esta estructura de datos, permite una busqueda rápida y de facil
 *      implementación. Cada nodo del arbol es un componenete lexico en el se
 *      almacena su ID asi como el lexema.
 */

abb arbol;


// FUNCIONES: IMPRIMIR
// -------------------

/*      Las dos siguientes funciones permiten mostrar por terminal los contenidos
 *      de la tabla de simbolos, pensada esta funcion para mostrar de manera modulzarizada
 *      el estado de la tabla antes y despues de la ejecución del analis sintactico.
 */
void _imprimir(abb A)
{
    tipoelem elem;
    if ( !es_vacio(A) )
    {

        leer(A, &elem);
        printf("║ " ANSI_COLOR_MAGENTA "%d" ANSI_COLOR_RESET " | " ANSI_COLOR_CYAN "%-35s" ANSI_COLOR_RESET " ║\n", elem.id, elem.lexema );
        printf("╠═══════════════════════════════════════════╣\n");
        
        _imprimir( der(A) );
        _imprimir( izq(A) );
    }
    
}
void imprimir_tabla()
{
    printf("╔═══════════════════════════════════════════╗\n");
    printf("║ TABLA DE SIMBOLOS                         ║\n");
    printf("╠═══════════════════════════════════════════╣\n");
    _imprimir(arbol);
    printf("║ FIN DE TABLA DE SIMBOLOS                  ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
}


// FUNCION: INICIALIZAR
// --------------------

/*      En esta funcion se crean y inicializan las variables necesarias para el funcionammiento
 *      de la tabla. Asi como la inserción en la misma de las "keywords" definidas en la
 *      especificacion del lenguaje.
 */
void inicializar_tabla()
{

    //inicializar estructura de datos
    crear(&arbol);

    //variable que contiene las keywords
    tipoelem comp[25];

    //inicializacion de las keywords
    comp[0].lexema = "break" ; comp[0].id = BREAK;
    comp[1].lexema = "case" ; comp[1].id = CASE;
    comp[2].lexema = "chan" ; comp[2].id = CHAN;
    comp[3].lexema = "const" ; comp[3].id = CONST;
    comp[4].lexema = "continue" ; comp[4].id = CONTINUE;

    comp[5].lexema = "default" ; comp[5].id = DEFAULT;
    comp[6].lexema = "defer" ; comp[6].id = DEFER;
    comp[7].lexema = "else" ; comp[7].id = ELSE;
    comp[8].lexema = "fallthrough" ; comp[8].id = FALLTHROUGH;
    comp[9].lexema = "for" ; comp[9].id = FOR;

    comp[10].lexema = "func" ; comp[10].id = FUNC;
    comp[11].lexema = "go" ; comp[11].id = GO;
    comp[12].lexema = "goto" ; comp[12].id = GOTO;
    comp[13].lexema = "if" ; comp[13].id = IF;
    comp[14].lexema = "import" ; comp[14].id = IMPORT;

    comp[15].lexema = "interface" ; comp[15].id = INTERFACE;
    comp[16].lexema = "map" ; comp[16].id = MAP;
    comp[17].lexema = "package" ; comp[17].id = PACKAGE;
    comp[18].lexema = "range" ; comp[18].id = RANGE;
    comp[19].lexema = "return" ; comp[19].id = RETURN;

    comp[20].lexema = "select" ; comp[20].id = SELECT;
    comp[21].lexema = "struct" ; comp[21].id = STRUCT;
    comp[22].lexema = "switch" ; comp[22].id = SWITCH;
    comp[23].lexema = "type" ; comp[23].id = TYPE;
    comp[24].lexema = "var" ; comp[24].id = VAR;

    //insercion de las keywords
    for (size_t i = 0; i < 25; i++)
    {
        insertar(&arbol, comp[i]);
    }

    //impresion de la tabla por terminal
    imprimir_tabla();

}


// FUNCION: LIBERAR TABLA
// ----------------------

/*      Se imprime la tabal una vez finalizada la ejecución de los otros componentes del sistema
 *      para mostrar su estado y se libera y destruye la estructura de datos y sus componentes.
 */
void liberar_tabla()
{
    imprimir_tabla();
    destruir(&arbol);
}


// FUNCION: INSERTAR
// -----------------

/*  Se inserta en la tabla un nuevo elemento, esta funcion necesita como parametros
 *  el identificador del componente lexico y el lexema que lo forma.
 */
void insertar_tabla( int id, char* lexema )
{

    // declaracion
    tipoelem componente;
    componente.id = id;
    componente.lexema = lexema;

    //insercion
    insertar(&arbol, componente);

}



// FUNCION: BUSCAR
// ---------------

/*      Se busca dentro de la estrucutra de datos de la tabla la existencia de un componente
 *      lexico, esta funcion es critica ya que si hay una lexema ya en la tabla, se evita volver
 *      a introducir el mismo de manera repetida.
 */
int buscar_tabla( int id, char* lexema ){

    //declaracion
    tipoelem elem;
    elem.id = id;
    elem.lexema = lexema;

    //busqueda
    return es_miembro(arbol, elem);
}
