#include<stdio.h>
#include<stdlib.h>
#include"func.h"

int main(){
    int N,x,y,T;//variaveis pedidas...
    FILE *antes,*depois;//file pointers para cada estado da matriz
    scanf("%d %d %d %d",&N,&x,&y,&T);
    antes=fopen("antes.pgm","w");
    fprintf(antes,"P3\n%d %d\n255\n",N,N);//cabeçalho do PGM onde P3 indica uma imagem colorida e os N as dimensoes da imagem
    depois=fopen("depois.pgm","w");
    fprintf(depois,"P3\n%d %d\n255\n",N,N);
    int** matriz;
    matriz=criar_matriz(N,T);//alocando a matriz dinamicamente
    colocar(matriz,N,antes);//colocando ela no file
    printar(matriz,N);//um print basico
    busca_recursiva(matriz,N,x,y,T);//a busca recursiva
    colocar(matriz,N,depois);//colocando a resultante no file "depois.pgm"
    printf("\n");
    printar(matriz,N);


    return 0;
}