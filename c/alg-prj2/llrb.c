#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"llrb.h"
//regra 1: aresta vermelha do lado esq
//regra 2: incidencia de uma aresta vermelha eh no max 1
//regra 3: caminho das folhas até a raíz
struct no
{
    no_t *esq,*dir;
    int cor;//se 0 preto se 1 vermelho
    int id;
};

no_t*addNO(int chave){
    no_t* temp = (no_t*)malloc(sizeof(no_t));
    temp->esq=NULL;
    temp->dir=NULL;
    temp->id=chave;
    temp->cor=1;
    return temp;
}
no_t* rotar_esq(no_t* aux){
    no_t* temp_dir = aux->dir;
    no_t* temp_dir_esq = temp_dir->esq;
    temp_dir->esq=aux;
    aux->dir = temp_dir_esq;
    return temp_dir;
}
no_t* rotar_dir(no_t* aux){
    no_t* temp_esq = aux->esq;
    no_t* temp_esq_dir = temp_esq->dir;
    temp_esq->dir=aux;
    aux->esq = temp_esq_dir;
    return temp_esq;
}
void trocar_cor(no_t*trocar,no_t*trocador){//função utilitária para trocar a cor de nós
    int temp = trocar->cor;
    trocar->cor = trocador->cor;
    trocador->cor = temp;
}
no_t* insert(no_t* raiz,int chave){
    if(raiz==NULL) return addNO(chave);

    if (chave < raiz->id)  raiz->esq = insert(raiz->esq, chave); 
    else if (chave > raiz->id)  raiz->dir = insert(raiz->dir, chave); 
    else   return raiz; 


    //caso haja uma subtree na direita e a cor seja vermelha violamos a regra 1!
    if (raiz->dir!=NULL&&raiz->dir->cor==1&&(raiz->esq==NULL || raiz->esq->cor!=1))
    {
        raiz = rotar_esq(raiz);
        trocar_cor(raiz,raiz->esq);
    }
    //caso haja tanto uma esq vermelha quanto uma esq->esq vermelha violamos o caso 3 dos caminhos
    if (raiz->esq!=NULL&&raiz->esq->esq!=NULL&&raiz->esq->cor==1&&raiz->esq->esq->cor==1)
    {
        raiz = rotar_dir(raiz);
        trocar_cor(raiz,raiz->dir);
    }
    //caso haja tanto uma direita vermelha como uma esquerda violamos tanto a regra 1 como a 2
    if (raiz->dir!=NULL&&raiz->esq!=NULL&&raiz->esq->cor==1&&raiz->dir->cor==1)
    {
        if(raiz->cor==1) raiz->cor = 0;
        else raiz->cor = 1;
        raiz->dir->cor = 0;
        raiz->esq->cor = 0;
    }
    return raiz;
    
}
int maximo(no_t* raiz){//buscamos o maximo de cada subtree
    if(raiz==NULL) return 0;//<--- aqui evitamos qualquer tipo de retorno maior que alguma possibilidade na árvore
    int max = raiz->id;
    int maxesq = maximo(raiz->esq);
    int maxdir = maximo(raiz->dir);
    if (maxdir>max) max = maxdir;
    if (maxesq>max) max =maxesq;
    
    return max;
}
int minimo(no_t* raiz){//mesma coisa invertida
    if(raiz==NULL) return __INT_MAX__;//<--- aqui evitamos qualquer tipo de retorno menor que alguma possibilidade na árvore
    int max = raiz->id;
    int maxesq = minimo(raiz->esq);
    int maxdir = minimo(raiz->dir);
    if (maxdir<max) max = maxdir;
    if (maxesq<max) max = maxesq;
    return max;
}
no_t* pai(no_t* raiz,int chave){//dado um no achamos seu pai
    if(raiz == NULL) return NULL;
    if(raiz->esq != NULL && raiz->esq->id ==chave) return raiz;
    if(raiz->dir != NULL && raiz->dir->id ==chave) return raiz;
    no_t* temp = pai(raiz->esq,chave);
    if(temp==NULL) temp = pai(raiz->dir,chave);
    return temp;
}
void printord(no_t*raiz){//ordem
    if (raiz!=NULL)
    {
        printord(raiz->esq);
        printf("%d ",raiz->id);
        printord(raiz->dir);
    }
    
}
void printposord(no_t*raiz){//posordem
    if (raiz!=NULL)
    {
        printposord(raiz->esq);
        printposord(raiz->dir);
        printf("%d ",raiz->id);
    }
    
}
void printpre(no_t*raiz){//preordem
    if (raiz!=NULL)
    {
        printf("%d ",raiz->id);
        printpre(raiz->esq);
        printpre(raiz->dir);
    }
    
}
no_t* busca(no_t*raiz,int chave){
    if(raiz == NULL) return NULL;
    if(raiz->id==chave) return raiz;
    no_t* temp = pai(raiz->esq,chave);
    if(temp==NULL) temp = pai(raiz->dir,chave);
    return temp;
}
no_t* predecessor(no_t*raiz,int chave){
    if(raiz==NULL) return NULL;
    no_t* atual = busca(raiz,chave);
    if(atual==NULL) return NULL;
    no_t* pa = pai(raiz,atual->id);
    if (atual->esq!=NULL)//temos um no valido na esquerda
    {
        no_t* temp=atual->esq;//buscamos o maior no da válido subtree na esquerda do nosso alvo
        while (temp->dir!=NULL)
        {
            temp = temp->dir;
        }
        return temp;
    }
    else if (pa->esq!=NULL&&pa->esq==atual)//se estamos na esquerda de um no devemos subir até achar o primeiro pai que aponta para a direita
    {
        no_t* temp = pa;
        while (temp!=NULL&&pai(raiz,temp->id)->dir!=temp)
        {
            if(temp!=NULL) temp = pai(raiz,temp->id);
        }
        return temp;
    }else if (pa->dir==atual)//se todo o resto for falso estamos na direita do pai. portanto o pai é o nosso predecessor
    {
        return pa;
    }
    
}
no_t* sucessor(no_t*raiz,int chave){//processo reverso da função acima
    if(raiz==NULL) return NULL;
    no_t* atual = busca(raiz,chave);
    if(atual==NULL) return NULL;
    no_t* pa = pai(raiz,atual->id);
    if (atual->dir!=NULL)
    {
        no_t* temp=atual->dir;
        while (temp->esq!=NULL)
        {
            temp = temp->esq;
        }
        return temp;
    }
    else if (pa->dir!=NULL&&pa->dir==atual)
    {
        no_t* temp = pa;
        while (temp!=NULL&&pai(raiz,temp->id)->esq!=temp)
        {
            if(temp!=NULL) temp = pai(raiz,temp->id);
        }
        return temp;
    }else if (pa->esq==atual)
    {
        return pa;
    }
    
    
    
}