#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, d;
        cin>>n>>d;

        vector<int> a(n);

        for(int i = 0; i < n; i++){
            cin >> a[i];
        }

        vector<int> b(3 * n);
        for(int i = 0; i < 3 * n; i++){
            b[i] = a[i % n];
        }
        vector<int> pre(3 * n + 1, 0);

        for(int i = 0; i < 3 * n; i++){
            pre[i + 1] = pre[i] + b[i];
        }
        int ans = 0;

        for(int i = 0; i < n; i++){
            int pos = n + i;

            int left = pre[pos] - pre[pos - d];
            int right = pre[pos + d + 1] - pre[pos + 1];

            int coeff = 2LL * d * a[i] - (left + right);

            if (coeff > 0){
                ans += coeff;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}