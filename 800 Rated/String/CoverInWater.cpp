#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while(t--) {
        int n, ct = 0;
        string s;
        cin>> n >> s;

        bool ok = false; //...

        for(int i = 0; i < n; i++) {
            if(s[i] == '.')
                ct++;
 // if 3 consecutive empty cells ans is 2
            if(i + 2 < n && s[i] == '.' && s[i + 1] == '.' && s[i + 2] == '.') {
                ok = true;
                break;
            }
        }
        cout << (ok ? 2 : ct) << '\n';
    }
}