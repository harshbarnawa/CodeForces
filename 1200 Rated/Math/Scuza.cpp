#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<ll> prefSum(n);
        vector<int> prefMax(n);

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;

            if (i == 0) {
                prefMax[i] = x;
                prefSum[i] = x;
            } else {
                prefMax[i] = max(prefMax[i - 1], x);
                prefSum[i] = prefSum[i - 1] + x;
            }
        }

        while (q--) {
            int k;
            cin >> k;

            int idx = upper_bound(prefMax.begin(), prefMax.end(), k) - prefMax.begin() - 1;

            if (idx < 0)
                cout << 0 << " ";
            else
                cout << prefSum[idx] << " ";
        }

        cout << "\n";
    }

    return 0;
}