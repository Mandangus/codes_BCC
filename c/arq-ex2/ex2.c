#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024
#define MAXSIZESTR 50


int lerLinha(FILE* fp,int*id,char*nome,int*idade){
    int pos=0; char letra; int fim =1;//setamos o fim como 1 para que se o final do arquivo fosse chegado nao aconteceria o set fim=0 no break
    fread(id,sizeof(int),1,fp);//lemos a primeira int
    while (fread(&letra,sizeof(char),1,fp)!=0)
    {
        nome[pos]=letra;
        pos++;
        if(letra=='\0')
        {
            fim = 0;//                                     <----------------------------------- aqui
            break;
        }
    }
    fseek(fp,MAXSIZESTR-pos,SEEK_CUR);//movemos o ponteiro para o final do tamanho predeterminado para a string. Vamos do atual para o maximo menos o atual
    fread(idade,sizeof(int),1,fp);
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
    return fim;
    
}


int main(int argc,char* argv[]){
    char filename[20];//pegamos o nome do arquivo
    scanf("%s",filename);
    FILE *fp=fopen(filename,"rb");
    if (fp==NULL) printf("Erro ao ler arquivo!\n");//tratamos um possivel erro...
    int linecounter = 0,fim=0;
    //contador de linhas para ignorar os rotulos e int fim para registrar o fim do arquivo
    do{
        int idade,id;
        char* nome = (char*)malloc(MAXSIZESTR*sizeof(char));
        if (linecounter!=0)
        {
            fim = lerLinha(fp,&id,nome,&idade);
        }
        linecounter++;
    }while(fim!=1);



    return 0;
}