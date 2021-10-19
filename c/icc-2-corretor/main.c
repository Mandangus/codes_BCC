#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"spell.h"

int main(){
    FILE *fp_txt,*fp_json;
    //lendo os filenames
    char* txtname = read_line(stdin);
    char* jsonname = read_line(stdin);
    //abrindo...
    fp_txt = fopen(txtname,"r");
    fp_json = fopen(jsonname,"r");
    //checando para erros de abertura
    if (fp_txt==NULL) printf("ERRO txt não identificado!\n");
    if (fp_json==NULL) printf("ERRO json não identificado!\n");


    //inicializando uma lista
    lis_t* livro = initialize();
    //vamos dar parse no txt!
    parse_txt(fp_txt,livro);
    






    //lendo o tweet...
    char* tweet = tweet_txt(fp_json);
    do
    {
        //tweet_txt funciona como um strtok em que retorna NULL se n tem mais oq fazer
        if (tweet==NULL)
        {
            printf("No tweets to check\n");
        }else
        {
            //vamo dar parse no tweet usando strtok!
            parse_tweet(tweet,livro);
        }
        
        

        tweet = tweet_txt(fp_json);
    } while (tweet!=NULL);
    
    



}