#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<string> w(n), a(m);
        for (auto &x : w) cin >> x;
        for (auto &x : a) cin >> x;

        set<char> have;
        for (auto x : w)
            have.insert(toupper(x[0]));

        vector<bool> done(m, false);
        int cnt = 0;

        while (true) {
            bool changed = false;

            for (int i = 0; i < m; i++) {
                if (done[i]) continue;

                bool ok = true;
                for (char c : a[i]) {
                    if (!have.count(c)) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    done[i] = true;
                    have.insert(a[i][0]);
                    cnt++;
                    changed = true;
                }
            }

            if (!changed) break;
        }

        cout << (cnt == m ? "YES" : "NO") << '\n';
    }

    return 0;
}