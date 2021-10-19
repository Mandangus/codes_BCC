#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bigint.h"

int main(){
    int n=1,j;
    scanf("%d",&j);
    getchar();
    while (n!=j+1)
    {
        char* entry;//comando de entrada
        entry=read_line();
        int key = comando(entry);//identifica o comando
        lista_t *num1,*num2;
        num1=ini();//inicializando os 2 números
        num2=ini();
        char* aux=read_line();//lendo os números da entrada padrão
        big_int(num1,aux);//colocando cada digito na lista
        aux=read_line();
        big_int(num2,aux);
        switch (key)
        {
            case 1:
                printf("Resultado %d: ",n);
                sum(num1,num2);
                break;
            case 2:
                printf("Resultado %d: %d\n",n,big(num1,num2));
                break;
            case 3:
                printf("Resultado %d: %d\n",n,sml(num1,num2));
                break;
            case 4:
                printf("Resultado %d: %d\n",n,eql(num1,num2));
                break;
        }
        n++;
    }
}