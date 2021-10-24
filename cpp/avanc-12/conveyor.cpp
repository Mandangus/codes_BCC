#include<cstdio>
#include<cstdlib>
#include<iostream>

typedef long long unsigned int llu;
using namespace std;

int k;// minima capacidade do maior container


int f(int cap,int maximos[],int numVessl,int nCont){//funcao a ser bisectada
    int soma = 0, atual = 0;
    for (int i = 0; i < numVessl; i++)
    {
        if(maximos[i] > cap) return -1;//não é o maior!!!

        if(atual + maximos[i] > cap) atual = 0;// esvazia o atual!!!
        if(atual == 0) soma++;

        atual += maximos[i];
        if(soma > nCont) return -1;// mais elementos na soma que existem?!!

    }
    return 0;
}

int main(){
    llu nCont = 0;
    int nVessl = 0;
    while(scanf("%d",&nVessl) == 1){
        cin >> nCont;
        int capVessl[nVessl];
        for (int i = 0; i < nVessl; i++)
        {
            cin >> capVessl[i];
        }
        //vamos fazer o mesmo procedimento do primeiro exercicio...


        int max = nVessl+1, min = 0;
        while (max - min > 0)
        {
            if(f(max,capVessl,nVessl,nCont)>=0){//no caso vams apenas checar se a função é válida para dado max!!
                max = min + (max - min)/2;
            } else{
                min = max;
                max = max + max/2;
            }
        }
        k = max + 1;
        printf("%d\n",k);
    }

    return 0;
}