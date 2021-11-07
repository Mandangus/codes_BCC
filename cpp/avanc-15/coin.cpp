#include <bits/stdc++.h>

int n,m;

using namespace std;

int memo[20000][100];


int dp(int vec[],int metade){
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j <= metade; j++)
        {
            if(vec[i]<=j){
                memo[j][i] = max(memo[j][i-1],vec[i]+memo[j-vec[i]][i-1]);
            }else
            {
                memo[j][i] = memo[j][i-1];  
            }
            
        }
            
    }
    return 2*memo[metade][m];
}



int main(void){
    
    cin >> n;
    int count = 0;
    while (count<n)
    {
        cin >> m;
        int vec[m];
        int total = 0;
        for (int i = 1; i <= m; i++){
            cin >>vec[i];
            total+=vec[i];
        }
        int metade = total/2;
        for(int i = 0; i <= metade;i++){
            memo[i][0] = 0;
        }

        cout << total - dp(vec,metade) << endl;
        

        count++;
    }
    





    return 0;
}