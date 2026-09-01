#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    int mx = 0;

    for (int &x : a) {
        cin >> x;
        mx = max(mx, x);
    }

    int ans = 0;

    for (int x : a)
        ans += mx - x;

    cout << ans << '\n';

    return 0;
}