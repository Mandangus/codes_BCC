#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arv.h"


int main(){
    int n;
    arv_t* arvore;
    arvore = initialize();
    scanf("%d",&n);
    getchar();
    montar(arvore,n);
    return 0;
}