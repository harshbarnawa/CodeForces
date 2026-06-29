#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        int xr = 0;
        for(int i = 0; i < n; i++){
            int x;
            cin >> x;
            xr ^= x;
        }

        if(n & 1)
            cout << xr << '\n';
        else {
            if(xr == 0)
                cout << 0 << '\n';
            else
                cout << -1 << '\n';
        }
    }
}