#include <bits/stdc++.h>

using namespace std;
typedef long unsigned int lu;

int main(){
    int t;
    lu G,L;
    cin >> t;
    while (t--)
    {
        // gcd(x,y) para minimizar x: então G = x
        // se G = x portanto gcd * lcm = a * b
        // G * L = G * b
        // b = L
        cin >> G >> L;
        if(L%G==0) {
            cout << G << " " << L << endl;
        }else cout << "-1\n";
    }
    


    return 0;
}