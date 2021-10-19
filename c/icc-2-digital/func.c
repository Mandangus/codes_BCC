#include<stdio.h>
#include<stdlib.h>
#include"func.h"

int** criar_matriz(int N,int T){
    srand(T);//ajustando a seed do rand
    int** matriz=(int**)malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++)
    {
        matriz[i]=(int*)malloc(N*sizeof(int));
        for (int j = 0; j < N; j++)
        {
            matriz[i][j]=rand()%256;//atribuindo um numero de 0-255 para o elemento
        }
        
    }
    return matriz;
}
void printar(int** matriz,int N){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t",matriz[i][j]);
        }
        printf("\n");
    }
    
}
void colocar(int** matriz,int N,FILE *fp){
    for (int i = 0; i < N; i++)
    {//similarmente ao print. colocamos cada elemento por um duplo for
        for (int j = 0; j < N; j++)
        {
            fprintf(fp,"%d\t",matriz[i][j]);
        }
        fprintf(fp,"\n");
    }
}
void busca_recursiva(int **matriz,int N,int x,int y,int T){
    int p = matriz[x][y];
    int esquerda=0,direita=0,cima=0,baixo=0;
    //checando a borda da imagem
    if (x<=0)
    {
        cima=1;
    }
    if (x>=N-1)
    {
        baixo=1;
    }
    if (y<=0)
    {
        esquerda=1;
    }
    if (y>=N-1)
    {
        direita=1;
    }
    if (cima==0)
    {
        if (abs(p-matriz[x-1][y])<=T)
        {
            if (matriz[x-1][y]!=p)//checando se não é igual
            {
                matriz[x-1][y]=p;
                busca_recursiva(matriz,N,x-1,y,T);//chamando para o próximo elemento
                return;
            }        
        } 
    }
    if (direita==0)
    {
        if (abs(p-matriz[x][y+1])<=T)
        {
            if (matriz[x][y+1]!=p)
            {
                matriz[x][y+1]=p;
                busca_recursiva(matriz,N,x,y+1,T);
                return;
            }        
        }        
    }
    if (baixo==0)
    {
        if (abs(p-matriz[x+1][y])<=T)
        {
            if (matriz[x+1][y]!=p)
            {
                matriz[x+1][y]=p;
                busca_recursiva(matriz,N,x+1,y,T);
                return;
            }        
        } 
    }
    if (esquerda==0)
    {
        if (abs(p-matriz[x][y-1])<=T)
        {
            if (matriz[x][y-1]!=p)
            {
                matriz[x][y-1]=p;
                busca_recursiva(matriz,N,x,y-1,T);
                return;
            }        
        } 
    }

    return;
    
}
