#include<stdio.h>
#include<stdlib.h>
#define BUFFER 200


/*
*           NOME                    NUSP
*
*   Antonio Rodrigues Rigolino - 11795791 
*   
*   Vinícius Santos Monteiro - 11932463
*
*
*/

typedef struct vertice ver_t;
typedef struct pilha pil_t;
typedef struct grafo graf_t;
typedef struct fila fil_t;

struct vertice
{
    ver_t* paiX;
    ver_t* paiY;
    int visitado;
    int id;
};


struct pilha
{
    int topo;
    int* ids;
};

struct fila
{
    int *fil;
    int frente;
    int costas;
};

struct grafo
{
    ver_t **vertices;
    int **adje;//matriz de adjecencia
    int countVert;
};

fil_t* newFila(int num)
{
    fil_t* queue = (fil_t*)malloc(sizeof(fil_t));
    queue->fil = (int*)malloc(sizeof(int)*BUFFER);
    queue->costas = -1;
    queue->frente = -1;
    return queue;
}


int isEmptyQueue(fil_t queue)
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
    if (isEmptyQueue(*queue))
    {
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


pil_t* newPilha(int num)
{
    pil_t* p = (pil_t*)malloc(sizeof(pil_t));
    p->ids = (int*)malloc(sizeof(int)*BUFFER);
    p->topo=-1;
    return p;
}

graf_t* newGrafo(int num)
{
    graf_t* graf = (graf_t*) calloc(1,sizeof(graf_t));;
    graf->countVert = 0;
    graf->vertices = (ver_t**)calloc(num,sizeof(ver_t*));
    graf->adje = (int**)malloc(num*sizeof(int*));
    
    for (int i = 0; i < num; i++)
    {
        graf->adje[i] = (int*)calloc(num,sizeof(int));
    }

    return graf;
}


int pop(pil_t* p)//retirar do topo da pilha
{
    if (p->topo==-1)
    {
        printf("Pilha vazia!\n");
        return -1;
    }
    int retirado = p->ids[p->topo];
    p->topo--;
    return retirado;
}
void push(pil_t* p,int i)//empilhar
{
    p->topo++;
    p->ids[p->topo]=i;
}

int isEmpty(pil_t p)//utilidade para a pilha vazia...
{
    if (p.topo==-1)
    {
        return 1;
    }
    return 0;
}

void inserirGrafo(int id, graf_t *graf)//inserindo o vertice lido no grafo
{
    ver_t* ver = (ver_t*)malloc(sizeof(ver_t));
    ver->id = id;
    ver->visitado = 0;
    graf->vertices[graf->countVert] = ver;
    graf->countVert++;
}

void inserirAdje(graf_t *graf,int source,int desti)//inserindo as edges no grafo
{
    graf->adje[source][desti] = 1;

    if( graf->vertices[desti]->paiX == NULL ){

       graf->vertices[desti]->paiX = graf->vertices[source];

    }else{

        graf->vertices[desti]->paiY = graf->vertices[source];

    }
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

int* adjVisitDFS(int indice,graf_t graf,int*tam)//aqui contamos quais vertices nao visitados sao adjacentes ao vertice em questao
{

    //printf("buscar por pais\n");

    int count = 0;
    int* lista;
    for (int i = 0; i < graf.countVert; i++)
    {
        //if (graf.adje[indice][i] == 1 && graf.vertices[i]->visitado == 0)
        if ((graf.adje[i][indice] == 1 && graf.vertices[i]->visitado == 0) && graf.vertices[indice]->paiX != NULL &&( (i == graf.vertices[indice]->paiX->id ) || (i == graf.vertices[indice]->paiY->id) ) )
        {
            if (count == 0)
            {
                lista = (int*)malloc(sizeof(int));
            }else
            {
                lista = (int*)realloc(lista,sizeof(int)*(count+1));
            }
            //printf("\t\tteste i|%d|\n", i);
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

int readNum(FILE*fp)
{

    char* aux = (char*)calloc(BUFFER,sizeof(char));
    char meuChar = '\0';
    int i = 0;
    do
    {
        meuChar = getc(fp);
        if (meuChar!='\n'&&meuChar!=' '&&meuChar!=EOF&&meuChar!='\r')
        {
            aux[i] = meuChar;
            i++;
        }
    }while (meuChar!=' '&&meuChar!=EOF&&meuChar!='\r');
    if(meuChar==EOF) return -1;
    int numero = atoi(aux);

    return numero;
}
void printStack(pil_t p)//função usada para debugar o programa
{
    if (p.topo==-1)
    {
        printf("[]\n");
        return;
    }
    
    for (int i = 0; i <= p.topo; i++)
    {
        printf("[%d] ",p.ids[i]+1);
    }
    printf("\n");
}

int* BFS(graf_t graf,int qual)//bfs padrao com a mudança de que se acharmos o alvo vamos retraçar o caminho até o mesmo caso contrário retornamos 0 pois eh consigo mesmo
{
    fil_t *queue = newFila(graf.countVert);//criamos uma fila
    int* dist = (int*)calloc(graf.countVert,sizeof(int));
    graf.vertices[qual]->visitado = 1;//raiz visitada
    enqueue(queue,qual);//enfileiramos a raiz
    while (isEmptyQueue(*queue)!=1)//enquanto a fila nao estiver vazia...
    {
        int tam;
        int atual = dequeue(queue);//tiramos o primeiro...
        int* lista_adj = adjVisit(atual,graf,&tam);//checamos os adjacentes
        if (lista_adj!=NULL)//caso tenham adjacentes
        {
            for (int i = 0; i < tam; i++)
            {
                graf.vertices[lista_adj[i]]->visitado = 1;//adicionamos aos visitados

                dist[lista_adj[i]] = dist[atual] + 1;


                enqueue(queue,lista_adj[i]);//caso contrario seguimos enfileirando os vertices
            }
        }
        
    }
    
    return dist;
}


int DFS(graf_t graf,int target)
{

    int count = 0;
    ver_t* ver = graf.vertices[target];
    pil_t* p = newPilha(graf.countVert);
    push(p,ver->id);
    ver->visitado = 1;
    while (!isEmpty(*p))//enquanto a pilha não estiver vazia...
    {
        int tam;
        int id = pop(p);//retiramos o próximo elemento
        count++;
        if (id==-1)
        {
            return -2;
        }else if( id == 0 ){
            return 1;
        }

        int* lisAdj = adjVisitDFS(id,graf,&tam);//pegamos a lista de todos os vertices adjacentes e não visitados
        
        if (lisAdj!=NULL)//caso essa lista não for nula...
        {
            for (int i = 0; i < tam; i++)
            {
                graf.vertices[lisAdj[i]]->visitado = 1;//adicionamos aos visitado
                
                push(p,lisAdj[i]);//empilhamos novos vertices
            }
        }
    }

    return 0;//retornando o número de vertices dessa chamada, portanto, desse componente
}



int main()
{

    char filename[20];
    int tam_vert;
    scanf("%s",filename);
    FILE* fp_pajek = fopen(filename,"r");


    //quantos vertices?
    fseek(fp_pajek,10,SEEK_SET);//*Vertice_(ponteiro)(int)
    tam_vert = readNum(fp_pajek);
    graf_t* graf = newGrafo(tam_vert);

    for (int i = 0; i < tam_vert; i++)
    {
        inserirGrafo(i, graf);
    }
    fseek(fp_pajek,8,SEEK_CUR);//*Edges\n(ponteiro)(int)_(int)

    int src = 0,dest = 0;

    while (src!=-1 && dest!=EOF)
    {
        src = readNum(fp_pajek);
        if( src == -1 ){ break; }
        fseek(fp_pajek,3,SEEK_CUR);
        
        dest = readNum(fp_pajek);
        if (dest==EOF)
        {
            break;
        }
            inserirAdje(graf,src-1,dest-1);

            
        
    }

    int cont;
    int minimoGlobal = __INT_MAX__;//definindo um minimo global de distancia para o vertice 1
    int k = 0;
    int verts[BUFFER];

    for( int i = 0 ; i < tam_vert ; i++ ){

        cont = 0;

        for(int j = i ; j < tam_vert ; j++){

            if( graf->adje[i][j] == 1 ){

                cont++;
                break;

            }

        }

        if( cont == 0 ){

            int paiX = DFS(*graf, graf->vertices[i]->paiX->id);
            for( int i = 0 ; i < tam_vert ; i++ ){

                graf->vertices[i]->visitado = 0;

            }
            int paiY = DFS(*graf, graf->vertices[i]->paiY->id);
            for( int i = 0 ; i < tam_vert ; i++ ){

                graf->vertices[i]->visitado = 0;

            }

            if( (paiX == 1) && (paiY == 1) ){
                verts[k] = i;
                k++;
            }

        }

    }


    int* d = BFS(*graf,0);
    
    for (int i = 0; i < k; i++)
    {
        int v = graf->vertices[verts[i]]->id;
        int dx = d[graf->vertices[v]->paiX->id];
        int dy = d[graf->vertices[v]->paiY->id];
        if (dx + dy < minimoGlobal)// se as distancias dos pais sao menores atualizamos o minimo Global do grafo
        {
            minimoGlobal = dx + dy;
        }
        
    }
    for (int i = 0; i < k; i++)
    {
        int v = graf->vertices[verts[i]]->id;
        int dx = d[graf->vertices[v]->paiX->id];
        int dy = d[graf->vertices[v]->paiY->id];
        if (dx + dy == minimoGlobal)// printamos os vertices que possuem as distancias de seus pais igual ao minimo global
        {
            printf("%d\n",v+1);
        }
    }
    

    return 0;
}