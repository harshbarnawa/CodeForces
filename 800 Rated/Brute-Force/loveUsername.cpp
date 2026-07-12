#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int best = a[0], worst = a[0];
    int ans = 0;

    for (int i = 1; i < n; i++) {
        if (a[i] > best) {
            ans++;
            best = a[i];
        } else if (a[i] < worst) {
            ans++;
            worst = a[i];
        }
    }

    cout << ans << endl;
    return 0;
}