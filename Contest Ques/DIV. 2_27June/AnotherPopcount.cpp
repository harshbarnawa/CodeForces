#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;

    while(t--){
        int n, k;
        cin>> n>>k;
        long long ans = 0;
        long long p = 1;

        while(p <= n){
            long long ct = n / p;
            if(ct > k){
                ct = k;
            }

            ans += ct;
            n -= ct * p;
            p *= 2;
        }
        cout << ans << '\n';
    }
}