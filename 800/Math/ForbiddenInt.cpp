#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, k, x;
        cin >> n >> k >> x;

        vector<int> ans;

        if (x != 1) {
            ans.assign(n, 1);
        }
        else {
            if (k == 1 || (k == 2 && n & 1)) {
                cout << "NO\n";
                continue;
            }

            if (n & 1) {
                ans.push_back(3);
                n -= 3;
            }

            while (n) {
                ans.push_back(2);
                n -= 2;
            }
        }

        cout << "YES\n";
        cout << ans.size() << "\n";

        for (auto x : ans) cout << x << " ";
        cout << "\n";
    }
}