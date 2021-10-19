#include<stdio.h>
#include<stdlib.h>

/*
*           NOME                    NUSP
*
*   Antonio Rodrigues Rigolino - 11795791 
*   
*   Vinícius Santos Monteiro - 11932463
*
*
*///

#define BUFFER 200

typedef struct vertice no_t;
typedef struct grafo graf_t;
typedef struct fila fil_t;

struct vertice
{
    no_t* paiX;
    no_t* paiY;
    int id;
    int visitado;   //  no pode ter sido visitado, portanto, nao o colocamos na queue
};

struct grafo
{
    int num_vert;
    int** matriz_adj;   // matriz de adjecencia
};

struct fila
{
    int *fil;
    int frente;
    int costas;
};

graf_t* newGrafo(int n)
{
    graf_t* g = (graf_t*)calloc(1,sizeof(graf_t));
    g->num_vert = n;
    g->matriz_adj = (int**)calloc(n,sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        g->matriz_adj[i] = (int*)calloc(n,sizeof(int));
    }
    
    return g;
}

int readNum(FILE*fp)
{
    int num = -1,pos = 0;
    char *aux = (char*)calloc(30,sizeof(char));
    char meuChar;
    do
    {
        meuChar = getc(fp);
        if (meuChar!='\n'&&meuChar!='\r'&&meuChar!=EOF&&meuChar!=' ')
        {
            aux[pos] = meuChar;
            pos++;
        }
        
    } while (meuChar!='\n'&&meuChar!='\r'&&meuChar!=EOF&&meuChar!=' ');
    
    if (meuChar == EOF)
    {
        return -1;
    }
    

    aux[pos] = '\0';
    num = atoi(aux);
    free(aux);


    return num;

}

void insertEdge(graf_t* g, int src, int dest, int weight)
{
    g->matriz_adj[src][dest] = weight;
    return;
}

int main(int argc,char* argv[])
{
    char filename[20];
    int tam_vert;
    scanf("%s",filename);
    FILE* fp_pajek = fopen(filename,"r");


    //quantos vertices?
    fseek(fp_pajek,10,SEEK_SET);//*Vertice_(ponteiro)(int)
    tam_vert = readNum(fp_pajek);
    graf_t* g = newGrafo(tam_vert);



    fseek(fp_pajek,21,SEEK_SET);//*Arcs\n(ponteiro)(int)_(int)
    
    int src = 0,dest = 0;
    while (src!=-1 && dest!=EOF)
    {
        src = readNum(fp_pajek);
        fseek(fp_pajek,3,SEEK_CUR);
        dest = readNum(fp_pajek);
        if (dest==EOF)
        {
            break;
        }
        
        insertEdge(g,src-1,dest-1,1);
        fseek(fp_pajek,1,SEEK_CUR);
    }
    
    int numFontes = 0;//numero de vertices fonte calculado pelas colunas vazias na matriz de adjecencia

    for (int i = 0; i < g->num_vert; i++)
    {
        int k = 0;
        for (int j = 0; j < g->num_vert; j++)
        {
            if (g->matriz_adj[j][i]==1)
            {
                k=1;
            }
            
        }
        if (k==0)
        {
            numFontes++;
        }
        
    }

    int numSovre = 0;//numero de vertices fonte calculado pelas linhas vazias na matriz de adjecencia
    for (int i = 0; i < g->num_vert; i++)
    {
        int k = 0;
        for (int j = 0; j < g->num_vert; j++)
        {
            if (g->matriz_adj[i][j]==1)
            {
                k=1;
            }
            
        }
        if (k==0)
        {
            numSovre++;
        }
        
    }
    
    printf("%d\n",numFontes);
    return 0;
}