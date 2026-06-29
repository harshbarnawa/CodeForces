class Solution {
public:
    
};

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

        vector<long long> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        bool sorted = true;

        for (int i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                sorted = false;
                break;
            }
        }

        if (!sorted) {
            cout << 0 << "\n";
            continue;
        }

        long long ans = LLONG_MAX;

        for (int i = 0; i < n - 1; i++) {
            long long diff = a[i + 1] - a[i];
            ans = min(ans, diff / 2 + 1);
        }

        cout << ans << "\n";
    }

    return 0;
}