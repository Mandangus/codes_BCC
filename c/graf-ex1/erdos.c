#include<stdio.h>
#include<stdlib.h>
#include<math.h>



double aleatorio()
{
    return (double)rand() / RAND_MAX;
}


int main(int argc,char* argv[]){
    int n;//numero de vertices
    double p;//probabilidade de conectar um par de vertices  onde "p E [0,1]"
    printf("Insira o número de vertices: ");
    scanf("%d",&n);
    printf("\n");
    getchar();
    printf("Insira a probabilidade entre 0 e 1: ");
    scanf("%lf",&p);
    getchar();
    printf("\n");
    int G[n][n];//matriz que contém o grafo onde 0 significa que não há aresta e 1 que há uma aresta

    /////////////////////////criando a matriz///////////////////////////////////////
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(aleatorio()<=p)//se a probabilidade acerta...
            {
                if (j>i)//e estamos acima da diagoal...
                {
                    G[i][j]=1;//o valor é 1
                    G[j][i]=G[i][j];//e o simetrico tambem
                }
                if (j==i) G[i][j]=0;//diagonal
            }else//se a probabilidade erra...
            {
                if (j>=i)//e estamos acima ou na diagonal
                {
                    G[i][j]=0;
                    G[j][i]=G[i][j];
                }
            }
        }
    }
///////////////////////////////////printando a matriz////////////////////////////
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ",G[i][j]);
        }
        printf("\n");
    }
///////////////////////////////////buscando o grau e aestas de um vertice///////////////////////
    int x,grau=0,busca,busca2;//pos do vertice desejado de pesquisa
    printf("\n");
    printf("\nConsulte um vertice:  ");
    scanf("%d",&x);
    for (int i = 0; i < n; i++)
    {
        if(G[x][i]==1)//se na linha tratando do vertice buscado existe um 1 então temos uma aresta!
        {
            grau++;//soma-se o grau
            printf("Tem uma aresta entre o vertice buscado e o %d\n",i);//e informamos a aresta
        }
    }
    printf("\nO grau do vertice %d é %d\n",x,grau);

/////////////////////////////buscando a aresta////////////////////////////
    printf("Buscando a aresta entre: ");
    scanf("%d %d",&busca,&busca2);
    if(G[busca2][busca]==1)
    {
        printf("Existe aresta entre %d e %d\n",busca2,busca);
    }else
    {
        printf("Não existe aresta entre %d e %d\n",busca2,busca);
    }

    return 0;
}