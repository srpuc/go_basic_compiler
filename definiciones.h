#ifndef DEFINICIONES_H
#define DEFINICIONES_H

// COLORES TERMINAL
// ----------------

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


//VALORES ID
//----------

//identifiers
#define ID 300

//keywords
#define BREAK 301
#define CASE 302
#define CHAN 303
#define CONST 304
#define CONTINUE 305

#define DEFAULT 306
#define DEFER 307
#define ELSE 308
#define FALLTHROUGH 309
#define FOR 310

#define FUNC 311
#define GO 312
#define GOTO 313
#define IF 314
#define IMPORT 315

#define INTERFACE 316
#define MAP 317
#define PACKAGE 318
#define RANGE 319
#define RETURN 320

#define SELECT 321
#define STRUCT 322
#define SWITCH 323
#define TYPE 324
#define VAR 325

//operators and puctuatuion
#define MAS 500
#define MAS_IGUAL 501
#define MAS_MAS 502

#define MENOS 503
#define MENOS_IGUAL 504
#define MENOS_MENOS 505

#define POR 506
#define POR_IGUAL 507

#define DIV 508
#define DIV_IGUAL 509

#define MOD 510
#define MOD_IGUAL 511

#define AMPERSAND 512
#define AMPERSAND_IGUAL 513
#define AMPERSAND_AMPERSAND 514
#define AMPERSAND_UP 515
#define AMPERSAND_UP_IGUAL 516

#define VERTICAL 517
#define VERTICAL_IGUAL 518
#define VERTICAL_VERTICAL 519

#define UP 520
#define UP_IGUAL 521

#define MENOR 522
#define MENOR_MENOR 523
#define MENOR_MENOR_IGUAL 524
#define MENOR_IGUAL 525

#define MAYOR 526
#define MAYOR_MAYOR 527
#define MAYOR_MAYOR_IGUAL 528
#define MAYOR_IGUAL 529

#define IGUAL 530
#define IGUAL_IGUAL 531

#define EXCLAMACION 532
#define EXCLAMACION_IGUAL 533

#define DOSPUNTOS 534
#define DOSPUNTOS_IGUAL 535

#define COMA 44
#define PUNTOCOMA 59

#define PUNTO 537
#define TRESPUNTOS 538

#define PARENTESIS_IZQ 40
#define PARENTESIS_DER 41

#define CORCHETE_IZQ 91
#define CORCHETE_DER 93

#define LLAVE_IZQ 123
#define LLAVE_DER 125

#define TILDE 126

//literales
#define ENTERO 400
#define REAL 401
#define IMAGINARIO 402
#define HEX 403
#define FLOAT 404
#define STRING 405

#endif