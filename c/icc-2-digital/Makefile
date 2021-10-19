arquivos_o = func.o main.o
arquivos_c = func.c main.c
arquivos_pgm = antes.pgm depois.pgm
all:$(arquivos_c) $(arquivos_o)
	gcc -c $(arquivos_c)
	gcc -o exec $(arquivos_o)
	rm $(arquivos_o)

run: exec
	./exec