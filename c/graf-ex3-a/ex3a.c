#include<stdio.h>
#include<stdlib.h>
#define BUFFER 200


typedef struct vertice ver_t;
typedef struct pilha pil_t;
typedef struct grafo graf_t;

struct vertice
{
    ver_t* pai;
    int visitado;
    int id;
};


struct pilha
{
    int topo;
    int* ids;
};


struct grafo
{
    ver_t **vertices;
    int **adje;//matriz de adjecencia
    int countVert;
};


pil_t* newPilha(int num)
{
    pil_t* p = (pil_t*)malloc(sizeof(pil_t));
    p->ids = (int*)malloc(sizeof(int)*BUFFER);
    p->topo=-1;
    return p;
}

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
        //printStack(*p);
        int id = pop(p);//retiramos o próximo elemento
        count++;
        if (id==-1)
        {
            return -1;
        }
        int* lisAdj = adjVisit(id,graf,&tam);//pegamos a lista de todos os vertices adjacentes e não visitados
        if (lisAdj!=NULL)//caso essa lista não for nula...
        {
            for (int i = 0; i < tam; i++)
            {
                graf.vertices[lisAdj[i]]->visitado = 1;//adicionamos aos visitados
                graf.vertices[lisAdj[i]]->pai = graf.vertices[id];//setamos o ponteiro pai
                push(p,lisAdj[i]);//empilhamos novos vertices
            }
        }
    }
    return count;//retornando o número de vertices dessa chamada, portanto, desse componente
}



int main()
{
    char filename[50];
    int tam_vert;
    scanf("%s",filename);
    FILE* fp_pajek = fopen(filename,"r");
    FILE* fp_txt = fopen("saida.txt","w");
    fseek(fp_pajek,10,SEEK_SET);//*Vertice_(ponteiro)(int)
    tam_vert = readNum(fp_pajek);
    graf_t graf = newGrafo(tam_vert);
    for (int i = 0; i < tam_vert; i++)
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
    //  para pegar os componentes de cada grafo vamos chamar um DFS para cada vértice não visitado, assim garantindo que passemos por todos os possíveis componentes do grafo
    int comp_count = 0;
    int* comp_size_vect=(int*)calloc(tam_vert,sizeof(int));
    for (int i = 0; i < tam_vert; i++)
    {
        if (graf.vertices[i]->visitado==0)
        {
            comp_size_vect[comp_count] = DFS(graf,i);
            comp_count++;
        }
        
    }
    for (int i = 0; i < comp_count; i++)//  sorting bem primitivo só para arrumar o vetor para escrever para o arquivo txt
    {
        for (int j = 0; j < comp_count; j++)
        {
            if (comp_size_vect[i]<comp_size_vect[i+1])
            {
                int temp = comp_size_vect[i];
                comp_size_vect[i] = comp_size_vect[i+1];
                comp_size_vect[i+1] = temp;
            }
        }
    }
    //escrevendo para o arquivo..
    fprintf(fp_txt,"%d\n",comp_count);
    for (int i = 0; i < comp_count; i++)
    {
        fprintf(fp_txt,"%d\n",comp_size_vect[i]);
    }
    printf("%d\n",comp_count);
    for (int i = 0; i < comp_count; i++)
    {
        printf("%d\n",comp_size_vect[i]);
    }


    return 0;
}