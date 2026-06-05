#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;

    while(t--){
        int n,k;
        string s;
        cin>>n>>k >> s;

        vector<int> f(26);
        for (char c : s) {
            f[c - 'a']++;
        }
        int odd = 0;


        for (int x : f)
            odd += x & 1;

        cout << (k >= odd - ((n - k) & 1) ? "YES" : "NO") << '\n';
    }
}