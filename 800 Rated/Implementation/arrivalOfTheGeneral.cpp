#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);

    for (int &x : a) cin >> x;

    int mx = *max_element(a.begin(), a.end());
    int mn = *min_element(a.begin(), a.end());

    int maxPos, minPos;

    for (int i = 0; i < n; i++) {
        if (a[i] == mx) {
            maxPos = i;
            break;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == mn) {
            minPos = i;
            break;
        }
    }

    int ans = maxPos + (n - 1 - minPos);

    if (maxPos > minPos) ans--;

    cout << ans;

    return 0;
}