#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hash.h"
#define BUFFER 25

struct no
{
    int key;//chave gerada pela soma
    char* nome;
    int sond;//sondagem linear caso necessário
};
struct lista
{
    int tam;//tamanho do vetor
    no_t* vetor;
};


lis_t* ini(int tam){
    lis_t* l = malloc(sizeof(lis_t));
    l->vetor=(no_t*)malloc(tam*sizeof(no_t));
    l->tam=tam;
    return l;
}
no_t* read_line(){//nesse readline pegamos direto a key do char* e malocamos espaço para o char* em cada NO
    int pos=0;
    char letra;
    no_t* aluno=malloc(sizeof(no_t));
    aluno->nome = malloc(BUFFER*sizeof(char));
    aluno->key=0;
    do
    {
        letra = getchar();
        if (letra!='\r'&&letra!='\n'&&letra!=EOF)
        {
            aluno->nome[pos]=letra;
            aluno->key+=letra;
            pos++;
        }
        
    } while (letra!='\n'&&letra!=EOF);
    aluno->nome[pos]='\0';
    aluno->sond=0;
    return aluno;
    
}
int get_hash(int key,int tam,int i){
    int pos = (key + i) % tam;
    return pos;
}
void al(no_t aluno,lis_t* l){
    int pos = get_hash(aluno.key,l->tam,aluno.sond);
    if (l->vetor[pos].nome==NULL)
    {
        l->vetor[pos]=aluno;//espaço vago!
    }else
    {
        aluno.sond++;//sondagem linear
        al(aluno,l);
    }
    
}
void ar(no_t aluno,lis_t* l){
    int pos = get_hash(aluno.key,l->tam,aluno.sond);
    if (l->vetor[pos].nome==NULL)
    {
        aluno.sond++;//movemos para a próxima pois este está vago
        ar(aluno,l);
    }else if (strcmp(l->vetor[pos].nome,aluno.nome)==0)
    {//achamos o aluno que se retirou
        l->vetor[pos].nome=NULL;
        l->vetor[pos].key=0;
        l->vetor[pos].sond=0;
        return;
    }else
    {
        aluno.sond++;//movemos para a próxima pois este está ocupado por outro aluno
        ar(aluno,l);
    }
    
    
    
}
int as(no_t aluno,lis_t* l,int count){
    if (count == l->tam-1)
    {
        return -1;//rodamos o vetor inteiro e não achamos
    }
    
    int pos = get_hash(aluno.key,l->tam,aluno.sond);
    if (l->vetor[pos].nome==NULL)
    {
        aluno.sond++;//movemos para a próxima pois este está vago
        count++;
        as(aluno,l,count);
    }else if (strcmp(l->vetor[pos].nome,aluno.nome)==0)
    {
        return pos;
    }else
    {
        count++;//movemos para a próxima pois este está ocupado por outro aluno
        aluno.sond++;
        as(aluno,l,count);
    }
    
    
    
}
void remover(lis_t* l){
    no_t* aluno = read_line();
    ar(*aluno,l);
}
void add_aluno(lis_t* l){
    no_t* aluno = read_line();
    al(*aluno,l);
}
void search(lis_t* l){
    no_t* aluno = read_line();
    int pos = as(*aluno,l,0);
    if (pos==-1)
    {
        printf("%s nao esta presente\n",aluno->nome);
    }else
    {
        printf("%s esta presente no lugar %d\n",aluno->nome,pos);
    }
    
}
void printar(lis_t* l){
    for (int i = 0; i < l->tam; i++)
    {
        if (l->vetor[i].nome==NULL)
        {
            printf("%d: XXXX\n",i);
        }else
        {
            printf("%d: %s\n",i,l->vetor[i].nome);
        }

        
    }
    
}