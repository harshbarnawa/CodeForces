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

        string a, b;
        cin >> a >> b;

        // dp[i] = min cost to tile columns 0..i-1
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for(int i = 0; i < n; i++){
            if(dp[i] == INT_MAX) continue;

            // Option 1: vertical domino at column i
            int costV = (a[i] != b[i]);
            dp[i + 1] = min(dp[i + 1], dp[i] + costV);

            // Option 2: two horizontal dominos spanning columns i and i+1
            if(i + 1 < n){
                int costH = (a[i] != a[i + 1]) + (b[i] != b[i + 1]);
                dp[i + 2] = min(dp[i + 2], dp[i] + costH);
            }
        }

        cout << dp[n] << "\n";
    }

    return 0;
}
