#include<bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

      int t; cin >> t;
    string x = "Timur";
    sort(x.begin(), x.end());

    while (t--) {
        int n; string s;
        cin >> n >> s;

        sort(s.begin(), s.end());
        cout << (n == 5 && s == x ? "YES" : "NO") << '\n';
    }
}