#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        string n;
        cin >> n;

        char mn = '9';

        for(char c : n){
            mn = min(mn, c);
        }

        cout << mn - '0' << '\n';
    }

    return 0;
}