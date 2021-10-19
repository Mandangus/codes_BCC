#include<cstdio>
#include<iostream>

typedef long long unsigned int llu;

using namespace std;
llu ans;

void merge(llu *vet,llu inf, llu mid, llu sup)
{


    llu i = inf;
    llu j = mid + 1;
    llu newTam = sup - inf + 1;
    llu temp[newTam];
    
    //printf("inf %lld - mid %lld - sup %lld\n",inf,mid,sup);

    llu k = 0;

    while (i <= mid && j <= sup)
    {
        if (vet[i] <= vet[j])
        {
            temp[k++] = vet[i++];
        }else
        {
            temp[k++] = vet[j++];
        }
    }    

    

    while (i<=mid)
    {
        temp[k++] = vet[i++];
    }
    
    while (j<=sup)
    {
        temp[k++] = vet[j++];
    }

    for (int m = 0; m < newTam; m++)
    {
        printf("%lld ",temp[m]);
    }
    cout << endl;

    //lista A
    if(temp[0]*(mid-inf+1)>ans)
        ans = temp[0]*(mid-inf+1);
    //lista B
    if(temp[mid+1]*(sup-mid)>ans)
        ans = temp[mid+1]*(sup-mid);

    
    
    return;
    
}

//inf == mid 
void solve(llu *vet,llu inf,llu max)
{
    if(inf >= max){
        if(vet[inf] > ans){
            ans = vet[inf];
        } 
        printf("%lld\n",vet[inf]);
        return;
    } 


    llu mid = (inf + max)/2;

    solve(vet, inf, mid);
    solve(vet, mid+1, max);
    merge(vet, inf, mid, max);


    return;

}


int main(int argc, char const *argv[])
{

    llu tam;
    while (cin >> tam)
    {
        if (tam != 0)
        {
            llu vet[tam];

            for (llu i = 0; i < tam; i++)
            {
                cin >> vet[i];
            }
            ans = 0;
            solve(vet,0,tam-1);
            cout << ans << endl;
        }
    }
    
    

    return 0;
}