#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        string a, b;

        cin >> n;
        cin >> a >> b;

        int oddA = 0, evenA = 0;
        int oddB = 0, evenB = 0;

        for (int i = 0; i < n; i++) {
            if (a[i] == '1') {
                if (i % 2 == 0) oddA++;
                else evenA++;
            }

            if (b[i] == '1') {
                if (i % 2 == 0) oddB++;
                else evenB++;
            }
        }

        if (oddA == oddB && evenA == evenB)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}