#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        long long mx = 0;

        for (int i = 0; i < n; i++) {
            long long x;
            cin >> x;

            if (x < mx)
                mx += x;
            else
                mx = x;
        }

        cout << mx << '\n';
    }

    return 0;
}