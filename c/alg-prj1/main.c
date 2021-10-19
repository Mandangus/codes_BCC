#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"dic.h"

int main(){
    slist_t* dicionario;
    dicionario = initialize(4);
    int key;
    char letra,*entry,*termo;
    while (!feof(stdin))
    {
        
        entry=read_line(1);
        int sw = read_entry(entry); 
        switch (sw)
        {
            case 1:
                termo=read_line(1);
                key=termo[0];
                insert(dicionario,key,termo);
                break;
            case 2:
                termo=read_line(1);
                retirar(dicionario,key,termo);
                break;
            case 3:
                termo=read_line(1);
                no_t*atual=busca(dicionario,termo);
                if (atual==0)
                {
                    break;
                }
                
                printar(atual);
                break;
            case 4:
                scanf("%c",&letra);
                getchar();
                imprime(dicionario,letra);
                break;
            case 5:
                termo=read_line(1);
                altera(dicionario,termo);
                break;
            }
    }
    destroy(dicionario);
}