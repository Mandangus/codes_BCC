#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"treap.h"

struct no
{
    no_t *esq,*dir;
    int chave, prio;
};

int main(){
    int chave, prio;
    int n,count = 0;
    int temp;
    scanf("%d\n",&n);
    no_t* raiz = NULL;
    no_t* temp1=NULL;
    char* aux;
    do
    {
        char* entry = read_line();//lendo o comando
        int sw = comando(entry);//usando a funcao para usar um switch
        switch (sw)
        {
        case 0://insert
            scanf("%d %d\n",&chave,&prio);
            if(busca(raiz,chave)==NULL)//se não existe insere caso contrário printa uma mensagem
            {
                raiz=insert(raiz,chave,prio);
            }else
            {
                printf("Elemento ja existente\n");
            }
            break;
        case 1://remocao
            scanf("%d\n",&chave);//se não existe printa uma mensagem, se existe remove
            if(busca(raiz,chave)==NULL)
            {
                printf("Chave nao localizada\n");
            }else
            {
                raiz = remover(raiz,chave);
            }
            break;
        case 2://impressao
            aux = read_line();
            temp = comando_printf(aux);
            if(temp==0)printord(raiz);//ordem
            else if(temp==1)printposord(raiz);//posordem
            else if(temp==2)printpre(raiz);//preordem
            else 
            {
                fila_t* fi = initialize();//inicializa uma lista auxiliar
                printar_larg(raiz,fi);//largura
                free(fi);//libera a lista
            }
            printf("\n");
            break;
        case 3://busca
            scanf("%d\n",&chave);
            temp1 = busca(raiz,chave);
            if(temp1==NULL)
            {
                printf("0\n");
                break;
            }
            printf("1\n");
            break;
        default:
            printf("COMANDO NAO ENCONTRADO!\n");
            return 1;
            break;
        }
        count++;
    } while (count<n);
    return 0;
}