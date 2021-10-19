#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"treap.h"
#define BUFFER 1024
struct no
{
    no_t *esq,*dir;
    int chave, prio;
};
struct fila//fila será usada no print da largura!
{
    no_t**memb;
    int tam;
};

char* read_line(){
    char letra;
    int pos=0;
    char* pal = malloc(BUFFER*sizeof(char));
    do
    {
        letra = getchar();
        if (letra!='\n'&&letra!=EOF&&letra!='\r'&&letra!=' ')
        {
            pal[pos]=letra;
            pos++;
        }
        
    } while (letra!='\n'&&letra!=EOF&&letra!=' ');
    pal[pos]='\0';
    return pal;
}
int comando(char* entry){//separando os comandos para usar um switch na main
    char v[4][20]={"insercao","remocao","impressao","buscar"};
    for (int i = 0; i < 4; i++)
    {
        if(strcmp(v[i],entry)==0) return i;
    }
    return -1;
    
}
int comando_printf(char* entry){
    char v[4][20]={"ordem","posordem","preordem","largura"};
    for (int i = 0; i < 4; i++)
    {
        if(strcmp(v[i],entry)==0) return i;
    }
    return -1;
    
}
no_t* pai(no_t* raiz,int chave){//função utilitária para buscar o pai de um nó
    if(raiz == NULL) return NULL;
    if(raiz->esq != NULL && raiz->esq->chave ==chave) return raiz;
    if(raiz->dir != NULL && raiz->dir->chave ==chave) return raiz;
    no_t* temp = pai(raiz->esq,chave);
    if(temp==NULL) temp = pai(raiz->dir,chave);
    return temp;
}
no_t* rotar_esq(no_t* aux){//giro para a esquerda
    no_t* temp_dir = aux->dir;
    no_t* temp_dir_esq = temp_dir->esq;
    temp_dir->esq=aux;
    aux->dir = temp_dir_esq;
    return temp_dir;
}
no_t* rotar_dir(no_t* aux){//giro para a direita que é usado APENAS no insert
    no_t* temp_esq = aux->esq;
    no_t* temp_esq_dir = temp_esq->dir;
    temp_esq->dir=aux;
    aux->esq = temp_esq_dir;
    return temp_esq;
}
no_t* busca(no_t*raiz,int chave){//busca básica O(logn)
    if(raiz == NULL||raiz->chave==chave) return raiz;
    if(raiz->chave<chave) return busca(raiz->dir,chave);
    return busca(raiz->esq,chave);
}
no_t* addNO(int chave,int prio){//função para alocar o espaço para um novo no
    no_t* aux = (no_t*)malloc(sizeof(no_t));
    aux->chave=chave;
    aux->prio=prio;
    aux->esq=NULL;
    aux->dir=NULL;
    return aux;
}
no_t* insert(no_t* raiz,int chave,int prio){//insert já com as rotações
    if(raiz==NULL) return addNO(chave,prio);//retornamos o nó alocado ao achar o lugar vago
    if (chave<raiz->chave)
    {
        raiz->esq=insert(raiz->esq,chave,prio);//buscamos na esquerda do no
        if (raiz->esq->prio>raiz->prio)//caso a condição da max heap seja ferida vamos rotacionar para restaurá-la
        {
            raiz = rotar_dir(raiz);
        }
        
    }
    else
    {
        raiz->dir = insert(raiz->dir,chave,prio);//buscamos na direita do no
        if (raiz->dir->prio>raiz->prio)//caso a condição da max heap seja ferida vamos rotacionar para restaurá-la
        {
            raiz = rotar_esq(raiz);
        }
        
    }
    return raiz;

}
no_t* remover(no_t* raiz,int chave){
    //mesma coisa que a busca mas quando achamos o no não retornamos
    if (raiz==NULL) return NULL;
    if (raiz->chave < chave) return remover(raiz->dir,chave);
    else if (raiz->chave > chave) return remover(raiz->esq,chave);
    else if (raiz->esq==NULL)
    {//puxamos o no da direita pra cima no lugar do no removido
        no_t* temp = raiz->dir;
        free(raiz);
        raiz = temp;
    }
    else if (raiz->dir==NULL)
    {//puxamos o no da esquerda pra cima no lugar do no removido
        no_t* temp = raiz->esq;
        free(raiz);
        raiz = temp;
    }
    else if (raiz->esq->prio>raiz->dir->prio)
    {//rotacionamos para a equerda afim de preservar a max heap e escolhemos um no filho para ocupar o lugar do falecido
        raiz=rotar_esq(raiz);
        raiz->esq = remover(raiz->esq,chave);
        no_t* temp = raiz->esq;
        if(temp==NULL) temp = raiz->dir;
        raiz->esq=raiz;
        raiz= temp;
    }
    else
    {//rotacionamos para a equerda afim de preservar a max heap
        raiz=rotar_esq(raiz);
        raiz->esq=remover(raiz->esq,chave);
    }
    return raiz;
    
}
fila_t* initialize(){//função para alocar a fila usada na impressão da largura
    fila_t* fi = (fila_t*)malloc(sizeof(fila_t));
    fi->tam = 0;
    fi->memb = (no_t**)malloc(BUFFER*sizeof(no_t*));
    return fi;
}
void printord(no_t*raiz){//ordem
    if (raiz!=NULL)
    {
        printord(raiz->esq);
        printf("(%d, %d) ",raiz->chave,raiz->prio);
        printord(raiz->dir);
    }
    
}
void printposord(no_t*raiz){//posordem
    if (raiz!=NULL)
    {
        printposord(raiz->esq);
        printposord(raiz->dir);
        printf("(%d, %d) ",raiz->chave,raiz->prio);
    }
    
}
void printpre(no_t*raiz){//preordem
    if (raiz!=NULL)
    {
        printf("(%d, %d) ",raiz->chave,raiz->prio);
        printpre(raiz->esq);
        printpre(raiz->dir);
    }
    
}
void push(fila_t* fi,no_t* not){//adicionar um elemento no final da fila
    fi->memb[fi->tam]=not;
    fi->tam++;
}
no_t* pop(fila_t* fi){//retirar e olhar para o primeiro elemento da fila
    no_t* temp = fi->memb[0];
    for (int i = 1; i < fi->tam; i++)
    {
        if(fi->memb[i]!=NULL) fi->memb[i-1]=fi->memb[i];
    }
    fi->tam--;
    return temp;
}
void printar_larg(no_t* raiz,fila_t* fi){
    if(raiz!=NULL) push(fi,raiz);//entra o no no final da fila
    //else return;
    while (fi->tam>0)
    {
        no_t* temp = pop(fi);//olhamos o primeiro a ser atendido e descartamos
        printf("(%d, %d) ",temp->chave,temp->prio);
        if(raiz->esq!=NULL) printar_larg(raiz->esq,fi);//olhamos para a esquerda
        if(raiz->dir!=NULL) printar_larg(raiz->dir,fi);//olhamos para a direita
    }
    return;
    
}