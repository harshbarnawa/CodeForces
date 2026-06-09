#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while(t--){
        int n, x;
        cin>> n >> x;

        vector<int> a(n);
        int ans = 0, prev = 0;

        for(int i = 0; i < n; i++){
            cin >> a[i];
            ans = max(ans, a[i] - prev); //5 - 1 = 4
            prev = a[i]; //stilll 1
        }
        //max of 4 and 2(7-5) comparing last dig
        ans = max(ans, 2 * (x - a[n - 1]));

        cout << ans << '\n';
    }
}