#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;

        vector<int> l(n + 1), r(n + 1), u(n + 1), v(n + 1);

        for(int i = 1; i <= n; i++){
            cin >> l[i] >> r[i] >> u[i] >> v[i];
        }

        int ans = 0;

        for(int m = 1; m <= n; m++){
            vector<int> dp(m + 1, 0);
            dp[0] = 1;

            for(int i = 1; i <= n; i++){
                for(int j = min(i, m); j >= 1; j--){
                    int rr = m - j + 1;

                    if(dp[j - 1] &&
                       !(l[i] <= j && j <= r[i]) &&
                       !(u[i] <= rr && rr <= v[i])){
                        dp[j] = 1;
                    }
                }
            }

            if(dp[m]) ans = m;
        }

        cout << ans << '\n';
    }

    return 0;
}