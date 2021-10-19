#include<stdio.h>
#include<stdlib.h>
#define BUFFER 200 //buffer para o tamanho da fila estatica
/*
            ANTONIO RODRIGUES RIGOLINO 
                nUSP - 11795791

*/
typedef struct vertice ver_t;
typedef struct grafo graf_t;
typedef struct fila fil_t;

struct vertice
{
    int id;//numero associado
    int visitado;//se foi visitado ou nao ao inves do sistema de cores
    ver_t* pai;//ponteiro para o vertice pai afim de calcular a distancia
};

struct grafo
{
    ver_t **vertices;
    int **adje;//matriz de adjecencia
    int countVert;
};

struct fila
{
    int *fil;
    int frente;
    int costas;
};


//alocando uma nova fila...
fil_t* newFila(int num)
{
    fil_t* queue = (fil_t*)malloc(sizeof(fil_t));
    queue->fil = (int*)malloc(sizeof(int)*BUFFER);
    queue->costas = -1;
    queue->frente = -1;
    return queue;
}
//alocando um novo grafo...
graf_t newGrafo(int num)
{
    graf_t graf;
    graf.countVert = 0;
    graf.vertices = (ver_t**)malloc(num*sizeof(ver_t*));
    graf.adje = (int**)malloc(num*sizeof(int*));
    for (int i = 0; i < num; i++)
    {
        graf.adje[i] = (int*)malloc(num*sizeof(int));
    }
    
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
            graf.adje[i][j]=0;
    }
    return graf;
}




int isEmpty(fil_t queue)
{
    if (queue.costas == -1)
    {
        return 1;
    }
    return 0;
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

void inserirGrafo(int id,graf_t *graf)//inserindo o vertice lido no grafo
{
    ver_t* ver = (ver_t*)malloc(sizeof(ver_t));
    ver->pai = NULL;
    ver->id = id;
    ver->visitado = 0;
    graf->vertices[graf->countVert] = ver;
    graf->countVert++;
}

void inserirAdje(graf_t *graf,int source,int desti)//inserindo as edges no grafo
{
    graf->adje[source][desti] = 1;
    graf->adje[desti][source] = 1;
}


int* adjVisit(int indice,graf_t graf,int*tam)//aqui contamos quais vertices nao visitados sao adjacentes ao vertice em questao
{
    int count = 0;
    int* lista;
    for (int i = 0; i < graf.countVert; i++)
    {
        if (graf.adje[indice][i] == 1 && graf.vertices[i]->visitado == 0)
        {
            if (count == 0)
            {
                lista = (int*)malloc(sizeof(int));
            }else
            {
                lista = (int*)realloc(lista,sizeof(int)*(count+1));
            }
            lista[count] = i;
            count++;
        }
        
    }
    if (count==0)
    {
        return NULL;//nao existem!
    }else{
        *tam = count;
        return lista;
    }
    
}

int calcDist(ver_t* alvo)//refazemos o caminha a partir do ponteiro pai para descubrir a distancia
{
    int dist = 0;
    ver_t* aux = alvo;
    while (aux->pai!=NULL)
    {
        aux = aux->pai;
        dist++;
    }
    
    return dist;
}

void clear_bfs(graf_t graf)//arrumando o vertices apos o uso no bfs
{
    for (int i = 0; i < graf.countVert; i++)
    {
        graf.vertices[i]->pai = NULL;
        graf.vertices[i]->visitado = 0;
    }

}


int BFS(graf_t graf,int qual,int ate)//bfs padrao com a mudança de que se acharmos o alvo vamos retraçar o caminho até o mesmo caso contrário retornamos 0 pois eh consigo mesmo
{
    fil_t *queue = newFila(graf.countVert);//criamos uma fila
    int dist = 0;
    graf.vertices[qual]->visitado = 1;//raiz visitada
    enqueue(queue,qual);//enfileiramos a raiz
    while (isEmpty(*queue)!=1)//enquanto a fila nao estiver vazia...
    {
        int tam;
        int atual = dequeue(queue);//tiramos o primeiro...
        int* lista_adj = adjVisit(atual,graf,&tam);//checamos os adjacentes
        if (lista_adj!=NULL)//caso tenham adjacentes
        {
            for (int i = 0; i < tam; i++)
            {
                graf.vertices[lista_adj[i]]->visitado = 1;//adicionamos aos visitados
                graf.vertices[lista_adj[i]]->pai = graf.vertices[atual];//setamos o ponteiro pai
                if (graf.vertices[lista_adj[i]]->id==ate)//caso seja o alvo...
                {
                    return calcDist(graf.vertices[lista_adj[i]]);//retornamos a distancia
                }
                
                enqueue(queue,lista_adj[i]);//caso contrario seguimos enfileirando os vertices
            }
        }
        
    }
    
    return dist;
}

int readNum(FILE*fp)
{
    char* aux = (char*)calloc(BUFFER,sizeof(char));
    char meuChar;
    int i = 0;
    do
    {
        meuChar = getc(fp);
        if (meuChar!='\n'&&meuChar!=' '&&meuChar!=EOF)
        {
            aux[i] = meuChar;
            i++;
        }
    }while (meuChar!='\n'&&meuChar!=' '&&meuChar!=EOF);
    if(meuChar==EOF) return -1;
    int numero = atoi(aux);

    return numero;
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
    //criando um grafo e uma fila novos
    graf_t graf = newGrafo(tam_vert);
    for (int i = 1; i <= tam_vert; i++)
    {
        inserirGrafo(i,&graf);
    }
    
    fseek(fp_pajek,8,SEEK_CUR);//*Edges\n(ponteiro)(int)_(int)
    int src = 0,dest = 0;
    while (src!=-1)
    {
        src = readNum(fp_pajek);
        if (src!=-1)
        {
            dest = readNum(fp_pajek);
            inserirAdje(&graf,src-1,dest-1);
        }
    }

    int distancias[tam_vert][tam_vert];//setando a matriz de distancias...
    for (int i = 0; i < tam_vert; i++)
    {
        for (int j = 0; j < tam_vert; j++)
        {
            distancias[i][j] = 0;
        }
    }


    for (int i = 0; i < tam_vert; i++)//fazendo o BFS
    {
        for (int j = 0; j < tam_vert; j++)
        {
            int dis = BFS(graf,i,j+1);
            distancias[i][j] = dis;
            clear_bfs(graf);
        }
        
    }
    

    for (int i = 0; i < tam_vert; i++)
    {
        for (int j = 0; j < tam_vert; j++)
        {
            printf("%d ",distancias[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}