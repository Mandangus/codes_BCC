
CC=gcc
LIBS=-Wall -Wextra -Wpedantic -pedantic-errors
CFLAGS=-c -g -O0
VFLAGS=--leak-check=full --track-origins=yes --show-leak-kinds=all --main-stacksize=8388608
BINARY=./database
DEP= veiculo.o linha.o mainveiculo.o funcoes-gerais.o

all: createDirObjects $(DEP)
	$(CC) $(DEP) -o $(BINARY) 


run:
	$(BINARY)

valgrind:
	valgrind $(VFLAGS) $(BINARY)

clear:
	rm -rf ./objects $(BINARY)