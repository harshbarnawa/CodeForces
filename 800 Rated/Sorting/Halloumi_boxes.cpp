#include<bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> a(n), b;
        for(auto &x : a) 
            cin >> x;
        b = a;
        sort(b.begin(), b.end());
        cout << (k > 1 || a == b ? "YES" : "NO") << '\n';
    }
}