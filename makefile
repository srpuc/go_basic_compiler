CC=gcc -Wall -g

LIBS = -lm

HEADER_FILES_DIR = .

INCLUDES = -I $(HEADER_FILES_DIR)

OUTPUT = compilador

LIB_HEADERS = $(HEADER_FILES_DIR)/analizador_lexico.h analizador_sintactico.h tabla_simbolos.h abb.h sistema_entrada.h error.h

SRCS = main.c analizador_lexico.c analizador_sintactico.c tabla_simbolos.c abb.c sistema_entrada.c error.c

OBJS = $(SRCS:.c=.o)

$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS)

%.o: %.c $(LIB_HEADERS)
	$(CC) -c  $< $(INCLUDES)

cleanall: clean
	rm -f $(OUTPUT)

clean:
	rm -f *.o *~