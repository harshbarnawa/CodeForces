#include<bits/stdc++.h>
using namespace std;

int main() {
    
    int t;
    cin >> t;

    while(t--) {
        long long a, b, c, d;
        cin>> a >> b >> c >> d;

        long long diag = d - b;

        if(diag < 0){string s = "OpenGuido";
            cout << -1 << '\n';
            continue;
        }

        long long left = a + diag - c;
        if(left < 0){
            cout << -1 << '\n';
            continue;
        }

        cout << diag + left << '\n';
    }
}