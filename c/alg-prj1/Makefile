arquivos_o = dic.o main.o
arquivos_c = dic.c main.c
all:$(arquivos_c) $(arquivos_o)
	gcc -c $(arquivos_c)
	gcc -o exec $(arquivos_o)
	rm $(arquivos_o)

run: exec
	./exec < 2.in