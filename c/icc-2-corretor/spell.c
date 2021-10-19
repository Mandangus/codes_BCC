#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"spell.h"
#include<ctype.h>
struct list
{
    int tam;
    char**elem;
};
//inicializando a lista alocando os vetor de strings e setando o tamanho...
lis_t* initialize(){
    lis_t* lista = (lis_t*)malloc(sizeof(lis_t));
    lista->tam = 0;
    lista->elem = (char**)malloc(sizeof(char*));
    return lista;
}
//read_line básico
char* read_line(FILE*stream){
    char* pal = (char*)malloc(BUFFER*sizeof(char));
    char letra;
    int pos = 0;
    do
    {
        letra = getc(stream);
        if (letra!='\n'&&letra!='\r'&&letra!=EOF)
        {
            pal[pos]=letra;
            pos++;
        }
    } while (letra!='\n'&&letra!=EOF);
    pal[pos]='\0';
    return pal;
}
//aqui (similar ao read_line) buscamos o char " para que possamos achar o campo "text"
char* read_json(FILE*stream){
    char* pal = (char*)malloc(1024*sizeof(char));
    char letra;
    int pos = 0;
    do
    {
        letra = getc(stream);
        if (letra=='\"')
        {
            do
            {
                letra=getc(stream);
                if(letra!='\"'){
                    pal[pos]=letra; 
                    pos++;
                }

            } while (letra!='\"');
            pal[pos]='\0';
            return pal;
        }
        
    }while (!feof(stream));
    //não achamos text! portanto não há tweets para ler
    return NULL;
}
int busca(char**elem,int max,char*procura){
    //binary search básico só que sem recursão e com strcmp
    int esq = 0;
    int dir = max - 1;
    while (esq<=dir)
    {
        int meio = esq + (dir-esq) / 2;
        int indice = 0;
        if (strcmp(procura,elem[meio])==0) return meio;
        if (strcmp(procura,elem[meio])>0) esq = meio + 1;
        if (strcmp(procura,elem[meio])<0) dir = meio - 1;
    }
    //não achou!
    return -1;
    
}
char* read_txt(FILE*stream){
    int pos = 0;
    char letra;
    char* pal = malloc(BUFFER*sizeof(char));
    letra = getc(stream);
    do
    {
        //aqui tiramos todos o chars inválidos para nossa database!
        if (letra!='.'&&letra!=','&&letra!=';'&&letra!=':'&&letra!=')'&&letra!='('&&letra!='!'&&letra!='?'&&letra!='\"'&&letra!='\n'&&letra!='&'&&letra!='\''&&letra!=' '&&letra!='@'&&letra!='-'&&letra!='#'&&letra!='\r'&&letra!=EOF){
            //colocamos tudo lowercase!
            letra = tolower(letra);
            pal[pos] = letra;
            pos++; 
        }else
        {
            break;
        }
        

        letra = getc(stream);
    } while (letra!=EOF);
    pal[pos]='\0';
    return pal;
}
char* tweet_txt(FILE* fp){
    char* text = NULL;
    do
    {
        //como o json é estruturado "text": "blá blá ..." é fácil achar o texto depois de encontrar o campo "text"
        text = read_json(fp);
        if (text==NULL) return NULL;
    }while (strcmp(text,"text")!=0);
    //lendo o texto do tweet!
    text = read_json(fp);
    return text;
}
void insert(lis_t*lista,char* pal){
    //insert na lista! aumentando o tamanho e alocando mais memória
    //as palavras repetidas serão removidas em breve!
    lista->tam++;
    lista->elem=(char**)realloc(lista->elem,(lista->tam+1)*sizeof(char*));
    lista->elem[lista->tam-1]=strdup(pal);
    return;
}
void printar(lis_t*lista){
    //print da database usado para debugar
    for (int i = 0; i < lista->tam; i++)
    {
        printf("Indice: %d\tPalavra: %s\n",i,lista->elem[i]);
    }
    return;
}
//aqui eu adapto a função strcmp para poder usá-la no qsort
//o qsort pede const void* e strcmp pede const char*
//é fácil de arruamr! vamos dar uns casts em variáveis temporárias
int compare(const void*a,const void*b){
    const char** aa=(const char**)a;
    const char** bb=(const char**)b;

    return strcmp(*aa,*bb);
}
//aqui tiramos todas as entradas repetidas e colocamos tudo numvetor auxiliar que é mais eficiente em memória!
char** repetidos(lis_t*lista,int* tam){
    int i = 0,j = 0;
    char**aux=malloc(sizeof(char*));
    aux[j]=strdup(lista->elem[i]);
    while (i<lista->tam-1)
    {
        i++;
        if(aux[j]!=NULL&&lista->elem[i]!=NULL)//se for diferente adicionamos ao vetor! e não NULL obviamente.
        {
            if (strcmp(aux[j],lista->elem[i])!=0)
            {
                j++;
                aux = (char**)realloc(aux,(j+1)*sizeof(char*));
                aux[j]=strdup(lista->elem[i]);
            }
        }
    }
    *tam = j;
    return aux;
}
void parse_txt(FILE *fp,lis_t* lista){
    char* pal = NULL;
    do
    {
        pal = read_txt(fp);

        if(pal!=NULL&&strcmp(pal,"")!=0) insert(lista,pal);//se a palavra não for vazia e NULL damos insert
        free(pal);
    } while (!feof(fp));
    qsort(lista->elem,lista->tam,sizeof(BUFFER*sizeof(char*)),compare);//qsort com o strcmp adaptado!
    int tam_aux;//o tamanho da vetor sem repetições vai ser menor!
    lista->elem=repetidos(lista,&tam_aux);//tiramos os repetidos e pegamos o novo tamanho!
    lista->tam = tam_aux+1;
    //printar(lista); era usado para debugar!
    return;
}

void parse_tweet(char* tweet,lis_t* lista){
    //aqui usamos strtok afinal temos diversos chars proibídos!
    char* aux = strtok(tweet," .,-\'#…!()&�@’”\"“—0123456789:?");
    char* lower = strdup(aux);//temos que transformar em lower case para comparar com a database
    for (int i = 0; i < strlen(lower); i++)
    {
        lower[i]=tolower(lower[i]);
    }
    
    do
    {
        lower = strdup(aux);
        for (int i = 0; i < strlen(lower); i++)
        {
            lower[i]=tolower(lower[i]);
        }
        if (strcmp(aux,"")!=0)//se não é vazio...
        {
            int x = busca(lista->elem,lista->tam,lower);//buscamos o lowercase
            if(x==-1)
            { 
                printf("%s ",aux);//caso -1 significa que não achamos no binary sort então printamos 
            }
        }
        aux = strtok(NULL," .,-\'#…!()&�@’”\"“—0123456789:?");
    } while(aux!=NULL);
    printf("\n");//passamos de linha...
}