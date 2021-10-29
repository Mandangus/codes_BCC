#include <iostream>
#include <cstdio>
#include <cstring>

//problema 10465 de programação dinâmica
#define MAX 20001
using namespace std;

int n,m;
int memo[MAX];
bool possivel[MAX];




void setPossivel(int tempoTotal,int tempoAcumulado){
    if(tempoAcumulado>tempoTotal) return;// acabou o tempo!
    if(possivel[tempoAcumulado]) return;// voltamos para um já visitado!
    possivel[tempoAcumulado] = true;// visitamos o possivel
    setPossivel(tempoTotal,tempoAcumulado + m);// vamos comer um krusty
    setPossivel(tempoTotal,tempoAcumulado + n);// vamos comer um apul
}



int solveDP(int t){// iterativamente
    memo[0] = 0;
    int deltaMin = t - min(m, n);
    int top = 1000;//valor setado no memset
    for (int i = 0; i <= deltaMin; i++)// bottom-up
    {
        if (memo[i]!=top)//existe na memória?
        {
            memo[i + m] = max(memo[i + m],memo[i] + 1);//escolhi o hamburguer do krusty?
            memo[i + n] = max(memo[i + n],memo[i] + 1);//escolhi o hamburguer do apul?
        }
    }
    int deltaBreja = t;
    while (memo[deltaBreja] == top) deltaBreja--;//o homer irá beber cerveja? se sim decrementa

    return memo[deltaBreja];
    
    

}


int main(){
    int t;
    while (cin >> m)
    {
        cin >> n >> t;
        
        memset(memo,1000,sizeof(memo));// o memset não será -1 pois vamos fazer bottom-up!
        memset(possivel,false,sizeof(possivel));
        setPossivel(t,0);//vamos achar as combinações possíveis dado o tempo t

        if(possivel[t]==false){// sabemos que não é possível só comer nesse tempo! precisamos beber
            int i;
            for (i = t; i >= 0; i--) {if(possivel[i]) break;};//vamos achar o indice de maior tempo de hamburguer possivel! 
            int result = solveDP(i);
            printf("%d %d\n",result,t-i);

        }else printf("%d\n",solveDP(t));//caso contrario so sera comer
        
    }
    



    return 0;
}