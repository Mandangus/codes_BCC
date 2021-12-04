#include <bits/stdc++.h>

using namespace std;


#define MIN(a,b,c) min(min(a,b),c)
#define MAX 5000

int memo[MAX][MAX];
int delta = 1;

int compar(const void* p1,const void* p2)
{
    if(*(int*)p1 < *(int*)p2) return -1;
    if(*(int*)p1 == *(int*)p2) return 0;
    if(*(int*)p1 > *(int*)p2) return  1;

    return 0;
}

int alpha(int i, int j, int seq1[],int seq2[]){
    int ix = seq1[i];
    int iy = seq2[j];

    return abs(ix - iy);
    
}

int alin(int i, int j, int s1[], int s2[]){

    if (i==0){
        memo[0][j] = j*delta;
        return j*delta;
    }
    if (j==0){
        memo[0][i] = i*delta;
        return i*delta;
    }

    if (memo[i][j] != -1){
        return memo[i][j];
    }

    memo[i][j] = MIN(
        alpha(i-1,j-1,s1,s2) + alin(i-1,j-1,s1,s2),
        delta + alin(i-1,j,s1,s2), 
        delta + alin(i,j-1,s1,s2)
    );

    return memo[i][j];
}

int main(){

    int n;
    cin >> n;
    
    int a[n];
    int sortado[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
        sortado[i] = a[i];
    }
    //edit distance!! para a sequencia de cartas
    qsort(sortado,n,sizeof(int),compar);//pegamos a sequencia certa

    memset(memo,-1,sizeof(memo));
    int dist2 = alin(n,n,a,sortado);

    printf("%d\n",dist2);

    return 0;
}