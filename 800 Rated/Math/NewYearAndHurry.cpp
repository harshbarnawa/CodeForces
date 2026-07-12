#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int time = 240 - k;
    int sum = 0, ans = 0;

    for (int i = 1; i <= n; i++) {
        sum += 5 * i;
        if (sum <= time)
            ans++;
        else
            break;
    }

    cout << ans;

    return 0;
}