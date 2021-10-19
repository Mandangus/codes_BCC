#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 256


void permutar(char**regras,char**palavras,int count,int re,int pal,int*tamdig,int*tamrule,int*pos){
    
    if (count==tamdig[re])
    {
        for (int i = 0,n = 0; i < tamrule[re]; i++)
        {
            if(regras[re][i]=='0'){ 
                printf("%d",pos[n++]);
            }
            else {
                printf("%s",palavras[pal]);
            }
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < 10; i++)
    {
        pos[count]=i;
        permutar(regras,palavras,count+1,re,pal,tamdig,tamrule,pos);
    }
    
    
    
}




int main(){

    char c = -1;
    c = getc(stdin);
    int pos[1024];
    while (c != EOF)
    {
        int num_palavras = atoi(&c);
        char** words = (char**)malloc(num_palavras*sizeof(char*));
        for (int i = 0; i < num_palavras; i++)
        {
            words[i] = (char*)malloc(MAXSIZE*sizeof(char));
            scanf("%s",words[i]);
        }
        int num_regras;
        scanf("%d",&num_regras);
        char** rules = (char**)malloc(num_palavras*sizeof(char*));
        int dig_rules[num_regras],tam_rules[num_regras];
        for (int i = 0; i < num_regras; i++)
        {
            rules[i] = (char*)malloc(MAXSIZE*sizeof(char));
            scanf("%s",rules[i]);
            int digits = 0;
            for (int j = 0; rules[i][j]!='\0'; j++)
            {
                if(rules[i][j]=='0') digits++;
            }
            dig_rules[i] = digits;
            tam_rules[i] = strlen(rules[i]);
        }
        
        printf("--\n");
        for (int i = 0; i < num_palavras; i++)
        {
            for (int j = 0; j < num_regras; j++)
            {
                permutar(rules,words,0,j,i,dig_rules,tam_rules,pos);
            }
            
        }
        
        
        getchar();
        c = getc(stdin);
    }
    



    return 0;
}