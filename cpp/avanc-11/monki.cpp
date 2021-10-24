#include<cstdio>
#include<cstdlib>
#include<iostream>

typedef long long unsigned int llu;
int k;

int f(int pulo,int vect[],int tam){//função do pulo no bambu
    int start = 0;//começo do pulo
    for (int i = 0; i < tam; i++)
    {
        int tamPulo = vect[i] - start;
        if(tamPulo < pulo){// se for válido pulamos
            start += tamPulo;
        } else if(tamPulo == pulo){// se for igual ao pulo máximo vamos decrementar!!
            start += tamPulo;
            pulo--;
        } else return -10000;// falhou o pulo!!! retorna -inf
    }
    return pulo;// completamos o bambu retorna o valor de k finalizado da função
}



int main(){
    int T = 0, count = 0;
    scanf("%d",&T);
    while (count < T)
    {
        llu n = 0;
        scanf("%lld",&n);
        int vect[n];
        for (llu i = 0; i < n; i++)
        {
            scanf("%d",&vect[i]);
        }

        k = 0;
        
        int max = n+1, min = 0;
        while (max - min > 0)
        {
            if(f(max,vect,n)>=0){
                max = min + (max - min)/2;
            } else{
                min = max;
                max = max + max/2;
            }
        }

        k = max + 1;
        count++;
        
        printf("Case %d: %d\n",count,k);
    }
    
    

    return 0;
}