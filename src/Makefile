#makefile
#by Rodrigo Miranda

# Nome do compilador
CC = gcc

# Nome do executável final
EXEC = programa

# Arquivos fonte e objetos
SRCS = main.c funcoes.c
OBJS = main.o funcoes.o

# Regra principal: compilar e rodar
run: $(EXEC)
	./$(EXEC)

# Compila o programa principal a partir dos arquivos objeto
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Regra genérica: compila qualquer arquivo .c para .o
%.o: %.c
	$(CC) -c $< -o $@

# Remove arquivos gerados na compilação
clean:
	rm -f $(EXEC) $(OBJS)
