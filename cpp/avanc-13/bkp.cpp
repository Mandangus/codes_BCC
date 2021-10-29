#include <iostream>
#include <cstdio>
#include <cstring>
#define INF 0x3f3f3f

//problema 10465 de programação dinâmica
#define MAX 10005

using namespace std;

int n,m,t;
int memo[MAX];
bool possivel[MAX];
bool caminho[MAX];



void setPossivel(int tempoAcumulado){//testando as possiveis combinações

    if(tempoAcumulado>t) return;// acabou o tempo!
    if(possivel[tempoAcumulado]) return;// voltamos para um já visitado!

    possivel[tempoAcumulado] = true;// visitamos o possivel
    setPossivel(tempoAcumulado + m);// vamos comer um krusty
    setPossivel(tempoAcumulado + n);// vamos comer um apul

}



int solveDP(int tempoIdeal){// recursivamente top-down...
    
    if(tempoIdeal < 0) return -INF;
    if(tempoIdeal == 0) return 0;

    int &melhor = memo[tempoIdeal];
    if(caminho[tempoIdeal]) return melhor;// caso ja exista na memo
    
    caminho[tempoIdeal] = true;// visitamos na memo

    return melhor = max(solveDP(tempoIdeal-n),solveDP(tempoIdeal-m))+1;// rumamos para baixo decrementando krusty ou apul

}


int main(){
    while (cin >> n)
    {
        cin >> m >> t;
        memset(memo,-1,sizeof(memo));// o memset será -1 pois vamos fazer top-down!
        memset(possivel,false,sizeof(possivel));
        memset(caminho,false,sizeof(caminho));
        setPossivel(0);//vamos achar as combinações possíveis dado o tempo t

        if(!possivel[t]){// sabemos que não é possível só comer nesse tempo! precisamos beber
            for (int i = t; i >= 0; i--) {
                if(possivel[i]){
                    printf("%d %d\n",solveDP(i),(t-i));
                    break;
                }
            };//vamos achar o indice de maior tempo de hamburguer possivel! 

        }else printf("%d\n",solveDP(t));// caso contrário só vamos comer!!
        
    }
    



    return 0;
}