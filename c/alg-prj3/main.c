#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"treap.h"



int main(){
    int chave, prio;
    int n,count = 0;
    int temp;
    scanf("%d\n",&n);
    no_t* raiz = NULL;
    char* aux;
    do
    {
        char* entry = read_line();
        //printf("%s\n",entry);
        int sw = comando(entry);
        switch (sw)
        {
        case 0://insert
            scanf("%d %d\n",&chave,&prio);
            if(busca(raiz,chave)==0)
            {
                insert(raiz,chave,prio);
                update(raiz);
            }else
            {
                printf("Elemento ja existente\n");
            }
            break;
        case 1://remocao
            scanf("%d\n",&chave);
            if(busca(raiz,chave)==0)
            {
                printf("Chave nao localizada\n");
            }else
            {
                //raiz = remover(raiz,chave);
            }
            break;
        case 2://impressao
           /* aux = read_line();
            temp = comando_printf(aux);
            if(temp==1)printar(raiz);//ordem
            else if(temp==2)printar_pos(raiz);//posordem
            else if(temp==3)printar(raiz);//preordem
            else printar_larg(raiz);//largura*/
            break;
        case 3://busca
            scanf("%d\n",&chave);
            printf("%d\n",busca(raiz,chave));
            break;
        default:
            printf("COMANDO NAO ENCONTRADO!\n");
            return 1;
            break;
        }
        count++;
    } while (count<n-1);
    return 0;
}