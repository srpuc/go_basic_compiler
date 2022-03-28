#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

//CONSTANTES
//----------

#define TRUE 1
#define FALSE 0
#define FINAL -2
#define COMENTARIO 2

// DEFINICION DE LA ESTRUCTURA
// ---------------------------

/*      Estructura que conforma un componente lexico,
 *      en ella se encuentran dos campos, la id del componente
 *      y el propio lexema del componente.
 */
typedef struct componente{
    int id;
    char *lexema;
}componente;


// PROTOTIPOS DE FUNCIONES
// -----------------------

componente siguiente();

#endif