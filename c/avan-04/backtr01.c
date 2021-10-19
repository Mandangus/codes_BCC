#include<stdio.h>
#include<stdlib.h>


void printTabuleiro(int**tabuleiro){//função usada para debugar algumas teorias...
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d ",tabuleiro[i][j]);
        }
        printf("\n");
    }
    
}

int colocar(int posy,int posx,int*posRainha){//tenta achar a melhor rainha válida em uma linha
    for (int i = 0; i < posy; i++)
    {
        if (posRainha[i] == posx || (abs(posRainha[i]-posx) == abs(i - posy)))//é válido?
        {
            return 0;//não 
        }
        
    }
    return 1;
}

int calcTotal(int**tabuleiro,int*posRainha){
    int soma = 0;
    for (int i = 0; i < 8; i++)
    {
        //               que linha está a rainha
        //                      |
        //                      V 
        soma += tabuleiro[posRainha[i]][i];
    }
    

    return soma;
}


void backtrack(int**tabuleiro,int*posRainha,int*res,int cont){// tabuleiro / posição das rainhas por linha / resposta do exercicio / contador da recursão
    if (cont == 8)//chegou no final
    {
        int total = calcTotal(tabuleiro,posRainha);
        if (total > *res)//se esse caminho valer mais que o anterior mais valioso...
        {
            *res = total;
        }
        
    }
    
    for (int i = 0; i < 8; i++)
    {
        if (colocar(cont,i,posRainha))//se der pra colocar
        {
            posRainha[cont] = i;
            backtrack(tabuleiro,posRainha,res,cont+1);//proxima posição
        }
        
    }
    


    
}

int main(){
    int k = 0;
    scanf("%d",&k);
    for (int i = 0; i < k; i++)
    {
        int* posRainha = (int*)calloc(8,sizeof(int));//indo linha por linha qual a posição da melhor rainha valida
        int** tabuleiro = (int**)malloc(8*sizeof(int*));
        for (int j = 0; j < 8; j++) tabuleiro[j] = (int*)calloc(8,sizeof(int));
        
        for (int j = 0; j < 8; j++)
        {
            for (int l = 0; l < 8; l++)
            {
                scanf("%d",&tabuleiro[j][l]);
            }
            getchar();
        }
        int res = -10000000;//numero bem baixo para trocar com a resposta
        backtrack(tabuleiro,posRainha,&res,0);//vamos recursivamente testar todas as possibilidades e ficar com a melhor
        printf("%5d\n",res);


        free(posRainha);
        for (int i = 0; i < 8; i++) free(tabuleiro[i]);
        free(tabuleiro);
        
        

    }
    






    return 0;
}