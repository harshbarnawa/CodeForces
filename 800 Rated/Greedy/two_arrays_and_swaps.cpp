#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n), b(n);

        for (int &x : a) cin >> x;
        for (int &x : b) cin >> x;

        sort(a.begin(), a.end());                  // smallest first
        sort(b.rbegin(), b.rend());                // largest first

        for (int i = 0; i < k; i++) {
            if (b[i] > a[i]) {
                swap(a[i], b[i]);
            }
        }

        cout << accumulate(a.begin(), a.end(), 0) << '\n';
    }

    return 0;
}