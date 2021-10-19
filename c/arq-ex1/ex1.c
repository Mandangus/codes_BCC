#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024


void tockenizar(char* linha,int*id,char*nome,int*idade){
    int pos = 0 ,i = 0;
    //separando o ID//////////////////////////////////////
    char aux[50];
    while(linha[pos]!=','&&linha[pos]!='\n')
    {
        aux[i]=linha[pos];
        pos++; i++;
    }
    *id=atoi(aux);//atoi para pegar a int
    pos++; i=0;
    ////// separando o nome////////////////////////////////
    char aux1[50];
    while(linha[pos]!=','&&linha[pos]!='\n')
    {
        aux1[i]=linha[pos];
        pos++; i++;
    }
    aux1[i]='\0';//finalizamos a string...
    strcpy(nome,aux1);
    pos++; i=0;
    /////// separando a idade//////////////////////////////
    char aux2[50];
    while(linha[pos]!=','&&linha[pos]!='\0'&&linha[pos]!='\n')
    {
        aux2[i]=linha[pos];
        pos++; i++;
    }
    *idade=atoi(aux2);
    pos++; i=0;
    //aqui imprimimos os registros elegiveis
    if (*idade>=18)
    {
        if (nome[0]=='\0')
        {
            printf("O usuario de identificacao %d eh de maior.\n",*id);
        }else
        {
            printf("O usuario %s eh de maior.\n",nome);
        }
        
    }
    
    return;
}
int lerLinha(FILE* fp,int*id,char*nome,int*idade){
    char lido;
    int pos=0;
    char* linha = (char*)malloc(sizeof(char)*BUFFER);
    while(lido!='\n'&&lido!=EOF)
    {
        if (fread(&lido,sizeof(char),1,fp)==0) return 1;//reconhecendo o fim do arquivo sem feof
        linha[pos]=lido;
        pos++;
    }
    linha[pos-1]='\0';
    tockenizar(linha,id,nome,idade);//vamos separar cada parte da str pelo divisor ','
    return 0;
    
}

int main(int argc,char* argv[]){
    char filename[20];//pegamos o nome do arquivo
    scanf("%s",filename);
    FILE *fp=fopen(filename,"r");
    if (fp==NULL) printf("Erro ao ler arquivo!\n");//tratamos um possivel erro...
    int linecounter = 0,fim=0;
    //contador de linhas para ignorar os rotulos e int fim para registrar o fim do arquivo
    do{
        int idade,id;
        char* nome = (char*)malloc(BUFFER*sizeof(char));
        if (linecounter!=0)
        {
            fim = lerLinha(fp,&id,nome,&idade);
        }
        linecounter++;
    }while(fim!=1);



    return 0;
}