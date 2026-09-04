#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int even = 0, odd = 0;

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;

            if (i % 2 != x % 2) {
                if (i % 2 == 0)
                    even++;
                else
                    odd++;
            }
        }

        if (even != odd)
            cout << -1 << '\n';
        else
            cout << even << '\n';
    }

    return 0;
}