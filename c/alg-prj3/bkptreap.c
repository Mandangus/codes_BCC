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
int busca(no_t* raiz,int chave){
    if (raiz==NULL) return 0;
    if (raiz->chave==chave) return 1;
    if (raiz->chave < chave) return busca(raiz->dir,chave);
    return busca(raiz->esq,chave);
}
no_t* addNO(int chave,int prio){
    no_t* aux = (no_t*)malloc(sizeof(no_t));
    aux->chave=chave;
    aux->prio=prio;
    aux->esq=NULL;
    aux->dir=NULL;
    return aux;
}
void insert(no_t* raiz,int chave,int prio){
    if (raiz==NULL)
    {
        raiz = addNO(chave,prio);
        return;
    }
    if (chave<raiz->chave)
    {
        insert(raiz->esq,chave,prio);
    }else
    {
        insert(raiz->dir,chave,prio);
    }
}
void update(no_t* raiz){
    printf("vou dar update");
    if (raiz!=NULL)
    {
        if (raiz->esq!=NULL&&raiz->esq->prio>raiz->prio)
        {
            printf("rot dir %d > prio que %d\n",raiz->esq->chave,raiz->chave);
            raiz = rotar_dir(raiz);
        }else if (raiz->dir!=NULL&&raiz->dir->prio>raiz->prio)
        {
            printf("rot esq %d > prio que %d\n",raiz->dir->chave,raiz->chave);
            raiz = rotar_esq(raiz);
        }
        update(raiz->esq);
        update(raiz->dir);
    }
    
    
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
    {//puxamos o no da esquerda pra cima no lugar do no removida
        no_t* temp = raiz->esq;
        free(raiz);
        raiz = temp;
    }
    else if (raiz->esq->prio>raiz->dir->prio)
    {
        raiz=rotar_esq(raiz);
        raiz->esq = remover(raiz->esq,chave);
        no_t* temp = raiz->esq;
        raiz->esq=raiz;
        raiz= temp;
    }
    else
    {
        raiz=rotar_esq(raiz);
        raiz->esq=remover(raiz->esq,chave);
    }
    return raiz;
    
}
void printar(no_t*raiz){
    if (raiz!=NULL)
    {
        printf("(%d, %d)\n",raiz->chave,raiz->prio);
        printar(raiz->esq);
        printar(raiz->dir);
    }
    
}
void printar_pos(no_t* raiz) 
{ 
    if (raiz) 
    { 
        printar_pos(raiz->esq);
        printf("(%d, %d)",raiz->chave,raiz->prio);
        if (raiz->esq) printf(" | filho esquerdo: (%d, %d)",raiz->esq->chave,raiz->esq->prio);
        if (raiz->dir) printf(" | filho direito: (%d, %d)",raiz->dir->chave,raiz->dir->prio);
        printf("\n");
        printar_pos(raiz->dir); 
    }
} 