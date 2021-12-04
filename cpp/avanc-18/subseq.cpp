#include <bits/stdc++.h>

using namespace std;
#define MAX 5001

int memo[MAX][MAX];

int main(void){

    char str1[MAX],str2[MAX];
    while (cin >> str1 >> str2)
    {
        int len1 = strlen(str1);
        int len2 = strlen(str2);

        memset(memo,-1,sizeof(memo));

        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                if(str1[i-1] == str2[j-1]){
                    memo[i][j] = memo[i-1][j-1] + 1;
                }else{
                    memo[i][j] = max(memo[i-1][j],memo[i][j-1]);
                }
            }
            
        }
        cout << memo[len1][len2] + 1 << endl;

    }
    
        

    return 0;
}