#include<stdio.h>
#include<stdlib.h>



typedef struct vertice no_t;
typedef struct grafo graf_t;
typedef struct fila fil_t;
#define infinito __INT_MAX__
#define BUFFER 1024

struct vertice
{
    no_t* pai;
    int id;
    int visitado;   //  no pode ter sido visitado, portanto, nao o colocamos na queue
};

struct grafo
{
    int num_vert;
    int** matriz_adj;   //  pesos das edges
    no_t** vert;
};

struct fila
{
    int *fil;
    int frente;
    int costas;
};


//alocando uma nova fila...
fil_t* newFila()
{
    fil_t* queue = (fil_t*)malloc(sizeof(fil_t));
    queue->fil = (int*)malloc(sizeof(int)*BUFFER);
    queue->costas = -1;
    queue->frente = -1;
    return queue;
}

int isEmpty(fil_t queue)
{
    if (queue.costas == -1)
    {
        return 1;
    }
    return 0;
}

void printQueue(fil_t* queue)
{
    int frente = queue->frente;
    int costas = queue->costas;
    int count = frente;
    while (count<=costas)
    {
        printf("%d ",queue->fil[count]);
        count++;
    }
    printf("\n");
    
}

void enqueue(fil_t *queue,int valor)
{
    if (queue->frente == -1) queue->frente = 0;//caso for o primeiro elemento
    queue->costas++;
    queue->fil[queue->costas] = valor;
}

int dequeue(fil_t *queue)
{
    int valor;
    if (isEmpty(*queue))
    {
        printf("FILA VAZIA\n");
        valor = -1;
    }else
    {
        valor = queue->fil[queue->frente];
        queue->frente++;
        if (queue->frente > queue->costas)//fila se inverteu entao resetamos
        {
            queue->frente = -1;
            queue->costas = -1;
        }
        
    }
    
    return valor;
}

no_t* newNo(int id)
{
    no_t* no = (no_t*)calloc(1,sizeof(no_t));
    no->pai = NULL;
    no->id = id;
    no->visitado = 0;
    return no;
}


graf_t* newGrafo(int n)
{
    graf_t* g = (graf_t*)calloc(1,sizeof(graf_t));
    g->num_vert = n;
    g->matriz_adj = (int**)calloc(n,sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        g->matriz_adj[i] = (int*)calloc(n,sizeof(int));
    }
    g->vert = (no_t**)calloc(n,sizeof(no_t*));
    for (int i = 0; i < n; i++)
    {
        g->vert[i] = newNo(i);
    }
    
    return g;
}


void insertEdge(graf_t* g, int src, int dest, int weight)
{
    g->matriz_adj[src][dest] = weight;
    return;
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


void printMatriz(graf_t* g)
{
    if (g==NULL)
    {
        printf("Matriz vazia, grafo inexistente\n");
        return;
    }
    for (int i = 0; i < g->num_vert; i++)
    {
        for (int j = 0; j < g->num_vert; j++)
        {
            printf("%d ",g->matriz_adj[i][j]);
        }
        printf("\n");
    }
    
}

int* getWeights(int src,graf_t* g)
{
    return g->matriz_adj[src];
}

int* dijkstra(graf_t* g, int src)
{
    int v = g->num_vert;
    int *dists = (int*)malloc(v*sizeof(int));// setamos as distancias iniciais como infinito
    for (int i = 0; i < v; i++)
    {
        dists[i] = infinito;
    }
    dists[src] = 0;// a distancia para o proprio no sempre eh 0
    fil_t* q = newFila();
    enqueue(q,src);// entra na fila o inicial
    while (isEmpty(*q)!=1)
    {
        int atual = dequeue(q);
        g->vert[atual]->visitado = 2;// cor preta
        int* pesos = getWeights(atual,g);
        for (int i = 0; i < v; i++)
        {
            if (pesos[i]!=0)
            {
                if (g->vert[i]->visitado == 0)// caso seja branco
                {
                    enqueue(q,g->vert[i]->id);
                    g->vert[i]->visitado = 1;// cor cinza
                }
                if ((pesos[i] + dists[atual]) < dists[i])// o caminho visto é mais eficiente ?
                {
                    dists[i] = pesos[i] + dists[atual];
                }
                
            }
            
        }
        
    }
    
    
    return dists;// retorna a linha da matriz


}

int calcDig(int n)// função para se adpatar na formatação do runcodes
{
    int count = 0;
    if (n==0)
    {
        return 1;
    }
    
    while (n != 0) {
        n /= 10;     // n = n/10
        ++count;
    }
    return count;
}


void ressetDij(graf_t* g)
{
    int n = g->num_vert;
    for (int i = 0; i < n; i++)
    {
        g->vert[i]->visitado = 0;
    }
    
}

int main()
{
    char filename[30];
    scanf("%s[^\n]",filename);
    FILE* fp = fopen(filename,"r");



    fseek(fp,10,SEEK_SET);
    int n = readNum(fp);
    graf_t *g = newGrafo(n);

    int src = -1, dest = -1, weight = -1;
    fseek(fp,8,SEEK_CUR);
    do
    {
        src = readNum(fp);// inserindo a origem
        if (src==-1)
        {
            break;
        }
        
        dest = readNum(fp);// inserindo o destino
        weight = readNum(fp);// o peso da edge

        insertEdge(g,src-1,dest-1,weight);// indexado em 0

        getc(fp);
    }while (weight!=-1);
    

    int k = g->num_vert;
    int** distmatriz = (int**)malloc(sizeof(int*)*g->num_vert);
    for (int i = 0; i < k; i++)
    {
        distmatriz[i] = dijkstra(g,i);
        ressetDij(g);// resetando os valores visitado
    }
    int count = 0;
    for (int i = 0; i < g->num_vert; i++)
    {
        int w = calcDig(distmatriz[i][0]);// calculo do padding para a formatação
        if (w>count)
        {
            count= w;
        }
        
    }
    
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < g->num_vert; j++)
        {
            int padding = count - calcDig(distmatriz[i][j]);// formatação
            for (int l = 0; l < padding; l++)
            {
                printf(" ");
            }
             
            printf("%d ",distmatriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}