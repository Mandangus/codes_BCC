#include <bits/stdc++.h>

#define VALID ch != '#' && ch != EOF && ch != '\n'
int numero = 131071;

using namespace std;



int main(){
    char ch = 0;
    int numeroInt = 0;
    while(true)
    {
        ch = getc(stdin);
        if(ch == EOF) break;

        if(ch == '#'){
            if(numeroInt == 0) cout << "YES\n";
            else cout << "NO\n";
            numeroInt = 0;
        }else if (ch == 48 || ch == 49)
        {
            numeroInt = numeroInt * 2 + ch - 48;
            if(numeroInt >= numero) numeroInt %= numero;
        }

    }
    



    return 0;
}