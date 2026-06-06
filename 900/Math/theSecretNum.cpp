#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long n, p = 10;
        cin >> n;

        vector<long long> ans;

        for (int i = 1; i <= 18; i++) {
            if (n % (p + 1) == 0)
                ans.push_back(n / (p + 1));
            p *= 10;
        }

        sort(ans.begin(), ans.end());

        cout << ans.size() << '\n';
        for(auto i : ans){
            cout << i << ' ';

        }
        if (!ans.empty()) cout << '\n';
    }
}