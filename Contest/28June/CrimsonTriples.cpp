#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        cin>>n;

        long long ans = 0;

        for(int i = 1;i <= n;i++){
            long long x = n / i;
            ans += x * x;
        }

        cout << ans << "\n";

    }
}