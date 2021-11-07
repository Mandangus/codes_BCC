#include <bits/stdc++.h>

using namespace std;

int t,n,g;

int memo[10000][31];

typedef struct object obj_t;

struct object{
    int p,w;
};

int dp(obj_t things[],int mw){
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= mw; j++)
        {
            if (i == 0 or j == 0)
            {
                memo[i][j] = 0;

            }else if (things[i-1].w <= j)
            {
                memo[i][j] = max(things[i-1].p+memo[i-1][j-things[i-1].w],memo[i-1][j]);   
            }else
            {
                memo[i][j] = memo[i-1][j];
            }
            
        }
        
    }
    
    return memo[n][mw];
}

int main(void){
    cin >> t;
    while (t--)
    {
        cin >> n;
        obj_t things[n];
        for (int i = 0; i < n; i++) cin >> things[i].p >> things[i].w;

        cin >> g;
        int mw[g];
        for (int i = 0; i < g; i++) cin >> mw[i];

        int total = 0;

        for (int i = 0; i < g; i++)
        {
            total += dp(things,mw[i]);
        }
        
        printf("%d\n",total);
        
    }
    



    return 0;
}