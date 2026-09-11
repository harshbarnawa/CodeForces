#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int mx1 = max(a, b);
        int mx2 = max(c, d);

        vector<int> v = {a, b, c, d};
        sort(v.begin(), v.end());

        if ((mx1 == v[3] && mx2 == v[2]) ||
            (mx1 == v[2] && mx2 == v[3]))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}