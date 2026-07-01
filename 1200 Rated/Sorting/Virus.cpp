#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> a(m);

        for (int &x : a)
            cin >> x;

        sort(a.begin(), a.end());

        vector<int> gaps;

        for (int i = 0; i < m - 1; i++) {
            gaps.push_back(a[i + 1] - a[i] - 1);
        }

        gaps.push_back(n - a[m - 1] + a[0] - 1);

        sort(gaps.rbegin(), gaps.rend());

        int days = 0;
        int saved = 0;

        for (int gap : gaps) {

            int rem = gap - 2 * days;

            if (rem <= 0)
                continue;

            if (rem == 1) {
                saved++;
                days++;
            } else {
                saved += rem - 1;
                days += 2;
            }
        }

        cout << n - saved << "\n";
    }

    return 0;
}