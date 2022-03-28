#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tabla_simbolos.h"
#include "analizador_lexico.h"
#include "sistema_entrada.h"
#include "definiciones.h"
#include "error.h"

//FUNCIONES PRIVADAS
//------------------

/*      Estas son pequeñas funciones que permiten una gran
 *      simplificación del codigo facilitando asi su lectura
 *      y entendimiento a los programadores.
 */

int isLetter(char c)
{
    return ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' );
}

int isDigit(char c)
{
    return ( c >= '0' && c <='9' );
}

int isPunctuation(char c)
{
    //incompleto
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ';' ;
}


//FUNCIONES AUTOMATAS
//-------------------

/*      Estas son las diferentes funciones que realizan la funcionalidad
 *      de los diferentes automatas necesarios para reconocer los componentes
 *      del lenguaje.
 * 
 *      Reciben por referencia 2 argumentos, el estado del que provienen
 *      y la estructura del componente lexico con el que trabajan. 
 * 
 *      Estableceran los campos de esta estructura segun su procesamiento
 *      interno hasta un estado de aceptación o bien se mostrará un error.
 *      Y se devolverá el componente con sus campos por defecto.
 */

void _automata_cadena_alfanumerica( int* estado , componente* comp){

    char c = siguiente_char();

    while ( *estado != FINAL )
    {
        if ( isLetter(c) || c == '_' || isDigit(c) )
        {
            c = siguiente_char();
        }
        else
        {
            comp->id = ID;
            devolver();
            comp->lexema = get_lexema();

            if( !buscar_tabla(comp->id, comp->lexema) ){
                insertar_tabla( comp->id, comp->lexema );
            }

            *estado = FINAL;
        }
    }
    
}

void _automata_numeros( int* estado, componente* comp )
{

    devolver();
    char c = siguiente_char();

    int estado_local = 0;
    
    while ( *estado != FINAL )
    {
        
        switch ( estado_local )
        {

        //estado base (siempre hay un digito)
        case 0:
            
            if ( c == '0' )
            {
                estado_local = 1;
                c = siguiente_char();
            }
            else if ( c == '.' )
            {
                estado_local = 4;
                c = siguiente_char();
            }
            else
            {
                estado_local = 2;
                c = siguiente_char();
            }
            
            break;

        //primer digito 0 (puede ser hex)
        case 1:

            if ( c == 'x' || c == 'X' )
            {
                estado_local = 11;
                c = siguiente_char();
            }
            else if ( c == '.' )
            {
                estado_local = 4;
                c = siguiente_char();
            }
            else if ( c == 'i' )
            {
                comp->id = IMAGINARIO;
                comp->lexema = get_lexema();
                *estado = FINAL;
            }
            else
            {
                comp->id = ENTERO;
                devolver();
                comp->lexema = get_lexema();
                *estado = FINAL;
            }
    
            break;

        //entro un digito diferente de 0 
        case 2:
            if ( isDigit(c) )
            {
                c = siguiente_char();
            }
            else if ( c == 'e' || c == 'E' )
            {
                estado_local = 6;
                c = siguiente_char();
            }
            else if ( c == '_' )
            {
                c = siguiente_char();
                if ( isDigit(c) )
                {
                    c = siguiente_char();
                }
                else
                {
                    error(2, "Numero no reconocido. Los caracteres \'_\' tienen que separar digitos consecutivos.");
                }
                
            }
            else if ( c == '.' )
            {
                estado_local = 4;
                c = siguiente_char();
            }
            else if ( c == 'i' )
            {
                comp->id = IMAGINARIO;
                comp->lexema = get_lexema();
                *estado = FINAL;
            }
            else
            {
                comp->id = ENTERO;
                devolver();
                comp->lexema = get_lexema();
                *estado = FINAL;
            }
            
            break;

        //entra un punto
        case 4:

            if ( isDigit(c) )
            {
                estado_local = 5;
                c = siguiente_char();
            }
            else if ( c == 'e' || c == 'E' )
            {
                estado_local = 6;
                c = siguiente_char();   
            }
            else if ( c == 'i' )
            {
                comp->id = IMAGINARIO;
                comp->lexema = get_lexema();
                *estado = FINAL;
            }
            else
            {
                comp->id = FLOAT;
                devolver();
                comp->lexema = get_lexema();
                *estado = FINAL;   
            }

            break;

        //numeros antes del exponente
        case 5:

            if ( isDigit(c) )
            {
                c = siguiente_char();
            }
            else if ( c == '_' )
            {

                //simulamos estado 7
                c = siguiente_char();
                if ( isDigit(c) )
                {
                    c = siguiente_char();
                }
                else
                {
                    error(2, "Numero no reconocido. Los caracteres \'_\' tienen que separar digitos consecutivos.");
                }
                
            }
            else if ( c == 'e' || c == 'E' )
            {
                estado_local = 6;
                c = siguiente_char();
            }
            else if ( c == 'i' )
            {
                comp->id = IMAGINARIO;
                comp->lexema = get_lexema();
                *estado = FINAL;
            }
            else
            {
                comp->id = FLOAT;
                devolver();
                comp->lexema = get_lexema();
                *estado = FINAL;
            }

            break;

        //ha entrado la e del exponente
        case 6:

            if ( isDigit(c) )
            {
                estado_local = 9;
                c = siguiente_char();
            }
            else if ( c == '+' || c == '-' )
            {
                estado_local = 8;
                c = siguiente_char();
            }
            else
            {
                error(2, "Numero no reconocido. Caracter invalido.");
            }

            break;

        //exponente con operador
        case 8:

            if ( isDigit(c) )
            {
                estado_local = 9;
                c = siguiente_char();
            }
            else
            {
                error(2, "Numero no reconocido. Caracter invalido.");
            }

            break;

        //numeros del exponenete
        case 9:

            if ( isDigit(c) )
            {
                c = siguiente_char();
            }
            else if ( c == '_' )
            {
                c = siguiente_char();
                //simulamos estado 10
                if ( isDigit(c) )
                {
                    c = siguiente_char();
                }
                else
                {
                    error(2, "Numero no reconocido. Caracter invalido.");
                }
                
            }
            else if ( c == 'i' )
            {
                comp->id = IMAGINARIO;
                comp->lexema = get_lexema();
                *estado = FINAL;
            }
            else
            {
                comp->id = FLOAT;
                devolver();
                comp->lexema = get_lexema();
                *estado = FINAL;
            }
            
            break;

        //ha entrado una x
        case 11:

            if ( isxdigit(c) || c == '_')
            {
                estado_local = 12;
                c = siguiente_char();
            }
            else
            {
                error(2, "Numero no reconocido. Caracter invalido.");
            }
            
            break;

        //hex int
        case 12:

            if ( isxdigit(c) )
            {
                c = siguiente_char();
            }
            else if ( c == '_' )
            {
                c = siguiente_char();
                //simulamos estado 13
                if ( isDigit(c) )
                {
                    c = siguiente_char();
                }
                else
                {
                    error(2, "Numero no reconocido. Caracter invalido.");
                }
                
            }
            else if ( c == 'i' )
            {
                comp->id = IMAGINARIO;
                comp->lexema = get_lexema();
                *estado = FINAL;
            }
            
            else
            {
                comp->id = ENTERO;
                devolver();
                comp->lexema = get_lexema();
                *estado = FINAL;
            }

            break;

        default:
            break;
        }

    }
    
}

void _automata_mas( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = MAS_IGUAL;
    }
    else if ( c == '+' )
    {
        comp->id = MAS_MAS;
    }
    else
    {
        comp->id = MAS;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_menos( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = MENOS_IGUAL;
    }
    else if ( c == '-' )
    {
        comp->id = MENOS_MENOS;
    }
    else
    {
        comp->id = MENOS;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_asterisco( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = POR_IGUAL;
    }
    else
    {
        comp->id = POR;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_barra_inclinada( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = DIV_IGUAL;
    }
    else if ( c == '/' )
    {
        c = siguiente_char();
        while ( c != '\n' )
        {
            c = siguiente_char();
            mover_inicio();
        }
        *estado = COMENTARIO;
        return;
    }
    else if ( c == '*' )
    {
        c = siguiente_char();
        int bool = 0;
        while ( bool == 0 )
        {
            c = siguiente_char();
            mover_inicio();
            if ( c == '*' )
            {
                c = siguiente_char();
                if ( c == '/' )
                {
                    bool = 1;
                    *estado = COMENTARIO;
                    return;
                }
            }
        }
        mover_inicio();
    }
    else
    {
        comp->id = DIV;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_porcentaje( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = MOD_IGUAL;
    }
    else
    {
        comp->id = MOD;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_ampersand( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = AMPERSAND_IGUAL;
    }
    else if ( c == '&' )
    {
        comp->id = AMPERSAND_AMPERSAND;
    }
    else if ( c == '^' )
    {
        c = siguiente_char();
        if ( c == '=' )
        {
            comp->id = AMPERSAND_UP_IGUAL;
        }
        else
        {
            comp->id = AMPERSAND_UP;
            devolver();
        }   
    }
    else
    {
        comp->id = AMPERSAND;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_barra_vertical( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = VERTICAL_IGUAL;
    }
    else if ( c == '+' )
    {
        comp->id = VERTICAL_VERTICAL;
    }
    else
    {
        comp->id = VERTICAL;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_arriba( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = UP_IGUAL;
    }
    else
    {
        comp->id = UP;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_menor( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = MENOR_IGUAL;
    }
    else if ( c == '<' )
    {
        c = siguiente_char();
        if ( c == '=' )
        {
            comp->id = MENOR_MENOR_IGUAL;
        }
        else
        {
            comp->id = MENOR_MENOR;
            devolver();
        }   
    }
    else
    {
        comp->id = MENOR;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_mayor( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = MAYOR_IGUAL;
    }
    else if ( c == '>' )
    {
        c = siguiente_char();
        if ( c == '=' )
        {
            comp->id = MAYOR_MAYOR_IGUAL;
        }
        else
        {
            comp->id = MAYOR_MAYOR;
            devolver();
        }   
    }
    else
    {
        comp->id = MAYOR;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_igual( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = IGUAL_IGUAL;
    }
    else
    {
        comp->id = IGUAL;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_exclamacion( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = EXCLAMACION_IGUAL;
    }
    else
    {
        comp->id = EXCLAMACION;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_dos_puntos( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '=' )
    {
        comp->id = DOSPUNTOS_IGUAL;
    }
    else
    {
        comp->id = DOSPUNTOS;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;
}

void _automata_punto( int* estado, componente* comp )
{
    char c = siguiente_char();
    if ( c == '.' )
    {
        c = siguiente_char();
        if( c == '.' )
        {
            comp->id = TRESPUNTOS;
        }
        else
        {
            devolver();   
            comp->id = PUNTO;
            comp->lexema = get_lexema();
            devolver();
            *estado = FINAL;
        }
    }
    else if ( isDigit(c) )
    {
        devolver();
        devolver();
        _automata_numeros( estado, comp );
    }
    else
    {
        comp->id = PUNTO;
        devolver();
    }
    comp->lexema = get_lexema();
    *estado = FINAL;

}

void _automata_string( int* estado, componente* comp ){

    char c = siguiente_char();
    while ( *estado != FINAL )
    {
        if ( c == '\\')
        {
            c = siguiente_char();
            c = siguiente_char();
        }
        else if ( c == '\"' )
        {
            comp->id = STRING;
            comp->lexema = get_lexema();
            *estado = FINAL;
        }
        
        else
        {
            c = siguiente_char();
        }
    }

}

//PUBLIC FUNCTIONS
//----------------

/*      Esta es la funcion principal del analizador lexico, se ecarga
 *      de proporcionar al analizador sintactico una estructura que contenga
 *      la id del componente lexico y el propio lexema.
 * 
 *      Desde la llamada a esta funcion de inicializan y declaran variables asi
 *      como se decide a que subautomata se llamará para continuar con el
 *      analisis léxico.
 */

componente siguiente() {

    //declaracion de componente
    componente comp;
    comp.id = 0;
    comp.lexema = NULL;

    //declaracion de variables
    char c;
    int estado = 0;

    //inicializacion de analisis del componente
    mover_inicio();
    c = siguiente_char();

    //bucle hasta encontrar un componente lexico
    while ( estado != FINAL )
    {
        
        //ha habido un comentario previamente
        if (estado == COMENTARIO)
        {
            c = siguiente_char();
        }
        
        //cadena alfanumerica
        if ( isLetter(c) || c =='_' )
            _automata_cadena_alfanumerica( &estado, &comp );
        
        //digito
        else if ( isDigit(c) )
            _automata_numeros( &estado, &comp );
            
        //puntuación  
        else if ( isPunctuation(c) )
        {
            comp.id = c;
            comp.lexema = get_lexema();
            estado = FINAL;
        }
        //espacio
        else if ( c == ' ' || c == '\n' )
        {
            mover_inicio();
            c = siguiente_char();
        }
        else if ( c == '+')
            _automata_mas( &estado, &comp );
        
        else if (c == '-')
            _automata_menos( &estado, &comp );
            
        else if (c == '*')
            _automata_asterisco( &estado, &comp );
            
        else if (c == '/')
            _automata_barra_inclinada( &estado, &comp );
            
        else if (c == '%')
            _automata_porcentaje( &estado, &comp );
            
        else if (c == '&')
            _automata_ampersand( &estado, &comp );

        else if ( c == '|')
            _automata_barra_vertical( &estado, &comp );
            
        else if ( c == '^')
            _automata_arriba( &estado, &comp );
            
        else if ( c == '<')
            _automata_menor( &estado, &comp );
            
        else if ( c == '>')
            _automata_mayor( &estado, &comp );
            
        else if ( c == '=')
            _automata_igual( &estado, &comp );
            
        else if ( c == '!')
            _automata_exclamacion( &estado, &comp );
            
        else if ( c == ':')
            _automata_dos_puntos( &estado, &comp );

        else if ( c == '.')
            _automata_punto( &estado, &comp );

        else if ( c == '\"' )
            _automata_string( &estado, &comp );

        else if ( c == EOF)
        {
            comp.id = EOF;
            comp.lexema = get_lexema();
            estado = FINAL;
        }
        else
        {
            error(2, "Caracter no reconocido.");
            estado = FINAL;
        }

    }

    return comp;

}