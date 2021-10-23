#include<cstdio>
#include<cstdlib>
#include<iostream>

typedef long long unsigned int llu;
int k;

void solve(int vect[],int min,int max,int biggest){
    if (max == min)
    {
        return;
    }
    
    for (int i = min; i < max-1; i++)
    {
        int diff = vect[i+1] - vect[i];
        if(diff > biggest) biggest = diff;
    }
    
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
        int biggest = 0, indexBig = 0;//maior pulo do caso
        for (int i = 0; i < n-1; i++)
        {
            int diff = vect[i+1] - vect[i];
            if(diff > biggest){
                biggest = diff;
                indexBig = i;
            } 
        }
        solve(vect,indexBig,n,biggest);



        count++;
    }
    
    

    return 0;
}