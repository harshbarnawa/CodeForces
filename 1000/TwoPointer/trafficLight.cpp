#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        char c;
        cin >> n >> c;

        string s;
        cin >> s;

        if (c == 'g') {
            cout << 0 << "\n";
            continue;
        }

        string temp = s + s;

        vector<int> green;

        for (int i = 0; i < 2 * n; i++) {
            if (temp[i] == 'g') {
                green.push_back(i);
            }
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (temp[i] == c) {
                int idx = lower_bound(green.begin(), green.end(), i) - green.begin();
                ans = max(ans, green[idx] - i);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}