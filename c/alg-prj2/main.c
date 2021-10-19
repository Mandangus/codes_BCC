#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"llrb.h"
struct no
{
    no_t *esq,*dir;
    int cor;//se 0 preto se 1 vermelho
    int id;
};
int main(){
    no_t* temp1,*temp2;
    int n,count=0;
    int x,chave;
    no_t* raiz=NULL;
    scanf("%d\n",&n);
    do
    {
        scanf("%d",&x);
        switch (x)
        {
        case 1:
            scanf("%d\n",&chave);
            raiz=insert(raiz,chave);
            raiz->cor=0;//asseguramos que a raiz é preta
            break;
        case 2:
            scanf("%d\n",&chave);
            temp1=sucessor(raiz,chave);
            if(temp1==NULL||temp1->id==chave) printf("erro\n");
            else printf("%d\n",temp1->id);
            break;
        case 3:
            scanf("%d\n",&chave);
            temp2=predecessor(raiz,chave);
            if(temp2==NULL||temp2->id==chave) printf("erro\n");
            else printf("%d\n",temp2->id);
            break;
        case 4:
            printf("%d\n",maximo(raiz));
            break;
        case 5:
            printf("%d\n",minimo(raiz));
            break;
        case 6:
            printpre(raiz);
            printf("\n");
            break;
        case 7:
            printord(raiz);
            printf("\n");
            break;
        case 8:
            printposord(raiz);
            printf("\n");
            break;
        default:
            printf("COMANDO NAO RECONHECIDO\n");
            break;
        }
        count++;
    } while (count<n);
    
}