#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"treap.h"
#define BUFFER 20
struct no
{
    no_t *esq,*dir;
    int chave, prio;
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
int comando(char* entry){
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
no_t* rotar_esq(no_t* aux){
    no_t* temp_dir = aux->dir;
    no_t* temp_dir_esq = temp_dir->esq;
    temp_dir->esq=aux;
    aux->dir = temp_dir_esq;
    aux = temp_dir;
    return aux;
}
no_t* rotar_dir(no_t* aux){
    no_t* temp_esq = aux->esq;
    no_t* temp_esq_dir = temp_esq->dir;
    temp_esq->dir=aux;
    aux->esq = temp_esq_dir;
    aux = temp_esq;
    return aux;
}
int busca(no_t*raiz,int chave){
    no_t* procura = raiz;
    while (procura!=NULL)
    {
        if (chave>procura->chave)
        {
            procura = procura->dir;
        }else if(chave<procura->chave)
        {
            procura = procura->esq;
        }
        else
        {
            break;
        }
    }
    if(procura==NULL) return 0;
    else return 1;
}
void update(no_t* raiz){
    no_t* aux = raiz;
    while (aux!=NULL)
    {
        if (aux->esq!=NULL&&aux->esq->prio>aux->prio)
        {
            printf("rot dir %d > prio que %d\n",aux->esq->chave,aux->chave);
            aux = rotar_dir(aux);
        }else if (aux->dir!=NULL&&aux->dir->prio>aux->prio)
        {
            printf("rot esq %d > prio que %d\n",aux->dir->chave,aux->chave);
            aux = rotar_esq(aux);
        }
        update(aux->esq);
        update(aux->dir);
        
    }
    
}
no_t* addNO(int chave,int prio){
    no_t* temp = (no_t*)malloc(sizeof(no_t));
    temp->chave=chave;
    temp->prio=prio;
    temp->esq=NULL;
    temp->dir=NULL;
    return temp;
}
void insert(no_t* raiz,int chave,int prio){
    no_t* aux = raiz;
    no_t* inserido = addNO(chave,prio);
    if(aux==NULL){
        aux = inserido;
        return;
    }
    while (aux!=NULL)
    {
        if (chave>aux->chave)
        {
            aux = aux->dir;
        }else if(chave<aux->chave)
        {
            aux = aux->esq;
        }
        else
        {
            break;
        }
    }
    aux = inserido;
    update(raiz);
}