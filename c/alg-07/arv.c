#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arv.h"
struct no
{
    int id;
    int grau;
    int altura;
    int tipo;//se tipo 1 -> raiz, se tipo 2 -> interno, se tipo 3 -> folha
    no_t *esq,*dir;
};

arv_t* initialize(){
    arv_t* arvore=(arv_t*)malloc(sizeof(arv_t));
    arvore->raiz=NULL;
    return arvore;//inicializando a raiz como NULL para lidar com situações tipo pai(arvore->raiz)
}
no_t* pai(no_t* raiz,int id){
    if (raiz==NULL)
    {
        return NULL;
    }
    
    if (raiz->esq!=NULL&&raiz->esq->id==id)
    {
        return raiz;//se o elemento a esquerda tiver o id do filho que buscamos achamos o pai
    }
    if (raiz->dir!=NULL&&raiz->dir->id==id)
    {
        return raiz;//se o elemento a direita tiver o id do filho que buscamos achamos o pai
    }
    no_t* p = pai(raiz->esq,id);//mesmo processo da busca...
    if (p==NULL)
    {
        p=pai(raiz->dir,id);
    }
    return p;
    
}
no_t*busca(no_t*raiz,int id){
    if (raiz==NULL)
    {
        return NULL;
    }
    if (raiz->id==id)
    {
        return raiz;
    }
    no_t*p=busca(raiz->esq,id);//caminhamos recursivamente pela arvore checando os filhos da esquerda depois da direita
    if (p==NULL)
    {
        p=busca(raiz->dir,id);
    }
    
    return p;
}
int altura(no_t* raiz){
    if (raiz==NULL)
    {
        return 0;
    }
    //vamos até o topo da árvore e depois subimos contando a altura
    //a altura do nó será o máximo das duas!
    int he = 1 + altura(raiz->esq);
    int hd = 1 + altura(raiz->dir);
    if (he>=hd)
    {
        return he;
    }else
    {
        return hd;
    }
    
    
}
void printar(no_t* raiz,arv_t*arvore){
    if (raiz!=NULL&&raiz->id!=-1)
    {
        //arrumando o grau...
        if (raiz->esq!=NULL&&raiz->esq->id!=-1)
        {
            raiz->grau++;
        }
        if (raiz->dir!=NULL&&raiz->dir->id!=-1)
        {
            raiz->grau++;
        }
        //estabelecendo a altura...
        raiz->altura=altura(raiz)-1;
        //checando o pai de cada nó 
        no_t* aux = pai(arvore->raiz,raiz->id);
        if (aux==NULL)
        {
            //caso seja a raiz
            raiz->tipo=1;
        }
        else
        {
            if (raiz->esq->id==-1&&raiz->dir->id==-1)
            {
                //caso seja uma folha
                raiz->tipo=3;
            }else
            {
                //caso seja um interno
                raiz->tipo=2;
            }
        }
        switch (raiz->tipo)
        {
        case 1:
            printf("no %d: pai = -1, altura = %d, grau = %d, filhos = (%d,%d), tipo = raiz\n",raiz->id,raiz->altura,raiz->grau,raiz->esq->id,raiz->dir->id);
            break;
        case 2:
            printf("no %d: pai = %d, altura = %d, grau = %d, filhos = (%d,%d), tipo = interno\n",raiz->id,aux->id,raiz->altura,raiz->grau,raiz->esq->id,raiz->dir->id);
            break;
        case 3:
            printf("no %d: pai = %d, altura = %d, grau = %d, filhos = (-1,-1), tipo = folha\n",raiz->id,aux->id,raiz->altura,raiz->grau);
            break;
        default:
            break;
        }
        printar(raiz->esq,arvore);
        printar(raiz->dir,arvore);
    }
    
}
void insert_esq(arv_t*arvore,int id,int paid){
    no_t*p=(no_t*)malloc(sizeof(no_t));
    p->esq=NULL;
    p->dir=NULL;
    p->id=id;
    p->grau=0;
    if (paid==-1)
    {
        if (arvore->raiz == NULL)
        {
            //é a raíz!
            arvore->raiz = p;
        }else
        {
            free(p);
            return;
        }
    }else
    {
        //buscando o pai...
        no_t* aux = busca(arvore->raiz,paid);
        if (aux!=NULL&&aux->esq==NULL)
        {
            //o pai não é NULL e a esquerda está vaga!
            aux->esq=p;
        }else
        {
            free(p);
            return;
        }
        
        
    }
    return;
    
}
void insert_dir(arv_t*arvore,int id,int paid){
    no_t*p=(no_t*)malloc(sizeof(no_t));
    p->esq=NULL;//iniciaizando as variáveis da estrutura
    p->dir=NULL;
    p->id=id;
    p->grau=0;
    if (paid==-1)
    {
        if (arvore->raiz == NULL)
        {
            //é a raíz!
            arvore->raiz = p;
        }else
        {
            free(p);
            return;
        }
    }else
    {
        no_t* aux = busca(arvore->raiz,paid);
        if (aux!=NULL&&aux->dir==NULL)
        {
            //direita está vaga e o pai não é NULL
            aux->dir=p;
        }else
        {
            free(p);
            return;
        }
        
        
    }
    return;
}
void montar(arv_t* arvore,int n){
    do
    {
        int id,id_esq,id_dir;//pegando os id's ....
        scanf("%d %d %d",&id,&id_esq,&id_dir);
        getchar();
        no_t* aux = pai(arvore->raiz,id);
        if (aux==NULL)
        {//se ñ tiver pai é a raíz!
            insert_esq(arvore,id,-1);
        }else if (aux->esq==NULL)
        {
            //primeiro vemos se a esquerda está vaga
            insert_esq(arvore,id,aux->id);
        }else
        {
            //sobrou a direita!
            insert_dir(arvore,id,aux->id);   
        }
        insert_esq(arvore,id_esq,id);
        insert_dir(arvore,id_dir,id);
        n--;
    } while (n>0);
    printar(arvore->raiz,arvore);
}