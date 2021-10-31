#include <bits/stdc++.h>

#define MAXSIZE 1000021


//Problema de DP 10404

using namespace std;


int n;
int m;


bool checkPoss(vector<int> vect){//checa todos as possíveis comb. e retorna quem ganhou

    bool memo[n+1];
    memset(memo,false,n+1);
    for (int i = 1; i <= n; i++)
    {
        for (auto &&escolha : vect)
        {
            if(i - escolha >= 0 && !memo[i-escolha]){//checa se pode retirar a pedra e se ja não foi computado...
                memo[i] = true; // marca como calculada determinada posição
                break;// quebra do laço pois achou a escolha válida
            }
        }
        
    }
    return memo[n];//retorna a possivel jogada final, que, se ocorrida significa a vitoria de Stan!!
}


int main(void){

    while (cin >> n)
    {
        cin >> m;
        vector<int> vect;
        int k;
        for (int i = 0; i < m; i++){
            cin >> k;
            vect.push_back(k);
        }
        

        if(checkPoss(vect)){
            printf("Stan wins\n");
        }else printf("Ollie wins\n");

    }
    



    return 0;
}