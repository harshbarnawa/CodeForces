#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>> t;
    while(t--){
        int n, k;
        string s, t;
        cin>> n>> k >> s >> t;
        long long ct = 0;
        long long ct2 = 0,ct3 = 0;

        for(int i = 0;i < n;i++){
            if(s[i]=='1' && t[i]=='0'){
                ct++;
            } else if(s[i]=='0'&&t[i]=='1'){
                ct2++;
            } else if(s[i]=='1'){
                ct3++;
            }
        }
        long long m = (1LL << k) + 1;

        auto f = [&](long long x){
            return x * (n - x);
        };

        cout << ((m+2)/3) * f(ct + ct3) + ((m + 1)/ 3) * f(ct2 + ct3) + (m/3) * f(ct + ct2) << '\n';







    }
}