#include <bits/stdc++.h>

using namespace std;

typedef long unsigned int lu;

struct prime{
    int value;
    int nums;
};

vector<prime> p;

int findPower(int n,int p)//acha a ocorrencia da potencia p de um primo em n!
{
    int res = 0;
    n /= p;
    do
    {
        res += n;
        n /= p;
    } while (n > 0);
    
    return res;
}

void checkInsert(int number){
    for (int i = 0; i < (int)p.size(); i++)
    {
        if(p[i].value == number){
            p[i].nums++;
            return;
        }
    }
    prime aux;
    aux.nums = 1;
    aux.value = number;
    p.push_back(aux);
}

void primeFactors(int m){

    while (m%2 == 0)
    {
        checkInsert(2);
        m /= 2;
    }
    
    for (int i = 3; i <= sqrt(m); i++)
    {
        while (m%i == 0)
        {
            checkInsert(i);
            m /= i;
        }
        
    }
    
    if(m > 2) checkInsert(m);

}

bool dividesFac(int n,int m){
    primeFactors(m);
    for (auto &&i : p)
    {
        int numPow = findPower(n,i.value);
        if(numPow < i.nums) return false;
    }
    return true;
}


int main(){

    int n , m;
    while (cin >> n >> m)
    {
        p.clear();
        if(dividesFac(n,m)){
            printf("%d divides %d!\n",m,n);
        }else
        {
            printf("%d does not divide %d!\n",m,n);
        }
        
    }
    



    return 0;
}