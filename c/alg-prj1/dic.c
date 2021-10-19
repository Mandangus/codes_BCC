#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"dic.h"
#define BUFFER 1024

struct no
{
    int key;//no caso desse programa decidi usar a key como o char da letra inicial do termo!
    char* definicao;
    char* termo;
    no_t **next;
};


struct skip_list
{
    int max;
    int ran;
    int level;
    no_t *ini;
};

no_t*addNo(int key,int level,char*termo){
    no_t* not=(no_t*)malloc(sizeof(no_t));
    not->key=key;
    not->termo=termo;
    if (termo!=NULL)
    {
        char* defini=read_line(2);
        
        not->definicao=defini;
    }else
    {
        not->definicao=NULL;
    }
    
    
    not->next=(no_t**)malloc((level+1)*sizeof(no_t*));//como todo nó está ligado no nível mais básico fazemos level+1
    for (int i = 0; i < level+1; i++)
    {
        not->next[i]=NULL;
    }
    return not;
}

slist_t* initialize(int max){
    slist_t* list=(slist_t*)malloc(sizeof(slist_t));
    list->max=max;//máximo de altura para a lista!
    list->ran=RAND_MAX/2;
    list->level=0;
    list->ini=addNo(-1,max,NULL);//sentinela da minha skip_list portanto terá altura máxima!
    return list;
}
///////////////////FUNÇÕES DE UTILIDADE/////////////////////////////////////////////
void printar(no_t* atual){
    printf("%s %s\n",atual->termo,atual->definicao);
}
char* read_line(int chave){//se a chave for 1 le como comando se for 2 como definicao
    char* pal=(char*)malloc(BUFFER*sizeof(char));
    char letra;
    int pos=0;
    if (chave==1)
    {
        do
        {
            letra=getc(stdin);
            if (letra!='\n'&&letra!=' '&&letra!='\r')
            {
                pal[pos]=letra;
            }
            pos++;
        } while (letra!='\n'&&letra!=' '&&letra!='\r');
        

    }else
    {
        do
        {
            letra=getc(stdin);
            if (letra!='\n'&&letra!='\r')
            {
                pal[pos]=letra;
            }
            pos++;
        } while (letra!='\n'&&letra!='\r');
    }
    pal[pos]='\0';
    return pal;
}

int read_entry(char* entry){
    //reconhecendo o comando...
    char comandos[5][20]={"insercao","remocao","busca","impressao","alteracao"};
    if (strcmp(entry,comandos[0])==0)
    {
        return 1;
    }
    if (strcmp(entry,comandos[1])==0)
    {
        return 2;
    }
    if (strcmp(entry,comandos[2])==0)
    {
        return 3;
    }
    if (strcmp(entry,comandos[3])==0)
    {
        return 4;
    }
    if (strcmp(entry,comandos[4])==0)
    {
        return 5;
    }
}
int new_level(slist_t* list){
    float ran = rand()%RAND_MAX;
    int level = 0;
    while (ran < (list->ran) && level < list->max)//fazemos um coinflip para cada nível se der "cara", ou seja, 
                                                  //rand < list->frac continuamos a incrementar níveis.
    {                                             //caso o nivel máximo for atingido ou o coinflip for perdido retornamos o tamanho obtido
        level++;
        ran = rand()%RAND_MAX;
    }
    return level;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void destroy(slist_t* list){
    if (list==NULL)
    {
        return;
    }
    no_t *aux,*atual;
    atual=list->ini->next[0];
    while (atual!=NULL)
    {
        //avança para o next e remove o no
        aux = atual;
        atual = atual->next[0];//vai pro next
        free(aux->next);//remove as ligações
        free(aux);//remove o no
    }
    free(list->ini);
    free(list);
}
no_t* busca(slist_t* list,char*termo){
    if (list==NULL)
    {
        return 0;
    }
    no_t* atual=list->ini;
    for (int i = list->level; i >= 0; i--)//vindo do topo para baixo...
    {
        if (atual->next[i]==NULL)
        {
            break;
        }
        while (atual->next[i]!=NULL&&strcmp(atual->next[i]->termo,termo)<0)
        {
            atual = atual->next[i];//assim nos movemos para a direita até que o próximo nó seja maior do que key! ou NULL
        }
        
    }
    //ao sair desse loop duplo a próxima chave deve ser aquela que buscamos!
    atual = atual->next[0];
    if (atual==NULL)
    {
        printf("OPERACAO INVALIDA\n");
        return 0; 
    }
    
    if (strcmp(atual->termo,termo)!=0)
    {
        printf("OPERACAO INVALIDA\n");
        return 0;
    }
    
    return atual;
}
void insert(slist_t* list,int key,char* termo){
    if (list==NULL)
    {
        return;
    }
    no_t* atual = list->ini;
    no_t** aux=(no_t**)malloc((list->max+1)*sizeof(no_t*));
    for (int i = 0; i <= list->max; i++)
    {
        aux[i]=NULL;
    }
    for (int i = list->level; i >= 0; i--)//fazemos uma operação similar a busca!
    {
        while (atual->next[i]!=NULL&&strcmp(atual->next[i]->termo,termo)<0)
        {
            atual = atual->next[i];
        }
        aux[i]=atual;
    }

    atual=atual->next[0];

    if (atual==NULL||strcmp(atual->termo,termo)!=0)
    {
        int level = new_level(list);
        //alocando o novo nó
        no_t* new = addNo(key,level,termo);

        if (level>list->level)
        {
            //temos um nível maior do que o maior préviamente na lista lista!
            for (int i = list->level+1; i <= level; i++)
            {
                //atualizamos a lista aumentando-a para o tamanho maior!
                aux[i] = list->ini;
            }
            list->level = level;
        }

        //agora temos que arrumar os ponteiros!
        for (int i = 0; i <= level; i++)//da base da lista até a altura do nó!
        {
            new->next[i] = aux[i]->next[i];//o novo nó aponta para aquele que o anterior a ele apontava
            aux[i]->next[i] = new;//e o anterior a ele aponta para o novo
        }
        free(aux);
    }
    else
    {
        printf("OPERACAO INVALIDA\n");
    }
    
}
void retirar(slist_t* list,int key,char*termo){
    if (list==NULL)
    {
        return;
    }
    no_t* atual=list->ini;
    no_t** aux= (no_t**)malloc((list->max+1)*sizeof(no_t*));
    for (int i = 0; i <=list->max; i++)
    {
        aux[i]=NULL;
    }
    for (int i = list->level; i >=0; i--)//mesmo processo do insert!
    {
        if (atual->next[i]==NULL)
        {
            break;
        }
        
        while (atual->next[i]!=NULL&&strcmp(atual->next[i]->termo,termo)<0)
        {
            atual = atual->next[i];
        }
        aux[i] = atual;
    }
    atual = atual->next[0];
    if (atual==NULL)
    {
        printf("OPERACAO INVALIDA\n");
        return;
    }
    
    if (strcmp(atual->termo,termo)==0)
    {
        for (int i = 0; i <=list->level; i++)
        {
            if (aux[i]->next[i]!=atual)
            {//se for diferente o ajuste ja foi feito!
                break;
            }
            aux[i]->next[i]=atual->next[i];//"remendamos" a lista passando o anterior->prox para atual->prox!
        }
        //se existem níveis vagos que apontam para NULL vamos retirar
        while (list->level>0 && list->ini->next[list->level]==NULL)
        {
            list->level--;
        }
        free(atual->next);
        free(atual);
        free(aux);
    }else
    {
        printf("OPERACAO INVALIDA\n");
    }
    

}
void altera(slist_t* list,char*termo){
    no_t* atual = busca(list,termo);
    if (atual!=0)
    {
        atual->definicao = read_line(2);
        
    }
    return;
}
void imprime(slist_t* list,char c1){
    no_t* atual=list->ini;
    int quant=0;
    while (atual!=NULL)
    {
        if (atual->key==c1)
        {//printando todos no nivel mais baixo. Como os termos são inseridos de maneira ordenada é só imprimir em ordem
            printar(atual);
            quant++;
        }
        atual=atual->next[0];        
    }
    if (quant==0)
    {
        printf("OPERACAO INVALIDA\n");
    }
         
}