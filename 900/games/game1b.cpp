#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        string s;
        cin >> s;

        int a = count(s.begin(), s.end(), '0');
        int b = s.size() - a;

        cout << (min(a, b) % 2 ? "DA" : "NET") << '\n';
    }

    return 0;
}