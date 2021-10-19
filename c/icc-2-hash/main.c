#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hash.h"


int main(){
    int n,m,r,k,count = 0;
    lis_t* l;
    scanf("%d\n%d",&n,&m);
    getchar();
    l=ini(n);



    //ADICIONAR
    do
    {
        add_aluno(l);
        count++;
    } while(count<m);
    printar(l);



    //REMOVER
    count = 0;
    scanf("%d",&r);
    getchar();
    while (count<r)
    {
        remover(l);
        count++;
    }

    printf("\n");
    //BUSCAR
    count = 0;
    scanf("%d",&k);
    getchar();
    while (count<k)
    {
        search(l);
        count++;
    }
    return 0;
}