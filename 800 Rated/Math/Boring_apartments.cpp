#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        string x;
        cin >> x;

        int d = x[0] - '0';
        int len = x.size();

        cout << (d - 1) * 10 + len * (len + 1) / 2 << '\n';
    }

    return 0;
}