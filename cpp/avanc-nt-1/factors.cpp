#include <bits/stdc++.h>

using namespace std;

int main(){

    int cases = 0;
    cin >> cases;
    while (cases--)
    {
        
        int number,n;
        cin >> number;

        if(number < 10)
        {
            cout << number << endl;
            continue;
        }

        int m = 9;
        vector<int> digits;
        while (m > 1)
        {
            while(number % m == 0)
            {
                number = number / m;
                digits.push_back(m);
            }
            m--;
        }
        sort(digits.begin(),digits.end());
        if(number == 1){
            for (auto &&i : digits)
            {
                cout << i;
            }
            
        }else cout << -1;
        cout << endl;
    }





    return 0;
}