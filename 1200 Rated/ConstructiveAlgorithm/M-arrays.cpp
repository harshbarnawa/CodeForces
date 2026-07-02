#include<bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;

    while(t--){
        int n,m;
        cin>>n>>m;

        vector<int> ct(m);

        for(int i = 0;i < n;i++){
            int x;
            cin>>x;
            ct[x % m]++;
        }

        int ans = 0;

        if(ct[0] > 0){
            ans++;
        }

        for(int i = 1;i <= (m - 1) / 2;i++){
            int a = ct[i];
            int b = ct[m - i];

            if(a == 0 || b == 0){
                ans += max(a,b);
            }
            else{
                ans += 1 + max(0LL,abs(a - b) - 1);
            }
        }

        if(m % 2 == 0 && ct[m / 2] > 0){
            ans++;
        }

        cout<<ans<<"\n";
    }

    return 0;
}