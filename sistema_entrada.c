#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema_entrada.h"
#include "error.h"

// DESCRIPCION
// -----------

/*      Esta es la parte del programa correspondiente al sistema de entrada, 
 *      en la que se encuentra el sistema del doble centinela para la lectura
 *      de un archivo asumiendo recursos de memoria limitados.
 *
 *      Para la mayor comprension de este codigo es importante aclarar un
 *      detalles acerca de la implementación, en este caso el uso de un
 *      array continuo que simula el uso de 2 buffers.
 */


// DECLARACION DE VARIABLES GLOBALES
// ---------------------------------

char* buff;
char* inicio;
char* delante;

int n;
int count;

FILE* f;


// FUNCION: INICIALIZACION
//--------------------------

/*      Esta es la primera función es se llamada desde el main, en ella se abre
*       el archivo que se va a procesar, se reserva memoria para los buffers 
*       y se llena el primer buffer con los primeros caracteres del archivo.
*/
void inicializar_sistema_entrada(char* filename)
{

    //almacenamos puntero a archivo
    f = fopen(filename,"r");

    //comprobar apartura del archivo
    if(f == NULL){
        perror("Failed: ");
        exit(EXIT_FAILURE);
    }

    //reservamos memoria para el buffer
    buff = (char*)malloc(2 * BLOCK_SIZE);
    buff[ BLOCK_SIZE - 1 ] = EOF;
    buff[ (2 * BLOCK_SIZE) - 1 ] = EOF;

    //variable en la que se almacena el numero de caracteres cargados en el buffer
    n = 1;

    //cargamos el primer bloque en el buffer
    cargar_bloque(0);

    //colocacion inicial de los punteros
    inicio = buff;
    delante = buff;

    //variable que lleva cuenta del numero de caracteres leidos
    count = 0;
    
}


// FUNCION: PRINCIPAL
// -----------------

/*      Esta función devuelve el siguiente caracter al analizador lexico y
 *      gestiona el doble buffer con entinela de manera que se proporciona una abtracción
 *      completa entre las dos partes.
 */
char siguiente_char()
{

    //variable que se devolverá
    char c;

    //comporbacion tamaño maximo lexema
    count++;
    if ( count > BLOCK_SIZE - 1 )
    {
        error(1, "Tamaño del lexema excede el tamaño de bloque.");
        return -1;
    }
    
    /*  El sistema de entrada se encuentra con un caractar EOF
     *  es necesario comprobar si se trata del fin del buffer o 
     *  del fin de fichero realmente.
     */
    if ( *delante == EOF )
    {
        //final del bloque 1
        if (delante == buff + BLOCK_SIZE - 1)
        {
            cargar_bloque(1);
            delante ++;
            c = *delante;
            delante ++;
            return c;
        }
        //final del bloque 2
        else if (  delante == buff + (2*BLOCK_SIZE) - 1 )
        {
            cargar_bloque(0);
            delante = buff;
            c = *delante;
            delante ++;
            return c;
        }
        //final de archivo
        else
        {
            return *delante;
        }

    }
    //otro caracter
    else
    {
        c = *delante;
        delante ++;
        return c;
    }
    
}


// FUNCION: MOVER INICIO
// ---------------------

/*      Utilizando el centinela no es necesario almacenar por duplicado
 *      los caracteres leidos de cada lexema, puesto que estos ya estan
 *      en el buffer. 
 * 
 *      Para poder posteriormente obtener directamente del buffer el lexema 
 *      es necesario indicar dentro del buffer donde comienza el lexema.
 */
void mover_inicio()
{
    inicio = delante;
    count = 0;
}


// FUNCION: DEVOLVER
// -----------------

/*      Hay ciertos automatas que su estado de parada finaliza en con el siguiente
 *      caracter al lexema. Puesto que el caracter ha sido reconocido, es necesario 
 *      devolverlo para que cuando se vuelve a ejecutar el automata este sea reconocido.
 */
void devolver()
{

    //se comprueba que el puntero no esté en el fin de fichero
    if ( *delante != EOF )
    {

        //se comprueba que el puntero no esté en el inicio
        if (delante != buff)
        {

            //compobramos si el puntero debe retrocedr uno o dos lugares puesto que retrocede a traves del EOF entre buffers
            if(*(delante-1) != EOF) 
            {
                delante--;
            }
            else
            {
                delante -= 2;
            }
            
        }
        //movemos el puntero desde el inicio al final del buffer
        else
        {
            delante = (buff + 2 * BLOCK_SIZE) - 1;
        }

    }
    
}


// FUNCION: CONSEGUIR LEXEMA
// -------------------------

/*      Se obtiene la string que conforma el lexema del componente lexico a partir del
 *      contenido de los buffers. Para ello se coje la información necesaria de cada uno de
 *      los buffer y se une para crear el lexema.
 */
char* get_lexema()
{

    //declararion y inicializacion de variables
    char* lexema = NULL;

    int n0 = 0;
    int n1 = 0;

    //comprobacion de orden
    //el final esta más adelante que el inicio
    if ( delante - inicio < 0 )
    {

        //calculo de cuantos caracteres copiar de cada buffer
        n0 = (buff + 2*BLOCK_SIZE - 1) - inicio;
        n1 = delante - buff;

        //reserva de memoria y copiado de informacion a la misma            //  Es necesario comentar que se reserva un caracter 
        lexema = (char *)malloc( n0 + n1 + 1);                              //  extra puesto que posteriormente se utilizará strcmp en
        strncpy(lexema, inicio, n0);                                        //  la tabla de simbolos y se requiere del caracter de
        strncpy(lexema + n0, buff, n1);                                     //  final de string.
        lexema[n0 + n1 ] = '\0';                        

    }
    //el inicio esta más adelante que el final
    else
    {
        if ( inicio < (buff + BLOCK_SIZE) && delante >= (buff + BLOCK_SIZE) )
        {
            n0 = (buff + BLOCK_SIZE - 1) - inicio;
            n1 = delante - (buff + BLOCK_SIZE);

            lexema = (char *)malloc( n0 + n1 + 1);

            strncpy(lexema, inicio, n0);
            strncpy(lexema + n0, buff + BLOCK_SIZE, n1);
            lexema[n0 + n1 ] = '\0';

        }
        else
        {
            n0 = delante - inicio;
            lexema = (char *)malloc(n0 + 1);
            strncpy(lexema, inicio, n0);
            lexema[n0] = '\0';
        }
        
    }

    return lexema;
    
}


// FUNCION: CARGAR BLOQUE
// ----------------------

/*      Simple función que modulariza el codigo. Se encarga de cargar en el buffer la 
 *      siguiente secuencia de caracteres del archivo.
 *      
 *      0 - primer bloque
 *      1 - segundo bloque
 */
void cargar_bloque(int num_bloque)
{
    n = fread(buff + num_bloque * BLOCK_SIZE , 1, BLOCK_SIZE - 1, f);
    if (n != BLOCK_SIZE - 1)
    {
        buff[(num_bloque * BLOCK_SIZE) + n] = EOF;
    }
    
}


// FUNCION: FINALIZAR
// ------------------

/*      Se cierra el archivo de entrada y se libera el puntero que
 *      apunta a la dirección del buffer.
 */
void finalizar_sistema_entrada(){

    fclose(f);
    free(buff);

}