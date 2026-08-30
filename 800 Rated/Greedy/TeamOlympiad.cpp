#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> v1, v2, v3;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        if (x == 1) v1.push_back(i);
        else if (x == 2) v2.push_back(i);
        else v3.push_back(i);
    }

    int ans = min({v1.size(), v2.size(), v3.size()});

    cout << ans << '\n';

    for (int i = 0; i < ans; i++) {
        cout << v1[i] << " " << v2[i] << " " << v3[i] << '\n';
    }

    return 0;
}