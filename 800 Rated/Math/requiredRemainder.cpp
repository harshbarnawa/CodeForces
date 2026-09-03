#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long x, y, n;
        cin >> x >> y >> n;

        cout << n - (n - y) % x << '\n';
    }

    return 0;
}