#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bigint.h"

struct no
{
    int cont;
};

struct lista
{
    int tam;
    int sinal;
    no_t *num;
};

lista_t* ini(){
    lista_t* l=(lista_t*)malloc(sizeof(lista_t));
    l->num=NULL;
    l->tam=0;
    return l;
}
int min(int a,int b){
    if (b<a)
    {
        return b;
    }else
    {
        return a;
    }
}
char* read_line(){
    //read_line básico
    int pos=0;
    char letra;
    int flag=0;
    char* palavra=(char*)malloc(BUFFER*sizeof(char));
    do
    {
        letra=getchar();
        if (letra!=48)//retira-se (caso houver) qualquer zero a esquerda
        {
            flag=1;
        }
        
        if (letra!=' '&&letra!='\n'&&flag==1)
        {
            palavra[pos]=letra;
            pos++;
        }
        
    } while (letra!=' '&&letra!='\n');
    palavra[pos]='\0';
    return palavra;
}
int comando(char* entry){
    //achando o comando correto
    char comandos[4][4]={"sum","big","sml","eql"};
    int key=0;
    if (strcmp(entry,comandos[0])==0)
    {
        key=1;
        return key;
    }
    if (strcmp(entry,comandos[1])==0)
    {
        key=2;
        return key;
    }
    if (strcmp(entry,comandos[2])==0)
    {
        key=3;
        return key;
    }
    if (strcmp(entry,comandos[3])==0)
    {
        key=4;
        return key;
    }
    printf("ERRO comando não identificado!\n");
}
void big_int(lista_t*l,char*num){
    //aqui designamos cada char para cada nó da lista
    int len=strlen(num);
    l->num=(no_t*)malloc(sizeof(no_t));
    int pos=0;
    if (num[0]=='-')
    {//se for negativo
        l->sinal=1;
        pos=1;
    }else
    {//se for positivo
        l->sinal=0;
    }
    
    while (l->tam!=len)
    {//-48 para designar o char como int do número correspondente
        l->num[l->tam].cont=num[pos]-48;
        l->num=(no_t*)realloc(l->num,(l->tam+BUFFER)*sizeof(no_t));
        l->tam++;
        pos++;
    }
    if (l->sinal==1)
    {
        //removendo uma casa extra do sinal
        l->tam--;
    }
    
}
void printar(lista_t* l){
    //print das listas
    if (l->sinal==1)
    {
        printf("-");
    }
    for (int i = 0; i < l->tam; i++)
    {
        printf("%d",l->num[i].cont);
    }
    printf("\n");
}
int sml(lista_t*num1,lista_t*num2){
    //mesmo processo do big() só que com os returns invertidos
    int len1=num1->tam;
    int len2=num2->tam;
    
    int flag1=0,flag2=0;
    if (num1->sinal==1)
    {
        flag1=1;
        if (num2->sinal==0)
        {
            return 1;
        }
        
    }
    if (num2->sinal==1)
    {
        flag2=1;
        if (num1->sinal==0)
        {
            return 0;
        }
        
    }
    int i=0,k=0;
    if (flag1==0)
    {
        if (len1<len2)
        {
            return 1;
        }
        if (len2<len1)
        {
            return 0;
        }
        
    }
    if (flag1==1)
    {
        if (len1<len2)
        {
            return 0;
        }
        if (len2<len1)
        {
            return 1;
        }
          
    }
    while (i<len1||k<len2)
    {
        if (num1->num[i].cont<num2->num[k].cont)
        {
            if (flag1==0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        if (num1->num[i].cont>num2->num[k].cont)
        {
            if (flag1==0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        i++;
        k++;
    }
    
    return 0;
    
}
lista_t* sum(lista_t* num1,lista_t* num2){
    lista_t*aux=ini();
    int flag=0;
    //pegando o maior tamanho dos dois números e somo 1 para que não haja espaços não alocados
    if (num1->tam>num2->tam)
    {
        aux->tam=num1->tam+1;
    }else
    {
        aux->tam=num2->tam+1;
    }
    //dou um calloc para depois remover os 0's a esquerda facilmente
    aux->num=(no_t*)calloc(aux->tam,sizeof(no_t));
    //temos um carry e um indice para o tamanho de cada número -1
    int carry=0,k=1,n=num1->tam-1,j=num2->tam-1,i=aux->tam-1;
    while (n!=-1&&j!=-1)
    {
        aux->num[i].cont=(num1->num[n].cont+num2->num[j].cont+carry)%10;//achamos o valor...
        carry=(num1->num[n].cont+num2->num[j].cont+carry)/10;//achamos o carry...
        i--,j--,n--;
    }
    if (n==-1&&j!=-1)
    {//o num1 acabou. agora é só o carry e o num2
        for (int y = i; y > 0; y--)
        {
            aux->num[y].cont=(num2->num[y].cont+carry)%10;
            carry=(num2->num[j].cont+carry)/10;
        }
        aux->num[0].cont=carry;
    }else if(j==-1&&n!=-1)//o num2 acabou. agora é só o carry e o num1
    {
        for (int y = i; y > 0; y--)
        {
            aux->num[y].cont=(num1->num[y].cont+carry)%10;
            carry=(num1->num[j].cont+carry)/10;
        }
        aux->num[0].cont=carry;
    }else
    {//acabaram ambos
        aux->num[0].cont=carry;
    }
    

    int flagzero=0;//uma flag para evitar a impressão de 0's a esquerda
    for (int l = 0; l < aux->tam; l++)
    {
        if (aux->num[l].cont!=0)
        {
            flagzero=1;
        }
        if (flagzero==1)
        {
            printf("%d",aux->num[l].cont);
        }
    }
    printf("\n");
    
}
int big(lista_t*num1,lista_t*num2){
    int len1=num1->tam;
    int len2=num2->tam;
    
    int flag1=0,flag2=0;
    //removemos de já os casos em que os sinais diferem
    if (num1->sinal==1)
    {
        flag1=1;
        if (num2->sinal==0)
        {
            return 0;
        }
        
    }
    if (num2->sinal==1)
    {
        flag2=1;
        if (num1->sinal==0)
        {
            return 1;
        }
        
    }
    int i=0,k=0;
    //removemos os casos em que o tamanho é diferente
    //se positivo
    if (flag1==0)
    {
        if (len1<len2)
        {
            return 0;
        }
        if (len2<len1)
        {
            return 1;
        }
        
    }
    //se negativo
    if (flag1==1)
    {
        if (len1<len2)
        {
            return 1;
        }
        if (len2<len1)
        {
            return 0;
        }
          
    }
    //caso os números tenham o mesmo tamanho e o mesmo sinal comparamos cada dígito
    while (i<len1||k<len2)
    {
        if (num1->num[i].cont<num2->num[k].cont)
        {
            //se positivo
            if (flag1==0)
            {
                return 0;
            }
            //se negativo
            else
            {
                return 1;
            }
        }
        if (num1->num[i].cont>num2->num[k].cont)
        {
            if (flag1==0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        i++;
        k++;
    }
    //os números são iguais
    return 0;
    
}
int eql(lista_t*num1,lista_t*num2){
    if (num1->tam!=num2->tam)
    {//se o tamanho for diferente
        return 0;
    }
    for (int i = 0; i < num1->tam; i++)
    {//comparando cada dígito
        if (num1->num[i].cont!=num2->num[i].cont)
        {
            return 0;
        }
        
    }
    return 1;//os números são iguais
}