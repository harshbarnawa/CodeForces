#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        string b, ans;
        cin >> b;

        for (int i = 0; i < b.size(); i += 2) {
            ans += b[i];
        }

        ans += b.back();

        cout << ans << '\n';
    }

    return 0;
}